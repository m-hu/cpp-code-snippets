#include <bits/stdc++.h>

namespace oi {

// LSD radix sort, base 256 (one byte per pass, 4 passes for int).
// Keys are biased by flipping the sign bit, so negative values order
// correctly; the previous base-10 version indexed buckets with a
// possibly negative digit and silently produced no sorted output
// for negative inputs.
inline std::vector<int> radix_sort(std::vector<int> &nums) {
	const size_t n = nums.size();
	if (n < 2) {
		return nums;
	}
	std::vector<int> buf(n);
	std::vector<int> *src = &nums;
	std::vector<int> *dst = &buf;
	for (int pass = 0; pass < 4; ++pass) {
		const int shift = pass * 8;
		size_t count[256] = {0};
		for (size_t i = 0; i < n; ++i) {
			uint32_t key = static_cast<uint32_t>((*src)[i]) ^ 0x80000000u;
			++count[(key >> shift) & 0xFFu];
		}
		size_t sum = 0;
		for (int b = 0; b < 256; ++b) {
			size_t c = count[b];
			count[b] = sum;
			sum += c;
		}
		for (size_t i = 0; i < n; ++i) {
			uint32_t key = static_cast<uint32_t>((*src)[i]) ^ 0x80000000u;
			(*dst)[count[(key >> shift) & 0xFFu]++] = (*src)[i];
		}
		std::swap(src, dst);
	}
	// 4 (even) passes leave the result back in nums.
	return nums;
}

}
