#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

struct Edge {
    int to;
    int rev;
    long long cap;
    long long flow;
};

class Dinic {
    int s, t;
    vector<vector<Edge>> adj;
    vector<int> level;
    vector<size_t> ptr;

public:
    Dinic(int n_nodes, int src, int snk) : s(src), t(snk), adj(static_cast<size_t>(n_nodes)),
        level(static_cast<size_t>(n_nodes)), ptr(static_cast<size_t>(n_nodes)) {}

    void add_edge(int from, int to, long long cap) {
        adj[static_cast<size_t>(from)].push_back({to, static_cast<int>(adj[static_cast<size_t>(to)].size()), cap, 0});
        adj[static_cast<size_t>(to)].push_back({from, static_cast<int>(adj[static_cast<size_t>(from)].size()) - 1, 0, 0});
    }

    bool bfs() {
        fill(level.begin(), level.end(), -1);
        level[static_cast<size_t>(s)] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (const auto& edge : adj[static_cast<size_t>(v)]) {
                if (edge.cap - edge.flow > 0 && level[static_cast<size_t>(edge.to)] == -1) {
                    level[static_cast<size_t>(edge.to)] = level[static_cast<size_t>(v)] + 1;
                    q.push(edge.to);
                }
            }
        }
        return level[static_cast<size_t>(t)] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0) return 0;
        if (v == t) return pushed;
        for (size_t& cid = ptr[static_cast<size_t>(v)]; cid < adj[static_cast<size_t>(v)].size(); ++cid) {
            auto& edge = adj[static_cast<size_t>(v)][cid];
            int tr = edge.to;
            if (level[static_cast<size_t>(v)] + 1 != level[static_cast<size_t>(tr)] || edge.cap - edge.flow <= 0) {
                continue;
            }
            long long tr_pushed = dfs(tr, min(pushed, edge.cap - edge.flow));
            if (tr_pushed == 0) continue;
            edge.flow += tr_pushed;
            adj[static_cast<size_t>(tr)][static_cast<size_t>(edge.rev)].flow -= tr_pushed;
            return tr_pushed;
        }
        return 0;
    }

    long long max_flow() {
        long long flow = 0;
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0, m = 0, s = 0, t = 0;
    if (!(cin >> n >> m >> s >> t)) return 0;

    Dinic dinic(n, s, t);
    for (int i = 0; i < m; ++i) {
        int u = 0, v = 0;
        long long cap = 0;
        cin >> u >> v >> cap;
        dinic.add_edge(u, v, cap);
    }

    long long max_f = dinic.max_flow();
    cout << max_f << "\n";

    return 0;
}
