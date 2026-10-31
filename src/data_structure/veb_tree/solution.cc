#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class VEBTree {
    int u;
    int lower_sqrt;
    int upper_sqrt;
    int min_val;
    int max_val;
    unique_ptr<VEBTree> summary;
    vector<unique_ptr<VEBTree>> cluster;

    static int log2_pow2(int n) {
        int k = 0;
        while ((1 << k) < n) {
            ++k;
        }
        return k;
    }

    int high(int x) const {
        return x / lower_sqrt;
    }

    int low(int x) const {
        return x % lower_sqrt;
    }

    int index(int h, int l) const {
        return h * lower_sqrt + l;
    }

    void empty_insert(int x) {
        min_val = x;
        max_val = x;
    }

public:
    explicit VEBTree(int universe)
        : u(universe),
          lower_sqrt(1),
          upper_sqrt(1),
          min_val(-1),
          max_val(-1),
          summary(nullptr),
          cluster() {
        int k = log2_pow2(u);
        int lower_k = k / 2;
        int upper_k = k - lower_k;
        lower_sqrt = 1 << lower_k;
        upper_sqrt = 1 << upper_k;
        if (u > 2) {
            summary.reset(new VEBTree(upper_sqrt));
            cluster.resize(static_cast<size_t>(upper_sqrt));
            for (int i = 0; i < upper_sqrt; ++i) {
                cluster[static_cast<size_t>(i)].reset(new VEBTree(lower_sqrt));
            }
        }
    }

    int minimum() const {
        return min_val;
    }

    int maximum() const {
        return max_val;
    }

    bool member(int x) const {
        if (x < 0 || x >= u) {
            return false;
        }
        if (x == min_val || x == max_val) {
            return true;
        }
        if (u == 2) {
            return false;
        }
        return cluster[static_cast<size_t>(high(x))]->member(low(x));
    }

    void insert(int x) {
        if (x < 0 || x >= u) {
            return;
        }
        if (min_val == -1) {
            empty_insert(x);
            return;
        }
        if (x == min_val || x == max_val) {
            return;
        }
        if (x < min_val) {
            swap(x, min_val);
        }
        if (u > 2) {
            int h = high(x);
            int l = low(x);
            VEBTree* c = cluster[static_cast<size_t>(h)].get();
            if (c->minimum() == -1) {
                summary->insert(h);
                c->empty_insert(l);
            } else {
                c->insert(l);
            }
        }
        if (x > max_val) {
            max_val = x;
        }
    }

    void remove(int x) {
        if (!member(x)) {
            return;
        }
        remove_present(x);
    }

private:
    void remove_present(int x) {
        if (min_val == max_val) {
            min_val = -1;
            max_val = -1;
            return;
        }
        if (u == 2) {
            min_val = (x == 0) ? 1 : 0;
            max_val = min_val;
            return;
        }
        if (x == min_val) {
            int first_cluster = summary->minimum();
            x = index(
                first_cluster,
                cluster[static_cast<size_t>(first_cluster)]->minimum()
            );
            min_val = x;
        }
        int h = high(x);
        int l = low(x);
        VEBTree* c = cluster[static_cast<size_t>(h)].get();
        c->remove_present(l);
        if (c->minimum() == -1) {
            summary->remove_present(h);
            if (x == max_val) {
                int summary_max = summary->maximum();
                if (summary_max == -1) {
                    max_val = min_val;
                } else {
                    max_val = index(
                        summary_max,
                        cluster[static_cast<size_t>(summary_max)]->maximum()
                    );
                }
            }
        } else if (x == max_val) {
            max_val = index(h, c->maximum());
        }
    }

public:
    int successor(int x) const {
        if (min_val == -1 || x >= max_val) {
            return -1;
        }
        if (x < min_val) {
            return min_val;
        }
        if (u == 2) {
            if (x == 0 && max_val == 1) {
                return 1;
            }
            return -1;
        }
        int h = high(x);
        int l = low(x);
        const VEBTree* c = cluster[static_cast<size_t>(h)].get();
        int max_low = c->maximum();
        if (max_low != -1 && l < max_low) {
            int offset = c->successor(l);
            return index(h, offset);
        }
        int succ_cluster = summary->successor(h);
        if (succ_cluster == -1) {
            return -1;
        }
        int offset = cluster[static_cast<size_t>(succ_cluster)]->minimum();
        return index(succ_cluster, offset);
    }

    int predecessor(int x) const {
        if (min_val == -1 || x <= min_val) {
            return -1;
        }
        if (x > max_val) {
            return max_val;
        }
        if (u == 2) {
            if (x == 1 && min_val == 0) {
                return 0;
            }
            return -1;
        }
        int h = high(x);
        int l = low(x);
        const VEBTree* c = cluster[static_cast<size_t>(h)].get();
        int min_low = c->minimum();
        if (min_low != -1 && l > min_low) {
            int offset = c->predecessor(l);
            return index(h, offset);
        }
        int pred_cluster = summary->predecessor(h);
        if (pred_cluster == -1) {
            if (min_val != -1 && x > min_val) {
                return min_val;
            }
            return -1;
        }
        int offset = cluster[static_cast<size_t>(pred_cluster)]->maximum();
        return index(pred_cluster, offset);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int u = 0;
    int q = 0;
    if (!(cin >> u >> q)) {
        return 0;
    }

    VEBTree tree(u);
    for (int i = 0; i < q; ++i) {
        int type = 0;
        cin >> type;
        if (type == 1) {
            int x = 0;
            cin >> x;
            tree.insert(x);
        } else if (type == 2) {
            int x = 0;
            cin >> x;
            tree.remove(x);
        } else if (type == 3) {
            int x = 0;
            cin >> x;
            cout << (tree.member(x) ? 1 : 0) << "\n";
        } else if (type == 4) {
            int x = 0;
            cin >> x;
            cout << tree.successor(x) << "\n";
        } else if (type == 5) {
            int x = 0;
            cin >> x;
            cout << tree.predecessor(x) << "\n";
        } else if (type == 6) {
            cout << tree.minimum() << " " << tree.maximum() << "\n";
        }
    }

    return 0;
}
