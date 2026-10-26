#include <bits/stdc++.h>

namespace oi {

// Counting sort for non-negative values. The effective bound is the
// larger of the caller-provided upper_bound and the actual maximum,
// so values above upper_bound are no longer indexed out of bounds.
// The previous version trusted upper_bound blindly, while the driver
// passed a fixed 10000 even for inputs up to ~1e6.
inline std::vector<int> counting_sort(const std::vector<int> &nums, int upper_bound) {
	std::vector<int> output(nums.size());
	if (nums.empty()) {
		return output;
	}
	int effective_bound = upper_bound;
	for (int num : nums) {
		if (num < 0) {
			// Counting sort is defined here for non-negative keys;
			// fall back to comparison sort rather than dropping
			// negative elements from the output.
			std::vector<int> sorted = nums;
			std::sort(sorted.begin(), sorted.end());
			return sorted;
		}
		if (num > effective_bound) {
			effective_bound = num;
		}
	}
	if (effective_bound < 0) {
		return output;
	}
	std::vector<int> count(static_cast<size_t>(effective_bound) + 1, 0);
	for (int num : nums) {
		if (num >= 0) {
			++count[static_cast<size_t>(num)];
		}
	}
	size_t k = 0;
	for (int value = 0; value <= effective_bound; ++value) {
		for (int j = 0; j < count[static_cast<size_t>(value)]; ++j) {
			output[k++] = value;
		}
	}
	return output;
}

}
