//https://www.hackerearth.com/practice/algorithms/graphs/strongly-connected-components/tutorial/
#include <bits/stdc++.h>
#define rep(i, l, r) for ((i) = (l); (i) < (r); (i)++)
#define all(x) (x).begin(), (x).end()
using namespace std;

class dfs_order {
 private:
  vector<vector<int> > graph;
  vector<bool> marked;
  stack<int> reverse_post;
  void reverse(const vector<vector<int> > &g) {
    graph = vector<vector<int>>(g.size());
    for (int v = 0; v < static_cast<int>(g.size()); ++v) {
      for (int w : g[v]) {
        graph[w].push_back(v);
      }
    }
  }
  void dfs(int v) {
    marked[v] = true;
    for (int w : graph[v]) {
      if (!marked[w])
        dfs(w);
    }
    reverse_post.push(v);
  }
 public:
  dfs_order(vector<vector<int> > g)
      :
      marked(vector<bool>(g.size(), false)) {
    reverse(g);
    for (int v = 0; v < static_cast<int>(graph.size()); ++v) {
      if (!marked[v])
        dfs(v);
    }
  }
  stack<int> reverse_post_order() {
    return this->reverse_post;
  }
};

class kosaraju {
 private:
  int n;
  vector<vector<int> > graph;
  vector<bool> marked;
  vector<int> components;
  int count;
 public:
  kosaraju(int s)
      :
      n(s),
      graph(vector<vector<int> >(s)),
      marked(vector<bool>(s, false)),
      components(vector<int>(s, -1)),
      count(0) {

  }
  void add(int a, int b) {
    graph[a].push_back(b);
  }
  void scc() {
    dfs_order order(graph);
    stack<int> s = order.reverse_post_order();
    while (!s.empty()) {
      int c = s.top();
      s.pop();
      if (!marked[c]) {
        dfs(c);
        ++count;
      }
    }
  }
  void dfs(int c) {
    marked[c] = true;
    components[c] = count;
    for (int w : graph[c]) {
      if (!marked[w])
        dfs(w);
    }
  }
  vector<int> node_count() {
    vector<int> node_counts(count + 1, 0);
    for (int c : components) {
      ++node_counts[c];
    }
    return node_counts;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  kosaraju algo(n);
  for (int a, b; cin >> a >> b;) {
    algo.add(a - 1, b - 1);
  }
  algo.scc();
  int odd = 0;
  int even = 0;
  for (int c : algo.node_count()) {
    if (c % 2 != 0) {
      odd += c;
    } else {
      even += c;
    }
  }
  cout << odd - even << endl;
  return 0;
}
