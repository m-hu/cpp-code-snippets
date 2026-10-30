#include <iostream>
#include <vector>
#include <string>

using namespace std;

class LazySegmentTree {
    int n;
    vector<long long> tree;
    vector<long long> lazy;

    void build(const vector<long long>& arr, int node, int l, int r) {
        if (l == r) {
            tree[static_cast<size_t>(node)] = arr[static_cast<size_t>(l)];
            return;
        }
        int mid = l + (r - l) / 2;
        build(arr, 2 * node, l, mid);
        build(arr, 2 * node + 1, mid + 1, r);
        tree[static_cast<size_t>(node)] = tree[static_cast<size_t>(2 * node)] + tree[static_cast<size_t>(2 * node + 1)];
    }

    void push_down(int node, int l, int r) {
        if (lazy[static_cast<size_t>(node)] != 0) {
            int mid = l + (r - l) / 2;
            long long val = lazy[static_cast<size_t>(node)];

            tree[static_cast<size_t>(2 * node)] += val * (mid - l + 1);
            lazy[static_cast<size_t>(2 * node)] += val;

            tree[static_cast<size_t>(2 * node + 1)] += val * (r - mid);
            lazy[static_cast<size_t>(2 * node + 1)] += val;

            lazy[static_cast<size_t>(node)] = 0;
        }
    }

public:
    explicit LazySegmentTree(const vector<long long>& arr) : n(static_cast<int>(arr.size())),
        tree(static_cast<size_t>(4 * n), 0), lazy(static_cast<size_t>(4 * n), 0) {
        if (n > 0) build(arr, 1, 0, n - 1);
    }

    void update(int node, int l, int r, int ql, int qr, long long val) {
        if (ql <= l && r <= qr) {
            tree[static_cast<size_t>(node)] += val * (r - l + 1);
            lazy[static_cast<size_t>(node)] += val;
            return;
        }
        push_down(node, l, r);
        int mid = l + (r - l) / 2;
        if (ql <= mid) update(2 * node, l, mid, ql, qr, val);
        if (qr > mid) update(2 * node + 1, mid + 1, r, ql, qr, val);
        tree[static_cast<size_t>(node)] = tree[static_cast<size_t>(2 * node)] + tree[static_cast<size_t>(2 * node + 1)];
    }

    long long query(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return tree[static_cast<size_t>(node)];
        }
        push_down(node, l, r);
        int mid = l + (r - l) / 2;
        long long sum = 0;
        if (ql <= mid) sum += query(2 * node, l, mid, ql, qr);
        if (qr > mid) sum += query(2 * node + 1, mid + 1, r, ql, qr);
        return sum;
    }

    int size() const { return n; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0, q = 0;
    if (!(cin >> n >> q)) return 0;

    vector<long long> arr(static_cast<size_t>(n));
    for (int i = 0; i < n; ++i) {
        cin >> arr[static_cast<size_t>(i)];
    }

    LazySegmentTree seg(arr);
    for (int i = 0; i < q; ++i) {
        string type;
        cin >> type;
        if (type == "UPDATE") {
            int l = 0, r = 0;
            long long val = 0;
            cin >> l >> r >> val;
            seg.update(1, 0, n - 1, l - 1, r - 1, val);
        } else if (type == "QUERY") {
            int l = 0, r = 0;
            cin >> l >> r;
            cout << seg.query(1, 0, n - 1, l - 1, r - 1) << "\n";
        }
    }

    return 0;
}
