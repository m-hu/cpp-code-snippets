#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

struct Event {
    string name;
    vector<int> vc;
};

// Returns: 1 if a -> b, -1 if b -> a, 0 if a || b (concurrent), 2 if a == b
int compare_clocks(const vector<int>& a, const vector<int>& b) {
    bool a_le_b = true;
    bool b_le_a = true;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] > b[i]) a_le_b = false;
        if (b[i] > a[i]) b_le_a = false;
    }
    if (a_le_b && b_le_a) return 2;
    if (a_le_b) return 1;
    if (b_le_a) return -1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n_procs = 0, n_ops = 0;
    if (!(cin >> n_procs >> n_ops)) return 0;

    vector<vector<int>> vc(static_cast<size_t>(n_procs), vector<int>(static_cast<size_t>(n_procs), 0));
    map<string, vector<int>> event_clocks;
    map<string, vector<int>> in_flight_messages;

    for (int op_idx = 0; op_idx < n_ops; ++op_idx) {
        string op;
        cin >> op;

        if (op == "LOCAL") {
            int p = 0;
            string name;
            cin >> p >> name;
            ++vc[static_cast<size_t>(p)][static_cast<size_t>(p)];
            event_clocks[name] = vc[static_cast<size_t>(p)];
        } else if (op == "SEND") {
            int from_p = 0;
            string msg_id;
            cin >> from_p >> msg_id;
            ++vc[static_cast<size_t>(from_p)][static_cast<size_t>(from_p)];
            in_flight_messages[msg_id] = vc[static_cast<size_t>(from_p)];
            event_clocks[msg_id + "_SEND"] = vc[static_cast<size_t>(from_p)];
        } else if (op == "RECV") {
            int to_p = 0;
            string msg_id;
            cin >> to_p >> msg_id;
            const auto& msg_vc = in_flight_messages[msg_id];
            for (int k = 0; k < n_procs; ++k) {
                vc[static_cast<size_t>(to_p)][static_cast<size_t>(k)] = max(vc[static_cast<size_t>(to_p)][static_cast<size_t>(k)], msg_vc[static_cast<size_t>(k)]);
            }
            ++vc[static_cast<size_t>(to_p)][static_cast<size_t>(to_p)];
            event_clocks[msg_id + "_RECV"] = vc[static_cast<size_t>(to_p)];
        }
    }

    int n_queries = 0;
    if (cin >> n_queries) {
        for (int q = 0; q < n_queries; ++q) {
            string e1, e2;
            cin >> e1 >> e2;
            const auto& v1 = event_clocks[e1];
            const auto& v2 = event_clocks[e2];
            int rel = compare_clocks(v1, v2);
            if (rel == 1) {
                cout << e1 << " -> " << e2 << "\n";
            } else if (rel == -1) {
                cout << e2 << " -> " << e1 << "\n";
            } else if (rel == 2) {
                cout << e1 << " == " << e2 << "\n";
            } else {
                cout << e1 << " || " << e2 << "\n";
            }
        }
    }

    return 0;
}
