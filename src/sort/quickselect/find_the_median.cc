// https://www.hackerrank.com/challenges/find-the-median/problem
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int partition(vector<int>& arr, int l, int r) {
    int pivot = arr[r];
    int i = l;
    for (int j = l; j < r; j++) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[r]);
    return i;
}

int quickselect(vector<int>& arr, int l, int r, int k) {
    if (l <= r) {
        int p = partition(arr, l, r);
        if (p == k) return arr[p];
        if (p > k) return quickselect(arr, l, p - 1, k);
        return quickselect(arr, p + 1, r, k);
    }
    return -1;
}

int findMedian(vector<int>& arr) {
    int n = static_cast<int>(arr.size());
    return quickselect(arr, 0, n - 1, n / 2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << findMedian(arr) << "\n";
    return 0;
}
