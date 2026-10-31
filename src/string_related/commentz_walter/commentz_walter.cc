#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

namespace {

struct CWNode {
    int next[26];
    int fail;
    int depth;
    std::vector<size_t> out;

    CWNode(int d) : fail(0), depth(d) {
        for (int i = 0; i < 26; ++i) {
            next[i] = -1;
        }
    }
};

std::vector<std::vector<size_t>> commentz_walter(
    const std::vector<std::string>& patterns, const std::string& text) {
    size_t num_patterns = patterns.size();
    std::vector<std::vector<size_t>> results(num_patterns);
    if (num_patterns == 0 || text.empty()) {
        return results;
    }

    size_t w_min = patterns[0].size();
    for (size_t i = 1; i < num_patterns; ++i) {
        if (patterns[i].size() < w_min) {
            w_min = patterns[i].size();
        }
    }
    if (w_min == 0 || w_min > text.size()) {
        return results;
    }

    std::vector<CWNode> trie;
    trie.emplace_back(0);
    size_t char_min_depth[26];
    for (size_t c = 0; c < 26; ++c) {
        char_min_depth[c] = w_min + 1;
    }

    for (size_t idx = 0; idx < num_patterns; ++idx) {
        const std::string& pat = patterns[idx];
        int u = 0;
        for (size_t k = 0; k < pat.size(); ++k) {
            char ch = pat[pat.size() - 1 - k];
            size_t c = static_cast<size_t>(ch - 'a');
            size_t dep = k + 1;
            if (dep >= 2 && dep < char_min_depth[c]) {
                char_min_depth[c] = dep;
            }
            if (trie[static_cast<size_t>(u)].next[c] == -1) {
                int next_id = static_cast<int>(trie.size());
                trie.emplace_back(static_cast<int>(dep));
                trie[static_cast<size_t>(u)].next[c] = next_id;
            }
            u = trie[static_cast<size_t>(u)].next[c];
        }
        trie[static_cast<size_t>(u)].out.push_back(idx);
    }

    // Build failure links on the reversed trie (Commentz-Walter automaton structure)
    std::queue<int> q;
    for (size_t c = 0; c < 26; ++c) {
        int nxt = trie[0].next[c];
        if (nxt != -1) {
            trie[static_cast<size_t>(nxt)].fail = 0;
            q.push(nxt);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (size_t c = 0; c < 26; ++c) {
            int v = trie[static_cast<size_t>(u)].next[c];
            if (v != -1) {
                int f = trie[static_cast<size_t>(u)].fail;
                while (f > 0 && trie[static_cast<size_t>(f)].next[c] == -1) {
                    f = trie[static_cast<size_t>(f)].fail;
                }
                if (trie[static_cast<size_t>(f)].next[c] != -1) {
                    f = trie[static_cast<size_t>(f)].next[c];
                }
                trie[static_cast<size_t>(v)].fail = f;
                q.push(v);
            }
        }
    }

    size_t n = text.size();
    size_t j = w_min - 1;
    while (j < n) {
        int u = 0;
        size_t pos = j;
        while (true) {
            size_t c = static_cast<size_t>(text[pos] - 'a');
            int nxt = trie[static_cast<size_t>(u)].next[c];
            if (nxt == -1) {
                break;
            }
            u = nxt;
            const std::vector<size_t>& outs = trie[static_cast<size_t>(u)].out;
            for (size_t k = 0; k < outs.size(); ++k) {
                results[outs[k]].push_back(pos);
            }
            if (pos == 0) {
                break;
            }
            --pos;
        }
        size_t c_right = static_cast<size_t>(text[j] - 'a');
        size_t shift = char_min_depth[c_right] - 1;
        if (shift < 1) {
            shift = 1;
        }
        j += shift;
    }

    return results;
}

}  // namespace

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    size_t n = 0;
    if (!(std::cin >> n)) {
        return 0;
    }
    std::vector<std::string> patterns(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> patterns[i];
    }
    std::string text;
    std::cin >> text;
    std::vector<std::vector<size_t>> res = commentz_walter(patterns, text);
    for (size_t i = 0; i < n; ++i) {
        if (res[i].empty()) {
            std::cout << -1 << "\n";
        } else {
            for (size_t j = 0; j < res[i].size(); ++j) {
                if (j > 0) {
                    std::cout << " ";
                }
                std::cout << res[i][j];
            }
            std::cout << "\n";
        }
    }
    return 0;
}
