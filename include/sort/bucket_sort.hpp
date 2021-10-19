#include <bits/stdc++.h>
#include "sort/insertion_sort.hpp"

namespace oi {

inline std::vector<int> bucket_sort(std::vector<int> &nums, int k) {
	std::vector<std::vector<int> > bucket(k + 1);
	int max = *max_element(nums.begin(), nums.end());
	int min = *min_element(nums.begin(), nums.end());
	for (size_t i = 0; i < nums.size(); ++i) {
		int index = (nums[i] - min) * k / (max - min);
		bucket[index].push_back(nums[i]);
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
