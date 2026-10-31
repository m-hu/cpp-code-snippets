// https://www.hackerrank.com/challenges/longest-increasing-subsequent/problem
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int longestIncreasingSubsequence(const vector<int>& arr) {
    if (arr.empty()) return 0;
    vector<int> tails;
    for (int x : arr) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) {
            tails.push_back(x);
        } else {
            *it = x;
        }
    }
    return static_cast<int>(tails.size());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;
    vector<int> arr(static_cast<size_t>(n));
    for (int i = 0; i < n; i++) {
        cin >> arr[static_cast<size_t>(i)];
    }

    cout << longestIncreasingSubsequence(arr) << "\n";
    return 0;
}
