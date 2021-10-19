#include <bits/stdc++.h>

namespace oi {

int partition(std::vector<int> &nums, int l, int r) {
  int pivot = nums[r];
  int i = (l - 1);
  for (int j = l; j < r; j++) {
    if (nums[j] <= pivot) {
      std::swap(nums[++i], nums[j]);
    }
  }
  std::swap(nums[i + 1], nums[r]);
  return (i + 1);
}

void quickSort(std::vector<int> &nums, int l, int r) {
  if (l < r) {
    int m = partition(nums, l, r);
    quickSort(nums, l, m - 1);
    quickSort(nums, m + 1, r);
  }
}

inline std::vector<int> quick_sort(std::vector<int> &nums) {
  quickSort(nums, 0, static_cast<int>(nums.size() - 1));
  return nums;
}
}
