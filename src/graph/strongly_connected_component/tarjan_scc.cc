#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class TarjanSCC {
    int n;
    vector<vector<int>> adj;
    vector<int> dfn;
    vector<int> low;
    vector<bool> on_stack;
    vector<int> st;
    int timer = 0;
    vector<vector<int>> sccs;

    void dfs(int u) {
        dfn[static_cast<size_t>(u)] = low[static_cast<size_t>(u)] = ++timer;
        st.push_back(u);
        on_stack[static_cast<size_t>(u)] = true;

        for (int v : adj[static_cast<size_t>(u)]) {
            if (dfn[static_cast<size_t>(v)] == 0) {
                dfs(v);
                low[static_cast<size_t>(u)] = min(low[static_cast<size_t>(u)], low[static_cast<size_t>(v)]);
            } else if (on_stack[static_cast<size_t>(v)]) {
                low[static_cast<size_t>(u)] = min(low[static_cast<size_t>(u)], dfn[static_cast<size_t>(v)]);
            }
        }

        if (low[static_cast<size_t>(u)] == dfn[static_cast<size_t>(u)]) {
            vector<int> scc;
            while (true) {
                int node = st.back();
                st.pop_back();
                on_stack[static_cast<size_t>(node)] = false;
                scc.push_back(node);
                if (node == u) break;
            }
            sort(scc.begin(), scc.end());
            sccs.push_back(scc);
        }
    }

public:
    TarjanSCC(int n_nodes, const vector<vector<int>>& graph)
        : n(n_nodes), adj(graph),
          dfn(static_cast<size_t>(n_nodes), 0),
          low(static_cast<size_t>(n_nodes), 0),
          on_stack(static_cast<size_t>(n_nodes), false) {}

    vector<vector<int>> run() {
        for (int i = 0; i < n; ++i) {
            if (dfn[static_cast<size_t>(i)] == 0) {
                dfs(i);
            }
        }
        sort(sccs.begin(), sccs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });
        return sccs;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0, m = 0;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> adj(static_cast<size_t>(n));
    for (int i = 0; i < m; ++i) {
        int u = 0, v = 0;
        cin >> u >> v;
        adj[static_cast<size_t>(u)].push_back(v);
    }

    TarjanSCC tarjan(n, adj);
    auto sccs = tarjan.run();

    cout << sccs.size() << "\n";
    for (const auto& scc : sccs) {
        for (size_t i = 0; i < scc.size(); ++i) {
            if (i > 0) cout << " ";
            cout << scc[i];
        }
        cout << "\n";
    }

    return 0;
}
