//https://www.hackerrank.com/challenges/dijkstrashortreach/problem
#include <bits/stdc++.h>
#define rep(i, l, r) for ((i) = (l); (i) < (r); (i)++)
#define all(x) (x).begin(), (x).end()
using namespace std;

vector<int> dijkstra(const vector<vector<pair<int, int>>> &graph, int s) {
  int n = static_cast<int>(graph.size());
  vector<int> dist(n, -1);
  dist[s] = 0;
  /** 
   * set itself is already a sorted data structure 
   * with the same insertion and reading complexity 
   * as a priority queue
   * */
  set<pair<int, int>> q;
  q.insert( { 0, s });
  while (!q.empty()) {
    int v, c;
    tie(c, v) = *(q.begin());
    q.erase(q.begin());
    for (pair<int, int> w : graph[v]) {
      int new_dist = dist[v] + w.second;
      if (dist[w.first] == -1) {
        dist[w.first] = new_dist;
        q.insert( { new_dist, w.first });
      } else if (new_dist < dist[w.first]) {
        /**
         * update the priority
         */
        q.erase(q.find( { dist[w.first], w.first }));
        dist[w.first] = new_dist;
        q.insert( { new_dist, w.first });
      }
    }
  }
  return dist;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  int i;
  rep(i, 0 , t)
  {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> graph(n);
    int j;
    rep(j, 0, m)
    {
      int x, y, r;
      cin >> x >> y >> r;
      graph[x - 1].push_back( { y - 1, r });
      graph[y - 1].push_back( { x - 1, r });
    }
    int s;
    cin >> s;
    j = 0;
    for (int w : dijkstra(graph, s - 1)) {
      if (j != (s - 1))
        cout << w << " ";
      ++j;
    }
    cout << endl;
  }
  return 0;
}
