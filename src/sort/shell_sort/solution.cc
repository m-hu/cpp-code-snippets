#include <bits/stdc++.h>
#include "sort/shell_sort.hpp"

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> nums(n);
	for (int i = 0; i < n; ++i) {
		cin >> nums[i];
	}
	oi::shell_sort(nums);
	cout << "[";
	for (int i = 0; i < n; ++i) {
		cout << nums[i];
		if (i != (n - 1))
			cout << ",";
	}
	cout << "]";
	return 0;
}
