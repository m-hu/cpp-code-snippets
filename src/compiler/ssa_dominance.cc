#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    size_t sz = static_cast<size_t>(n + 1);
    vector<vector<int>> adj(sz);
    vector<vector<int>> rev_adj(sz);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[static_cast<size_t>(u)].push_back(v);
        rev_adj[static_cast<size_t>(v)].push_back(u);
    }

    // Compute idom using iterative dominator algorithm
    vector<set<int>> dom(sz);
    dom[1].insert(1);
    set<int> all_nodes;
    for (int i = 1; i <= n; ++i) all_nodes.insert(i);
    for (int i = 2; i <= n; ++i) dom[static_cast<size_t>(i)] = all_nodes;

    bool changed = true;
    while (changed) {
        changed = false;
        for (int i = 2; i <= n; ++i) {
            set<int> new_dom;
            bool first = true;
            for (int p : rev_adj[static_cast<size_t>(i)]) {
                if (first) {
                    new_dom = dom[static_cast<size_t>(p)];
                    first = false;
                } else {
                    set<int> intersect;
                    for (int x : dom[static_cast<size_t>(p)]) {
                        if (new_dom.count(x)) intersect.insert(x);
                    }
                    new_dom = std::move(intersect);
                }
            }
            new_dom.insert(i);
            if (new_dom != dom[static_cast<size_t>(i)]) {
                dom[static_cast<size_t>(i)] = std::move(new_dom);
                changed = true;
            }
        }
    }

    vector<int> idom(sz, 0);
    for (int i = 2; i <= n; ++i) {
        size_t idx = static_cast<size_t>(i);
        for (int d : dom[idx]) {
            if (d != i && dom[idx].size() == dom[static_cast<size_t>(d)].size() + 1) {
                idom[idx] = d;
                break;
            }
        }
    }

    // Dominance Frontier DF(X)
    vector<set<int>> df(sz);
    for (int x = 1; x <= n; ++x) {
        size_t xu = static_cast<size_t>(x);
        for (int y : adj[xu]) {
            if (idom[static_cast<size_t>(y)] != x) {
                df[xu].insert(y);
            }
        }
    }
    for (int x = 1; x <= n; ++x) {
        size_t xu = static_cast<size_t>(x);
        for (int z = 1; z <= n; ++z) {
            if (idom[static_cast<size_t>(z)] == x) {
                for (int y : df[static_cast<size_t>(z)]) {
                    if (idom[static_cast<size_t>(y)] != x) {
                        df[xu].insert(y);
                    }
                }
            }
        }
    }

    // Variable defs
    int def_count;
    cin >> def_count;
    set<int> defs;
    for (int i = 0; i < def_count; ++i) {
        int b;
        cin >> b;
        defs.insert(b);
    }

    // Iterated Dominance Frontier (IDF) for phi placement
    set<int> phi_blocks;
    queue<int> w;
    for (int d : defs) w.push(d);
    while (!w.empty()) {
        int x = w.front();
        w.pop();
        for (int y : df[static_cast<size_t>(x)]) {
            if (!phi_blocks.count(y)) {
                phi_blocks.insert(y);
                if (!defs.count(y)) {
                    w.push(y);
                }
            }
        }
    }

    // Output idom
    for (int i = 2; i <= n; ++i) {
        cout << "idom(" << i << ")=" << idom[static_cast<size_t>(i)] << " ";
    }
    cout << "\n";
    // Output phi nodes
    if (phi_blocks.empty()) {
        cout << "NONE\n";
    } else {
        bool first = true;
        for (int b : phi_blocks) {
            if (!first) cout << " ";
            cout << b;
            first = false;
        }
        cout << "\n";
    }
    return 0;
}
