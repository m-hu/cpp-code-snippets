#include <bits/stdc++.h>
#include "sort/counting_sort.hpp"

using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i=0; i < n; ++i){
        cin >> nums[i];
    }
    // counting_sort returns a new sorted vector; the result was
    // previously discarded and the unsorted input printed instead.
    vector<int> sorted = oi::counting_sort(nums, 10000);
    cout << "[";
    for (int i=0; i < n; ++i){
        cout << sorted[i];
        if(i!=(n-1))
            cout << ",";
    }
    cout << "]";
    return 0;
}
