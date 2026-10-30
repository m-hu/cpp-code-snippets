#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

struct SuffixNode {
    map<char, int> children;
    int suffix_link = -1;
    int start = -1;
    int* end = nullptr;
    int suffix_index = -1;
};

class SuffixTree {
    string text;
    vector<SuffixNode> tree;
    int root = 0;
    int last_new_node = -1;
    int active_node = 0;
    int active_edge = -1;
    int active_length = 0;
    int remaining_suffix_count = 0;
    int leaf_end = -1;
    int* root_end = nullptr;

    int new_node(int start, int* end) {
        SuffixNode node;
        node.suffix_link = root;
        node.start = start;
        node.end = end;
        node.suffix_index = -1;
        tree.push_back(node);
        return static_cast<int>(tree.size()) - 1;
    }

    int edge_length(int n_idx) {
        if (n_idx == root) return 0;
        return *(tree[static_cast<size_t>(n_idx)].end) - tree[static_cast<size_t>(n_idx)].start + 1;
    }

    bool walk_down(int curr_node) {
        int elen = edge_length(curr_node);
        if (active_length >= elen) {
            active_edge += elen;
            active_length -= elen;
            active_node = curr_node;
            return true;
        }
        return false;
    }

    void extend(int pos) {
        leaf_end = pos;
        ++remaining_suffix_count;
        last_new_node = -1;

        while (remaining_suffix_count > 0) {
            if (active_length == 0) {
                active_edge = pos;
            }

            char cur_char = text[static_cast<size_t>(active_edge)];
            auto it = tree[static_cast<size_t>(active_node)].children.find(cur_char);

            if (it == tree[static_cast<size_t>(active_node)].children.end()) {
                // Rule 2 extension from node
                int leaf = new_node(pos, &leaf_end);
                tree[static_cast<size_t>(active_node)].children[cur_char] = leaf;

                if (last_new_node != -1) {
                    tree[static_cast<size_t>(last_new_node)].suffix_link = active_node;
                    last_new_node = -1;
                }
            } else {
                int next_node = it->second;
                if (walk_down(next_node)) {
                    continue; // Start again from current active_node
                }

                // Rule 3: character already on edge
                int edge_char_pos = tree[static_cast<size_t>(next_node)].start + active_length;
                if (text[static_cast<size_t>(edge_char_pos)] == text[static_cast<size_t>(pos)]) {
                    if (last_new_node != -1 && active_node != root) {
                        tree[static_cast<size_t>(last_new_node)].suffix_link = active_node;
                        last_new_node = -1;
                    }
                    ++active_length;
                    break;
                }

                // Rule 2 split
                int* split_end = new int(tree[static_cast<size_t>(next_node)].start + active_length - 1);
                allocated_ends.push_back(split_end);

                int split = new_node(tree[static_cast<size_t>(next_node)].start, split_end);
                tree[static_cast<size_t>(active_node)].children[cur_char] = split;

                int leaf = new_node(pos, &leaf_end);
                tree[static_cast<size_t>(split)].children[text[static_cast<size_t>(pos)]] = leaf;

                tree[static_cast<size_t>(next_node)].start += active_length;
                tree[static_cast<size_t>(split)].children[text[static_cast<size_t>(edge_char_pos)]] = next_node;

                if (last_new_node != -1) {
                    tree[static_cast<size_t>(last_new_node)].suffix_link = split;
                }
                last_new_node = split;
            }

            --remaining_suffix_count;
            if (active_node == root && active_length > 0) {
                --active_length;
                active_edge = pos - remaining_suffix_count + 1;
            } else if (active_node != root) {
                active_node = tree[static_cast<size_t>(active_node)].suffix_link;
            }
        }
    }

    vector<int*> allocated_ends;

public:
    explicit SuffixTree(const string& str) : text(str) {
        root_end = new int(-1);
        allocated_ends.push_back(root_end);
        root = new_node(-1, root_end);
        active_node = root;

        for (size_t i = 0; i < text.size(); ++i) {
            extend(static_cast<int>(i));
        }
    }

    ~SuffixTree() {
        for (int* p : allocated_ends) {
            delete p;
        }
    }

    size_t node_count() const {
        return tree.size();
    }

    long long count_distinct_substrings(int u = 0) {
        long long count = 0;
        for (const auto& kv : tree[static_cast<size_t>(u)].children) {
            int v = kv.second;
            int len = *(tree[static_cast<size_t>(v)].end) - tree[static_cast<size_t>(v)].start + 1;
            // Subtract sentinel character if present
            count += len + count_distinct_substrings(v);
        }
        return count;
    }

    bool find_pattern(const string& pat) {
        int cur = root;
        size_t idx = 0;
        while (idx < pat.size()) {
            char c = pat[idx];
            auto it = tree[static_cast<size_t>(cur)].children.find(c);
            if (it == tree[static_cast<size_t>(cur)].children.end()) return false;
            int nxt = it->second;
            int start = tree[static_cast<size_t>(nxt)].start;
            int end = *(tree[static_cast<size_t>(nxt)].end);
            int len = end - start + 1;

            for (int k = 0; k < len && idx < pat.size(); ++k, ++idx) {
                if (text[static_cast<size_t>(start + k)] != pat[idx]) {
                    return false;
                }
            }
            cur = nxt;
        }
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;

    SuffixTree st(s);
    cout << "Nodes: " << st.node_count() << "\n";
    cout << "Distinct substrings: " << st.count_distinct_substrings() << "\n";

    int num_queries = 0;
    if (cin >> num_queries) {
        for (int q = 0; q < num_queries; ++q) {
            string pat;
            cin >> pat;
            if (st.find_pattern(pat)) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }

    return 0;
}
