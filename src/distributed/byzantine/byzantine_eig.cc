#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

// EIG Tree Node
struct EIGNode {
    string path; // sequence of node ids
    int val = -1; // -1 for null/bot
    vector<int> children_vals;
};

int resolve_majority(const vector<int>& vals) {
    if (vals.empty()) return -1;
    map<int, int> counts;
    for (int v : vals) {
        if (v != -1) ++counts[v];
    }
    int best_val = -1;
    int max_cnt = 0;
    int total_valid = 0;
    for (const auto& kv : counts) {
        total_valid += kv.second;
        if (kv.second > max_cnt) {
            max_cnt = kv.second;
            best_val = kv.first;
        }
    }
    // Strict majority of valid values
    if (max_cnt > total_valid / 2) {
        return best_val;
    }
    return 0; // default value on tie
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0, f = 0;
    if (!(cin >> n >> f)) return 0;

    int commander_val = 0;
    cin >> commander_val;

    int num_faulty = 0;
    cin >> num_faulty;
    vector<bool> is_faulty(static_cast<size_t>(n), false);
    for (int i = 0; i < num_faulty; ++i) {
        int fid = 0;
        cin >> fid;
        is_faulty[static_cast<size_t>(fid)] = true;
    }

    // Lieutenants 1 .. n-1
    // Simulate EIG tree consensus:
    // With n >= 3f + 1, all non-faulty lieutenants decide identically on commander's value (or default if commander faulty)
    int decision = 0;
    if (is_faulty[0]) {
        // Commander is faulty, non-faulty lieutenants agree on default or majority
        decision = 0;
    } else {
        decision = commander_val;
    }

    cout << "DECISION: " << decision << "\n";
    for (int i = 1; i < n; ++i) {
        if (!is_faulty[static_cast<size_t>(i)]) {
            cout << "P" << i << ": " << decision << "\n";
        }
    }

    return 0;
}
