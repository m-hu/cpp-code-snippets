#include <bits/stdc++.h>

namespace oi {

inline std::vector<int> heap_sort(std::vector<int> &nums) {
	std::priority_queue<int> q;
	for (int num : nums) {
		q.push(num);
	}
	size_t k = nums.size() - 1;
	while (!q.empty()) {
		nums[k--] = q.top();
		q.pop();
	}
	return nums;
}

}
