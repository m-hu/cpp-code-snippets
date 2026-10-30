#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

namespace {

void morris_inorder(const std::vector<int64_t>& val,
                    const std::vector<int>& left,
                    std::vector<int>& right) {
    int curr = 0;
    bool first = true;
    while (curr != -1) {
        size_t u = static_cast<size_t>(curr);
        if (left[u] == -1) {
            if (!first) std::cout << ' ';
            first = false;
            std::cout << val[u];
            curr = right[u];
        } else {
            int pred = left[u];
            while (right[static_cast<size_t>(pred)] != -1 &&
                   right[static_cast<size_t>(pred)] != curr) {
                pred = right[static_cast<size_t>(pred)];
            }
            size_t p = static_cast<size_t>(pred);
            if (right[p] == -1) {
                right[p] = curr;
                curr = left[u];
            } else {
                right[p] = -1;
                if (!first) std::cout << ' ';
                first = false;
                std::cout << val[u];
                curr = right[u];
            }
        }
    }
    std::cout << '\n';
}

void morris_preorder(const std::vector<int64_t>& val,
                     const std::vector<int>& left,
                     std::vector<int>& right) {
    int curr = 0;
    bool first = true;
    while (curr != -1) {
        size_t u = static_cast<size_t>(curr);
        if (left[u] == -1) {
            if (!first) std::cout << ' ';
            first = false;
            std::cout << val[u];
            curr = right[u];
        } else {
            int pred = left[u];
            while (right[static_cast<size_t>(pred)] != -1 &&
                   right[static_cast<size_t>(pred)] != curr) {
                pred = right[static_cast<size_t>(pred)];
            }
            size_t p = static_cast<size_t>(pred);
            if (right[p] == -1) {
                if (!first) std::cout << ' ';
                first = false;
                std::cout << val[u];
                right[p] = curr;
                curr = left[u];
            } else {
                right[p] = -1;
                curr = right[u];
            }
        }
    }
    std::cout << '\n';
}

}  // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    if (!(std::cin >> n) || n <= 0) return 0;

    size_t sz = static_cast<size_t>(n);
    std::vector<int64_t> val(sz);
    std::vector<int> left(sz, -1);
    std::vector<int> right(sz, -1);

    for (size_t i = 0; i < sz; ++i) {
        std::cin >> val[i] >> left[i] >> right[i];
    }

    morris_inorder(val, left, right);
    morris_preorder(val, left, right);

    return 0;
}
