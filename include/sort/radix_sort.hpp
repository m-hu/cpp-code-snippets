#include <bits/stdc++.h>

namespace oi {

std::vector<int> radix_counting_sort(std::vector<int> & nums, int exp){
    std::vector<std::vector<int> > count(10, std::vector<int>());
    for (int num: nums){
        int digit = (num / exp) % 10;
        count[digit].push_back(num);
    }
    size_t k=0;
    for(int i=0; i < 10; ++i){
        for (int num: count[i]){
            nums[k++] = num;
        }
    }
    return nums;
}


inline std::vector<int> radix_sort(std::vector<int> & nums){
    if (!nums.empty()){
        int m = *max_element(nums.begin(), nums.end());
        for (int exp=1; exp <= m; exp *=10){
        	radix_counting_sort(nums, exp);
        }
    }
    return nums;
}

}
