#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0, m = 0;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> adj(static_cast<size_t>(n));
    vector<int> in_deg(static_cast<size_t>(n), 0);
    vector<int> out_deg(static_cast<size_t>(n), 0);

    for (int i = 0; i < m; ++i) {
        int u = 0, v = 0;
        cin >> u >> v;
        adj[static_cast<size_t>(u)].push_back(v);
        ++out_deg[static_cast<size_t>(u)];
        ++in_deg[static_cast<size_t>(v)];
    }

    // Sort edges for deterministic traversal order
    for (int i = 0; i < n; ++i) {
        sort(adj[static_cast<size_t>(i)].rbegin(), adj[static_cast<size_t>(i)].rend());
    }

    int start_node = -1;
    int end_node = -1;
    int bad_nodes = 0;

    for (int i = 0; i < n; ++i) {
        if (out_deg[static_cast<size_t>(i)] - in_deg[static_cast<size_t>(i)] == 1) {
            if (start_node != -1) bad_nodes = 100;
            start_node = i;
        } else if (in_deg[static_cast<size_t>(i)] - out_deg[static_cast<size_t>(i)] == 1) {
            if (end_node != -1) bad_nodes = 100;
            end_node = i;
        } else if (in_deg[static_cast<size_t>(i)] != out_deg[static_cast<size_t>(i)]) {
            bad_nodes = 100;
        }
    }

    bool is_circuit = false;
    if (bad_nodes == 0 && start_node == -1 && end_node == -1) {
        is_circuit = true;
        for (int i = 0; i < n; ++i) {
            if (out_deg[static_cast<size_t>(i)] > 0) {
                start_node = i;
                break;
            }
        }
        if (start_node == -1) start_node = 0;
    } else if (bad_nodes == 0 && start_node != -1 && end_node != -1) {
        is_circuit = false;
    } else {
        cout << "NO EULERIAN PATH\n";
        return 0;
    }

    // Hierholzer's algorithm using stack
    vector<int> st;
    vector<int> path;
    st.push_back(start_node);

    while (!st.empty()) {
        int u = st.back();
        if (!adj[static_cast<size_t>(u)].empty()) {
            int v = adj[static_cast<size_t>(u)].back();
            adj[static_cast<size_t>(u)].pop_back();
            st.push_back(v);
        } else {
            path.push_back(u);
            st.pop_back();
        }
    }

    reverse(path.begin(), path.end());

    if (static_cast<int>(path.size()) != m + 1) {
        cout << "NO EULERIAN PATH\n";
        return 0;
    }

    if (is_circuit) {
        cout << "CIRCUIT\n";
    } else {
        cout << "PATH\n";
    }

    for (size_t i = 0; i < path.size(); ++i) {
        if (i > 0) cout << " ";
        cout << path[i];
    }
    cout << "\n";

    return 0;
}
