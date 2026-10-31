#include <algorithm>
#include <iostream>
#include <vector>

void selection_sort(std::vector<long long>& a) {
    std::size_t n = a.size();
    for (std::size_t i = 0; i < n; ++i) {
        std::size_t min_idx = i;
        for (std::size_t j = i + 1; j < n; ++j) {
            if (a[j] < a[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            std::swap(a[i], a[min_idx]);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n = 0;
    if (!(std::cin >> n)) {
        return 0;
    }

    std::vector<long long> a(n);
    for (std::size_t i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    selection_sort(a);

    for (std::size_t i = 0; i < n; ++i) {
        if (i > 0) {
            std::cout << ' ';
        }
        std::cout << a[i];
    }
    std::cout << '\n';
    return 0;
}
