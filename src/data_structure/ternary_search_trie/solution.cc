#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct TSTNode {
    char ch;
    bool has_val = false;
    int64_t val = 0;
    int left = -1;
    int mid = -1;
    int right = -1;

    explicit TSTNode(char c) : ch(c) {}
};

class TernarySearchTrie {
    vector<TSTNode> nodes;
    int root = -1;

    int put(int u, const string& key, int64_t val, size_t d) {
        char c = key[d];
        if (u == -1) {
            u = static_cast<int>(nodes.size());
            nodes.emplace_back(c);
        }
        if (c < nodes[static_cast<size_t>(u)].ch) {
            int l = put(nodes[static_cast<size_t>(u)].left, key, val, d);
            nodes[static_cast<size_t>(u)].left = l;
        } else if (c > nodes[static_cast<size_t>(u)].ch) {
            int r = put(nodes[static_cast<size_t>(u)].right, key, val, d);
            nodes[static_cast<size_t>(u)].right = r;
        } else if (d + 1 < key.size()) {
            int m = put(nodes[static_cast<size_t>(u)].mid, key, val, d + 1);
            nodes[static_cast<size_t>(u)].mid = m;
        } else {
            nodes[static_cast<size_t>(u)].has_val = true;
            nodes[static_cast<size_t>(u)].val = val;
        }
        return u;
    }

    int get_node(int u, const string& key, size_t d) const {
        while (u != -1) {
            char c = key[d];
            const TSTNode& node = nodes[static_cast<size_t>(u)];
            if (c < node.ch) {
                u = node.left;
            } else if (c > node.ch) {
                u = node.right;
            } else if (d + 1 < key.size()) {
                u = node.mid;
                ++d;
            } else {
                return u;
            }
        }
        return -1;
    }

    void collect(int u, string& prefix, vector<string>& res) const {
        if (u == -1) return;
        const TSTNode& node = nodes[static_cast<size_t>(u)];
        collect(node.left, prefix, res);
        prefix.push_back(node.ch);
        if (node.has_val) {
            res.push_back(prefix);
        }
        collect(node.mid, prefix, res);
        prefix.pop_back();
        collect(node.right, prefix, res);
    }

    void collect_match(int u, string& prefix, size_t d, const string& pat, vector<string>& res) const {
        if (u == -1) return;
        const TSTNode& node = nodes[static_cast<size_t>(u)];
        char c = pat[d];
        if (c == '.' || c < node.ch) {
            collect_match(node.left, prefix, d, pat, res);
        }
        if (c == '.' || c == node.ch) {
            prefix.push_back(node.ch);
            if (d + 1 == pat.size()) {
                if (node.has_val) {
                    res.push_back(prefix);
                }
            } else {
                collect_match(node.mid, prefix, d + 1, pat, res);
            }
            prefix.pop_back();
        }
        if (c == '.' || c > node.ch) {
            collect_match(node.right, prefix, d, pat, res);
        }
    }

public:
    void insert(const string& key, int64_t val) {
        if (key.empty()) return;
        root = put(root, key, val, 0);
    }

    bool search(const string& key, int64_t& out_val) const {
        if (key.empty()) return false;
        int u = get_node(root, key, 0);
        if (u == -1 || !nodes[static_cast<size_t>(u)].has_val) return false;
        out_val = nodes[static_cast<size_t>(u)].val;
        return true;
    }

    vector<string> keys_with_prefix(const string& prefix) const {
        vector<string> res;
        if (prefix.empty()) return res;
        int u = get_node(root, prefix, 0);
        if (u == -1) return res;
        if (nodes[static_cast<size_t>(u)].has_val) {
            res.push_back(prefix);
        }
        string cur = prefix;
        collect(nodes[static_cast<size_t>(u)].mid, cur, res);
        return res;
    }

    string longest_prefix_of(const string& query) const {
        if (query.empty()) return "";
        int u = root;
        size_t d = 0;
        size_t best_len = 0;
        bool found = false;
        while (u != -1 && d < query.size()) {
            char c = query[d];
            const TSTNode& node = nodes[static_cast<size_t>(u)];
            if (c < node.ch) {
                u = node.left;
            } else if (c > node.ch) {
                u = node.right;
            } else {
                ++d;
                if (node.has_val) {
                    best_len = d;
                    found = true;
                }
                u = node.mid;
            }
        }
        if (!found) return "";
        return query.substr(0, best_len);
    }

    vector<string> keys_that_match(const string& pat) const {
        vector<string> res;
        if (pat.empty()) return res;
        string cur;
        collect_match(root, cur, 0, pat, res);
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0;
    int q = 0;
    if (!(cin >> n >> q)) return 0;

    TernarySearchTrie tst;
    for (int i = 0; i < n; ++i) {
        string word;
        int64_t val = 0;
        cin >> word >> val;
        tst.insert(word, val);
    }

    for (int i = 0; i < q; ++i) {
        int type = 0;
        string arg;
        cin >> type >> arg;
        if (type == 1) {
            int64_t val = 0;
            if (tst.search(arg, val)) {
                cout << val << "\n";
            } else {
                cout << "NOT_FOUND\n";
            }
        } else if (type == 2) {
            vector<string> res = tst.keys_with_prefix(arg);
            if (res.empty()) {
                cout << "NONE\n";
            } else {
                for (size_t j = 0; j < res.size(); ++j) {
                    if (j > 0) cout << " ";
                    cout << res[j];
                }
                cout << "\n";
            }
        } else if (type == 3) {
            string res = tst.longest_prefix_of(arg);
            if (res.empty()) {
                cout << "NONE\n";
            } else {
                cout << res << "\n";
            }
        } else if (type == 4) {
            vector<string> res = tst.keys_that_match(arg);
            if (res.empty()) {
                cout << "NONE\n";
            } else {
                for (size_t j = 0; j < res.size(); ++j) {
                    if (j > 0) cout << " ";
                    cout << res[j];
                }
                cout << "\n";
            }
        }
    }

    return 0;
}
