#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace {

std::vector<size_t> shift_and_bitap_k_mismatch(
    size_t k, const std::string& pattern, const std::string& text) {
    size_t m = pattern.size();
    size_t n = text.size();
    std::vector<size_t> matches;
    if (m == 0 || m > n) {
        return matches;
    }
    uint64_t mask_all = (m == 64) ? ~uint64_t(0) : ((uint64_t(1) << m) - 1);
    uint64_t char_mask[26];
    for (size_t c = 0; c < 26; ++c) {
        char_mask[c] = 0;
    }
    for (size_t i = 0; i < m; ++i) {
        size_t c = static_cast<size_t>(pattern[i] - 'a');
        char_mask[c] |= (uint64_t(1) << i);
    }

    std::vector<uint64_t> r(k + 1, 0);
    uint64_t accept_bit = uint64_t(1) << (m - 1);

    for (size_t j = 0; j < n; ++j) {
        size_t c = static_cast<size_t>(text[j] - 'a');
        uint64_t bc = char_mask[c];
        uint64_t prev_shifted = ((r[0] << 1) | uint64_t(1)) & mask_all;
        r[0] = prev_shifted & bc;
        for (size_t d = 1; d <= k; ++d) {
            uint64_t cur_shifted = ((r[d] << 1) | uint64_t(1)) & mask_all;
            r[d] = (cur_shifted & bc) | prev_shifted;
            prev_shifted = cur_shifted;
        }
        if (j + 1 >= m && (r[k] & accept_bit) != 0) {
            matches.push_back(j + 1 - m);
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
        size_t k = 0;
        std::string pattern;
        std::string text;
        std::cin >> k >> pattern >> text;
        std::vector<size_t> matches = shift_and_bitap_k_mismatch(k, pattern, text);
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
