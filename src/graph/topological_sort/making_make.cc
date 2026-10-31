// https://www.hackerrank.com/contests/lab-assignment-2/challenges/making-make
#include <bits/stdc++.h>
#define rep(i, l, r) for ((i) = (l); (i) < (r); (i)++)
#define all(x) (x).begin(), (x).end()
using namespace std;

vector<int> topological_sort(const vector<vector<int> > &graph,
                             vector<int> &indegree) {
  int n = static_cast<int>(graph.size());
  vector<int> ans(n);
  vector<int> order(n);
  /**
   * A priority queue is optional,
   * in case files must be built in a sorted order,
   * a priority could be used
   * */
  priority_queue<int> q;
  int i;
  for (i = n - 1; i >= 0; --i) {
    if (indegree[i] == 0)
      q.push(i);
  }
  int counter = 0;
  while (!q.empty()) {
    int v = q.top();
    q.pop();
    order[v] = counter++;
    for (int w : graph[v]) {
      if (--indegree[w] == 0) {
        q.push(w);
      }
    }
  }
  rep(i, 0, n)
  {
    ans[order[i]] = i;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int v, e;
  cin >> v >> e;
  int i;
  vector<vector<int> > graph(v);
  vector<int> indegree(v, 0);
  rep(i, 0, e)
  {
    int from, to;
    cin >> from >> to;
    graph[from].push_back(to);
    ++indegree[to];
  }
  for (int n : topological_sort(graph, indegree)) {
    cout << n << " ";
  }
  cout << endl;
  return 0;
}
