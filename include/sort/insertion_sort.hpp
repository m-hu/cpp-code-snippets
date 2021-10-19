#include <bits/stdc++.h>

namespace oi {

inline std::vector<int> insertion_sort(std::vector<int> &nums) {
	size_t i;
	long long j; //size_t is of long unsigned int type, j might be less than zero in some cases
	size_t n = nums.size();
	int current;
	for (i = 1; i < n; ++i) {
		current = nums[i];
		j = i - 1;
		while (j >= 0 && nums[j] > current) {
			nums[j + 1] = nums[j];
			j = j - 1;
		}
		nums[j + 1] = current;
	}
	return nums;
}

}
