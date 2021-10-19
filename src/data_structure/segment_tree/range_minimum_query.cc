/*
 * https://www.hackerearth.com/practice/data-structures/advanced-data-structures/segment-trees/tutorial/
 */
#include <bits/stdc++.h>
#define rep(i, l, r) for ((i) = (l); (i) < (r); (i)++)
#define all(x) (x).begin(), (x).end()
using namespace std;

class segment_tree {
 private:
  vector<int> tree;
  vector<int> a;
  void build(int node, int start, int end) {
    if (start == end) {
      tree[node] = a[start];
    } else {
      int mid = (start + end) / 2;
      build(2 * node, start, mid);
      build(2 * node + 1, mid + 1, end);
      tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }
  }
  int rmq(int node, int start, int end, int l, int r) {
    if (start > r || end < l)
      return INT_MAX;
    if (start >= l && end <= r) {
      return tree[node];
    } else {
      int mid = (start + end) / 2;
      int p1 = rmq(node * 2, start, mid, l, r);
      int p2 = rmq(node * 2 + 1, mid + 1, end, l, r);

      return min(p1, p2);
    }

  }

  void update(int start, int end, int node, int index, int value) {
    if (start == end) {
      a[index] = value;
      tree[node] = value;
      return;
    } else {
      int mid = (start + end) / 2;

      if (start <= index && index <= mid)
        update(start, mid, node * 2, index, value);
      else
        update(mid + 1, end, node * 2 + 1, index, value);

      tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
    }
  }
 public:
  segment_tree(const vector<int> &A)
      :
      a(A) {
    int n = static_cast<int>(A.size());
    int height = (int)(ceil(log2(n)));
    int max_size = 2*(int)pow(2, height) - 1;
    tree = vector<int>(max_size);
    build(1, 0, static_cast<int>(A.size()) - 1);
  }

  int q(int l, int r) {
    return rmq(1, 0, static_cast<int>(a.size()) - 1, l, r);
  }
  void u(int index, int value) {
    update(0, static_cast<int>(a.size()) - 1, 1, index, value);
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, q;
  cin >> n >> q;
  vector<int> A(n);
  int i;
  rep(i, 0 , n)
  {
    cin >> A[i];
  }
  segment_tree tree(A);

  rep(i, 0, q)
  {
    string type;
    int x, y;
    cin >> type >> x >> y;
    if (type == "q") {
      cout << tree.q(x - 1, y - 1) << endl;
    } else if (type == "u") {
      tree.u(x - 1, y);
    }
  }
  return 0;
}
