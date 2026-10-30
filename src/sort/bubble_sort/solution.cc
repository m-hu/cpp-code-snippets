#include <algorithm>
#include <iostream>
#include <vector>

long long bubble_sort(std::vector<long long>& a) {
    std::size_t n = a.size();
    long long swaps = 0;
    if (n < 2) {
        return 0;
    }
    for (std::size_t i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (std::size_t j = 0; j < n - 1 - i; ++j) {
            if (a[j] > a[j + 1]) {
                std::swap(a[j], a[j + 1]);
                ++swaps;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
    return swaps;
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

    long long swaps = bubble_sort(a);

    for (std::size_t i = 0; i < n; ++i) {
        if (i > 0) {
            std::cout << ' ';
        }
        std::cout << a[i];
    }
    std::cout << '\n' << swaps << '\n';
    return 0;
}
