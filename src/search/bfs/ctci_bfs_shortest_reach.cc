// https://www.hackerrank.com/challenges/ctci-bfs-shortest-reach/problem
#include <bits/stdc++.h>

using namespace std;

class Graph {
 private:
  vector<vector<int> > adj;
 public:
  Graph(int n)
      :
      adj(vector<vector<int>>(n)) {
  }
  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  vector<int> shortest_reach(int start) {
    vector<int> dist(adj.size(), -1);
    dist[start] = 0;
    queue<int> q;
    q.push(start);
    while (!q.empty()) {
      int current = q.front();
      q.pop();
      for (int c : adj[current]) {
        int new_dist = dist[current] + 6;
        if (dist[c] == -1 || new_dist < dist[c]) {
          dist[c] = new_dist;
          q.push(c);
        }
      }
    }
    return dist;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int queries;
  cin >> queries;

  for (int t = 0; t < queries; t++) {

    int n, m;
    cin >> n;
    // Create a graph of size n where each edge weight is 6:
    Graph graph(n);
    cin >> m;
    // read and set edges
    for (int i = 0; i < m; i++) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      // add each edge to the graph
      graph.add_edge(u, v);
    }
    int startId;
    cin >> startId;
    startId--;
    // Find shortest reach from node s
    vector<int> distances = graph.shortest_reach(startId);

    for (long long i = 0; i < static_cast<long long>(distances.size()); i++) {
      if (i != startId) {
        cout << distances[i];
        if (i != (static_cast<long long>(distances.size()) - 1))
          cout << " ";
      }
    }
    cout << endl;
  }

  return 0;
}
