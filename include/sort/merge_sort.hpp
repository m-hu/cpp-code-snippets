#include <bits/stdc++.h>

namespace oi {

void merge(std::vector<int> &nums, size_t l, size_t m, size_t r) {
	std::vector<int> left(nums.begin() + l, nums.begin() + m + 1);
	std::vector<int> right(nums.begin() + m + 1, nums.begin() + r + 1);
	size_t i = 0;
	size_t j = 0;
	size_t k = l;
	while (i < left.size() && j < right.size()) {
		if (left[i] <= right[j]) {
			nums[k++] = left[i++];
		} else {
			nums[k++] = right[j++];
		}
	}
	while (i < left.size()) {
		nums[k++] = left[i++];
	}
	while (j < right.size()) {
		nums[k++] = right[j++];
	}
}

void mergeSort(std::vector<int> &nums, size_t l, size_t r) {
	if (l < r) {
		size_t m = (l + r) / 2;
		mergeSort(nums, l, m);
		mergeSort(nums, m + 1, r);
		merge(nums, l, m, r);
	}
}

inline std::vector<int> merge_sort(std::vector<int> &nums) {
	mergeSort(nums, 0, nums.size() - 1);
	return nums;
}

}
