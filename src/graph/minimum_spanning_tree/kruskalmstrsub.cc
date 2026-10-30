//https://www.hackerrank.com/challenges/kruskalmstrsub/problem
#include <bits/stdc++.h>
#define rep(i, l, r) for ((i) = (l); (i) < (r); (i)++)
#define all(x) (x).begin(), (x).end()
using namespace std;

class disjoint_set {
 private:
  int n;
  vector<vector<long> > nodes;
 public:
  disjoint_set(int s)
      :
      n(s) {
    this->nodes = vector<vector<long> >(s, vector<long>(3));
    for (int i = 0; i < s; ++i) {
      this->make_set(i);
    }
  }
  void make_set(int index) {
    this->nodes[index] = { index, index, 1L };
  }
  int find(int index) {
    if (this->nodes[index][1] == index) {
      return index;
    } else {
      this->nodes[index][1] = this->find(static_cast<int>(this->nodes[index][1]));
      return static_cast<int>(this->nodes[index][1]);
    }
  }
  void union_set(int x, int y) {
    int x_root = this->find(x);
    int y_root = this->find(y);
    if (this->nodes[x_root][2] > this->nodes[y_root][2]) {
      this->nodes[y_root][1] = x_root;
      this->nodes[x_root][2] = this->nodes[x_root][2] + this->nodes[y_root][2];
    } else if (this->nodes[x_root][2] < this->nodes[y_root][2]) {
      this->nodes[x_root][1] = y_root;
      this->nodes[y_root][2] = this->nodes[x_root][2] + this->nodes[y_root][2];
    } else if (x_root != y_root) {
      this->nodes[y_root][1] = x_root;
      this->nodes[x_root][2] = this->nodes[x_root][2] + this->nodes[y_root][2];
    }
  }
  vector<int> get_roots() {
    vector<bool> is_roots(this->n, false);
    for (int node = 0; node < this->n; ++node) {
      int root = this->find(node);
      is_roots[root] = true;
    }
    vector<int> roots;
    for (int i = 0; i < this->n; ++i) {
      if (is_roots[i]) {
        roots.push_back(i);
      }
    }
    return roots;
  }
  long get_rank(int node_index) {
    long rank = this->nodes[node_index][2];
    cout << "rank of " << node_index << " is " << rank << endl;
    return rank;
  }
};

bool compare_edge(const vector<int> &lhs, const vector<int> &rhs) {
  return (lhs[2] < rhs[2]);
}

int kruskals(int g_nodes, const vector<int> &g_from, const vector<int> &g_to,
             const vector<int> &g_weight) {
  disjoint_set d_set(g_nodes);
  vector<vector<int> > edges;
  int nb_edges = static_cast<int>(g_from.size());
  for (int i = 0; i < nb_edges; ++i) {
    vector<int> edge = { g_from[i], g_to[i], g_weight[i] };
    edges.push_back(edge);
  }
  sort(edges.begin(), edges.end(), compare_edge);
  vector<vector<int> > min_spanning;
  for (vector<int> edge : edges) {
    int x = edge[0] - 1;
    int y = edge[1] - 1;
    if (d_set.find(x) != d_set.find(y)) {
      min_spanning.push_back(edge);
      d_set.union_set(x, y);
    }
  }
  int min_weight = 0;
  for (vector<int> edge : min_spanning) {
    min_weight += edge[2];
  }
  return min_weight;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int g_nodes, g_edges;
  vector<int> g_from;
  vector<int> g_to;
  vector<int> g_weight;
  cin >> g_nodes >> g_edges;
  int i;
  rep(i,0, g_edges)
  {
    int from, to, weight;
    cin >> from >> to >> weight;
    g_from.push_back(from);
    g_to.push_back(to);
    g_weight.push_back(weight);
  }
  cout << kruskals(g_nodes, g_from, g_to, g_weight) << endl;
  return 0;
}
