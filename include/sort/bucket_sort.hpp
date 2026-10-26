#include <bits/stdc++.h>
#include "sort/insertion_sort.hpp"

namespace oi {

inline std::vector<int> bucket_sort(std::vector<int> &nums, int k) {
	if (nums.empty()) {
		return nums;
	}
	std::vector<std::vector<int> > bucket(k + 1);
	int max = *max_element(nums.begin(), nums.end());
	int min = *min_element(nums.begin(), nums.end());
	if (max == min) {
		// All elements equal: already sorted. This also avoids the
		// division by zero (max - min == 0) that crashed this case.
		return nums;
	}
	for (size_t i = 0; i < nums.size(); ++i) {
		// Widen before multiplying: (nums[i] - min) * k overflows int
		// when the value range approaches the full int range.
		long long range = static_cast<long long>(max) - min;
		long long index = (static_cast<long long>(nums[i]) - min) * k / range;
		bucket[static_cast<size_t>(index)].push_back(nums[i]);
	}
	for (std::vector<int> &b : bucket) {
		oi::insertion_sort(b);
	}
	size_t i = 0;
	for (const std::vector<int> &b : bucket) {
		for (int a : b) {
			nums[i++] = a;
		}
	}
	return nums;
}

}
