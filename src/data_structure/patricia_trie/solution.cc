#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <string>

using namespace std;

struct RadixNode {
    string edge;
    bool has_val = false;
    int64_t val = 0;
    int64_t sub_count = 0;
    map<char, unique_ptr<RadixNode>> children;

    explicit RadixNode(const string& e) : edge(e) {}
};

class PatriciaTrie {
    unique_ptr<RadixNode> root;

    static size_t lcp_len(const string& a, const string& b) {
        size_t n = min(a.size(), b.size());
        size_t i = 0;
        while (i < n && a[i] == b[i]) {
            ++i;
        }
        return i;
    }

    static void update_count(RadixNode* u) {
        int64_t cnt = u->has_val ? 1 : 0;
        for (const auto& kv : u->children) {
            cnt += kv.second->sub_count;
        }
        u->sub_count = cnt;
    }

    static void insert_rec(RadixNode* u, const string& rem, int64_t val) {
        if (rem.empty()) {
            u->has_val = true;
            u->val = val;
            update_count(u);
            return;
        }
        char c = rem[0];
        auto it = u->children.find(c);
        if (it == u->children.end()) {
            auto leaf = make_unique<RadixNode>(rem);
            leaf->has_val = true;
            leaf->val = val;
            leaf->sub_count = 1;
            u->children[c] = move(leaf);
            update_count(u);
            return;
        }

        RadixNode* v = it->second.get();
        size_t k = lcp_len(rem, v->edge);
        if (k == v->edge.size()) {
            insert_rec(v, rem.substr(k), val);
            update_count(u);
            return;
        }

        auto mid = make_unique<RadixNode>(v->edge.substr(0, k));
        unique_ptr<RadixNode> old_v = move(it->second);
        old_v->edge = old_v->edge.substr(k);
        char old_c = old_v->edge[0];
        mid->children[old_c] = move(old_v);

        if (k == rem.size()) {
            mid->has_val = true;
            mid->val = val;
        } else {
            string leaf_edge = rem.substr(k);
            auto leaf = make_unique<RadixNode>(leaf_edge);
            leaf->has_val = true;
            leaf->val = val;
            leaf->sub_count = 1;
            mid->children[leaf_edge[0]] = move(leaf);
        }

        update_count(mid.get());
        it->second = move(mid);
        update_count(u);
    }

    static void erase_rec(RadixNode* u, const string& rem) {
        if (rem.empty()) {
            if (!u->has_val) return;
            u->has_val = false;
            update_count(u);
            return;
        }
        char c = rem[0];
        auto it = u->children.find(c);
        if (it == u->children.end()) return;

        RadixNode* v = it->second.get();
        size_t k = lcp_len(rem, v->edge);
        if (k < v->edge.size()) return;

        erase_rec(v, rem.substr(k));

        if (!v->has_val && v->children.empty()) {
            u->children.erase(it);
        } else if (!v->has_val && v->children.size() == 1) {
            auto child_it = v->children.begin();
            unique_ptr<RadixNode> grandchild = move(child_it->second);
            grandchild->edge = v->edge + grandchild->edge;
            it->second = move(grandchild);
        }
        update_count(u);
    }

public:
    PatriciaTrie() : root(make_unique<RadixNode>("")) {}

    void insert(const string& word, int64_t val) {
        insert_rec(root.get(), word, val);
    }

    void erase(const string& word) {
        erase_rec(root.get(), word);
    }

    bool search(const string& word, int64_t& out_val) const {
        const RadixNode* u = root.get();
        string rem = word;
        while (!rem.empty()) {
            auto it = u->children.find(rem[0]);
            if (it == u->children.end()) return false;
            const RadixNode* v = it->second.get();
            size_t k = lcp_len(rem, v->edge);
            if (k < v->edge.size()) return false;
            rem = rem.substr(k);
            u = v;
        }
        if (!u->has_val) return false;
        out_val = u->val;
        return true;
    }

    int64_t count_prefix(const string& prefix) const {
        const RadixNode* u = root.get();
        string rem = prefix;
        while (!rem.empty()) {
            auto it = u->children.find(rem[0]);
            if (it == u->children.end()) return 0;
            const RadixNode* v = it->second.get();
            size_t k = lcp_len(rem, v->edge);
            if (k == rem.size()) {
                return v->sub_count;
            }
            if (k < v->edge.size()) {
                return 0;
            }
            rem = rem.substr(k);
            u = v;
        }
        return u->sub_count;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q = 0;
    if (!(cin >> q)) return 0;

    PatriciaTrie trie;
    for (int i = 0; i < q; ++i) {
        int type = 0;
        string word;
        cin >> type >> word;
        if (type == 1) {
            int64_t val = 0;
            cin >> val;
            trie.insert(word, val);
        } else if (type == 2) {
            trie.erase(word);
        } else if (type == 3) {
            int64_t val = 0;
            if (trie.search(word, val)) {
                cout << val << "\n";
            } else {
                cout << "NOT_FOUND\n";
            }
        } else if (type == 4) {
            cout << trie.count_prefix(word) << "\n";
        }
    }

    return 0;
}
