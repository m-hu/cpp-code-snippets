//https://www.hackerrank.com/contests/data-structure-tasks-binary-tree-union-find/challenges/connected-component/problem
#include <bits/stdc++.h>
#define rep(i, l, r) for ((i) = (l); (i) < (r); (i)++)
#define all(x) (x).begin(), (x).end()
using namespace std;

class disjoint_set {
 private:
  int n;
  vector<long> nodes;
  int root_number;
 public:
  disjoint_set(int s)
      :
      n(s),
      root_number(s) {
    this->nodes = vector<long>(s);
    for (int i = 0; i < s; ++i) {
      this->make_set(i);
    }
  }
  void make_set(int index) {
    this->nodes[index] = index;
  }
  int find(int index) {
    if (this->nodes[index] == index) {
      return index;
    } else {
      this->nodes[index] = this->find(static_cast<int>(this->nodes[index]));
      return static_cast<int>(this->nodes[index]);
    }
  }
  bool union_set(int x, int y) {
    int x_root = this->find(x);
    int y_root = this->find(y);
    if (x_root != y_root) {
      this->nodes[y_root] = x_root;
      --this->root_number;
    }
    return x_root == y_root;
  }
  int get_root_number() {
    return root_number;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  disjoint_set s(n);
  vector<bool> connected(n, false);
  for (int u, v; cin >> u && cin >> v;) {
    u = u - 1;
    v = v - 1;
    bool cycled = s.union_set(u, v);
    cout << s.get_root_number();
    if (cycled) {
      cout << " CYCLE FORMED!";
    }
    cout << endl;
  }
  return 0;
}
