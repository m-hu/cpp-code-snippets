// https://www.hackerrank.com/challenges/find-the-running-median/problem
#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    priority_queue<int> max_heap; // lower half
    priority_queue<int, vector<int>, greater<int>> min_heap; // upper half

    cout << fixed << setprecision(1);

    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;

        if (max_heap.empty() || val <= max_heap.top()) {
            max_heap.push(val);
        } else {
            min_heap.push(val);
        }

        // Rebalance
        if (max_heap.size() > min_heap.size() + 1) {
            min_heap.push(max_heap.top());
            max_heap.pop();
        } else if (min_heap.size() > max_heap.size()) {
            max_heap.push(min_heap.top());
            min_heap.pop();
        }

        if (max_heap.size() == min_heap.size()) {
            cout << (max_heap.top() + min_heap.top()) / 2.0 << "\n";
        } else {
            cout << static_cast<double>(max_heap.top()) << "\n";
        }
    }

    return 0;
}
