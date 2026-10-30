// https://www.hackerrank.com/challenges/even-tree/problem
#include <iostream>
#include <vector>

using namespace std;

int cuts = 0;

int dfs(int u, int parent, const vector<vector<int>>& adj) {
    int subtree_size = 1;
    for (int v : adj[u]) {
        if (v != parent) {
            subtree_size += dfs(v, u, adj);
        }
    }
    if (subtree_size % 2 == 0 && parent != 0) {
        cuts++;
    }
    return subtree_size;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cuts = 0;
    dfs(1, 0, adj);

    cout << cuts << "\n";
    return 0;
}
