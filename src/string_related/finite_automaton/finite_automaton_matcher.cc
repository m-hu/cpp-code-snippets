#include <iostream>
#include <string>
#include <vector>

namespace {

std::vector<std::vector<size_t>> compute_transition_function(const std::string& pattern) {
    size_t m = pattern.size();
    std::vector<std::vector<size_t>> delta(m + 1, std::vector<size_t>(26, 0));
    std::vector<size_t> pi(m, 0);
    for (size_t i = 1; i < m; ++i) {
        size_t j = pi[i - 1];
        while (j > 0 && pattern[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            ++j;
        }
        pi[i] = j;
    }
    for (size_t q = 0; q <= m; ++q) {
        for (size_t c = 0; c < 26; ++c) {
            char ch = static_cast<char>('a' + c);
            if (q < m && pattern[q] == ch) {
                delta[q][c] = q + 1;
            } else if (q == 0) {
                delta[q][c] = 0;
            } else {
                delta[q][c] = delta[pi[q - 1]][c];
            }
        }
    }
    return delta;
}

std::vector<size_t> finite_automaton_matcher(const std::string& pattern, const std::string& text) {
    size_t m = pattern.size();
    size_t n = text.size();
    std::vector<std::vector<size_t>> delta = compute_transition_function(pattern);
    std::vector<size_t> matches;
    size_t q = 0;
    for (size_t i = 0; i < n; ++i) {
        size_t c = static_cast<size_t>(text[i] - 'a');
        q = delta[q][c];
        if (q == m) {
            matches.push_back(i + 1 - m);
        }
    }
    return matches;
}

}  // namespace

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int q = 0;
    if (!(std::cin >> q)) {
        return 0;
    }
    for (int i = 0; i < q; ++i) {
        std::string pattern;
        std::string text;
        std::cin >> pattern >> text;
        std::vector<size_t> matches = finite_automaton_matcher(pattern, text);
        if (matches.empty()) {
            std::cout << -1 << "\n";
        } else {
            for (size_t j = 0; j < matches.size(); ++j) {
                if (j > 0) {
                    std::cout << " ";
                }
                std::cout << matches[j];
            }
            std::cout << "\n";
        }
    }
    return 0;
}
