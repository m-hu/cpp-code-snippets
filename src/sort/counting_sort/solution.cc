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
    oi::counting_sort(nums, 10000);
    cout << "[";
    for (int i=0; i < n; ++i){
        cout << nums[i];
        if(i!=(n-1))
            cout << ",";
    }
    cout << "]";
    return 0;
}
