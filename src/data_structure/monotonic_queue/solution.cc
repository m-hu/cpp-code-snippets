#include <cstdint>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0;
    int k = 0;
    if (!(cin >> n >> k) || n <= 0 || k <= 0 || k > n) {
        return 0;
    }

    vector<int64_t> a(static_cast<size_t>(n));
    for (int i = 0; i < n; ++i) {
        cin >> a[static_cast<size_t>(i)];
    }

    deque<int> max_dq;
    deque<int> min_dq;
    vector<int64_t> max_out;
    vector<int64_t> min_out;
    max_out.reserve(static_cast<size_t>(n - k + 1));
    min_out.reserve(static_cast<size_t>(n - k + 1));

    for (int i = 0; i < n; ++i) {
        while (!max_dq.empty() && max_dq.front() <= i - k) {
            max_dq.pop_front();
        }
        while (!max_dq.empty() && a[static_cast<size_t>(max_dq.back())] <= a[static_cast<size_t>(i)]) {
            max_dq.pop_back();
        }
        max_dq.push_back(i);

        while (!min_dq.empty() && min_dq.front() <= i - k) {
            min_dq.pop_front();
        }
        while (!min_dq.empty() && a[static_cast<size_t>(min_dq.back())] >= a[static_cast<size_t>(i)]) {
            min_dq.pop_back();
        }
        min_dq.push_back(i);

        if (i >= k - 1) {
            max_out.push_back(a[static_cast<size_t>(max_dq.front())]);
            min_out.push_back(a[static_cast<size_t>(min_dq.front())]);
        }
    }

    for (size_t i = 0; i < max_out.size(); ++i) {
        if (i > 0) {
            cout << " ";
        }
        cout << max_out[i];
    }
    cout << "\n";

    for (size_t i = 0; i < min_out.size(); ++i) {
        if (i > 0) {
            cout << " ";
        }
        cout << min_out[i];
    }
    cout << "\n";

    return 0;
}
