#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;

    size_t nn = static_cast<size_t>(n);
    vector<set<int>> adj(nn);
    vector<int> spill_cost(nn, 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[static_cast<size_t>(u)].insert(v);
        adj[static_cast<size_t>(v)].insert(u);
    }

    set<int> active;
    for (int i = 0; i < n; ++i) active.insert(i);

    stack<int> select_stack;
    vector<bool> spilled(nn, false);

    while (!active.empty()) {
        // Find node with degree < k
        int simplify_node = -1;
        for (int u : active) {
            int deg = 0;
            for (int v : adj[static_cast<size_t>(u)]) {
                if (active.count(v)) deg++;
            }
            if (deg < k) {
                simplify_node = u;
                break;
            }
        }

        if (simplify_node != -1) {
            active.erase(simplify_node);
            select_stack.push(simplify_node);
        } else {
            // Spill candidate (maximum degree or lowest cost/deg)
            int spill_node = *active.begin();
            active.erase(spill_node);
            spilled[static_cast<size_t>(spill_node)] = true;
        }
    }

    // Color nodes
    vector<int> color(nn, -1);
    while (!select_stack.empty()) {
        int u = select_stack.top();
        select_stack.pop();

        set<int> used_colors;
        for (int v : adj[static_cast<size_t>(u)]) {
            if (color[static_cast<size_t>(v)] != -1) {
                used_colors.insert(color[static_cast<size_t>(v)]);
            }
        }
        for (int c = 0; c < k; ++c) {
            if (!used_colors.count(c)) {
                color[static_cast<size_t>(u)] = c;
                break;
            }
        }
        if (color[static_cast<size_t>(u)] == -1) {
            spilled[static_cast<size_t>(u)] = true;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (spilled[static_cast<size_t>(i)]) {
            cout << "v" << i << ":SPILL\n";
        } else {
            cout << "v" << i << ":R" << color[static_cast<size_t>(i)] << "\n";
        }
    }
    return 0;
}
