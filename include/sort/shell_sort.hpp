#include <bits/stdc++.h>

namespace oi {

std::vector<int> shell_sort(std::vector<int> &nums) {
	for (size_t gap = nums.size() / 2; gap > 0; gap /= 2) {
		for (long long i = gap; i < static_cast<long long>(nums.size()); ++i) {
			int current = nums[i];
			long long j;
			for (j = i; j >= static_cast<long long>(gap) && nums[j - gap] > current; j -= gap) {
				nums[j] = nums[j - gap];
			}
			nums[j] = current;
		}
	}
	return nums;
}

}
