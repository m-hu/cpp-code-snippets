#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    int rev;
    long long cap;
    long long flow;
};

class PushRelabel {
    int n;
    int s, t;
    vector<vector<Edge>> adj;
    vector<long long> excess;
    vector<int> height;
    vector<int> count;
    vector<bool> in_queue;
    queue<int> active_q;

public:
    PushRelabel(int n_nodes, int src, int snk)
        : n(n_nodes), s(src), t(snk),
          adj(static_cast<size_t>(n_nodes)),
          excess(static_cast<size_t>(n_nodes), 0),
          height(static_cast<size_t>(n_nodes), 0),
          count(static_cast<size_t>(2 * n_nodes), 0),
          in_queue(static_cast<size_t>(n_nodes), false) {}

    void add_edge(int from, int to, long long cap) {
        adj[static_cast<size_t>(from)].push_back({to, static_cast<int>(adj[static_cast<size_t>(to)].size()), cap, 0});
        adj[static_cast<size_t>(to)].push_back({from, static_cast<int>(adj[static_cast<size_t>(from)].size()) - 1, 0, 0});
    }

    void enqueue(int u) {
        if (!in_queue[static_cast<size_t>(u)] && u != s && u != t && excess[static_cast<size_t>(u)] > 0) {
            in_queue[static_cast<size_t>(u)] = true;
            active_q.push(u);
        }
    }

    void push(int u, Edge& edge) {
        long long amt = min(excess[static_cast<size_t>(u)], edge.cap - edge.flow);
        if (amt == 0 || height[static_cast<size_t>(u)] != height[static_cast<size_t>(edge.to)] + 1) return;

        edge.flow += amt;
        adj[static_cast<size_t>(edge.to)][static_cast<size_t>(edge.rev)].flow -= amt;
        excess[static_cast<size_t>(u)] -= amt;
        excess[static_cast<size_t>(edge.to)] += amt;
        enqueue(edge.to);
    }

    void relabel(int u) {
        int min_h = 2 * n;
        for (const auto& edge : adj[static_cast<size_t>(u)]) {
            if (edge.cap - edge.flow > 0) {
                min_h = min(min_h, height[static_cast<size_t>(edge.to)]);
            }
        }
        if (min_h < 2 * n) {
            int old_h = height[static_cast<size_t>(u)];
            --count[static_cast<size_t>(old_h)];
            height[static_cast<size_t>(u)] = min_h + 1;
            ++count[static_cast<size_t>(height[static_cast<size_t>(u)])];
        }
    }

    void discharge(int u) {
        size_t idx = 0;
        while (excess[static_cast<size_t>(u)] > 0) {
            if (idx < adj[static_cast<size_t>(u)].size()) {
                Edge& edge = adj[static_cast<size_t>(u)][idx];
                if (edge.cap - edge.flow > 0 && height[static_cast<size_t>(u)] == height[static_cast<size_t>(edge.to)] + 1) {
                    push(u, edge);
                } else {
                    ++idx;
                }
            } else {
                relabel(u);
                idx = 0;
            }
        }
    }

    long long max_flow() {
        height[static_cast<size_t>(s)] = n;
        count[static_cast<size_t>(n)] = 1;
        count[0] = n - 1;

        for (auto& edge : adj[static_cast<size_t>(s)]) {
            long long amt = edge.cap;
            if (amt > 0) {
                edge.flow += amt;
                adj[static_cast<size_t>(edge.to)][static_cast<size_t>(edge.rev)].flow -= amt;
                excess[static_cast<size_t>(edge.to)] += amt;
                excess[static_cast<size_t>(s)] -= amt;
                enqueue(edge.to);
            }
        }

        while (!active_q.empty()) {
            int u = active_q.front();
            active_q.pop();
            in_queue[static_cast<size_t>(u)] = false;
            discharge(u);
        }

        return excess[static_cast<size_t>(t)];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0, m = 0, s = 0, t = 0;
    if (!(cin >> n >> m >> s >> t)) return 0;

    PushRelabel pr(n, s, t);
    for (int i = 0; i < m; ++i) {
        int u = 0, v = 0;
        long long cap = 0;
        cin >> u >> v >> cap;
        pr.add_edge(u, v, cap);
    }

    cout << pr.max_flow() << "\n";

    return 0;
}
