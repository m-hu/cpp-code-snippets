#include <bits/stdc++.h>

namespace oi {

inline std::vector<int> counting_sort(const std::vector<int> & nums, int upper_bound){
    std::vector<int> count(upper_bound+1, 0);
    std::vector<int> output(nums.size());
    for (int num: nums){
        ++count[num];
    }
    size_t k=0;
    for(size_t i=0; i < upper_bound + 1; ++i){
        for (size_t j=0; j < count[i]; ++j){
            output[k++] = i;
        }
    }
    return output;
}

}
