#include <bits/stdc++.h>
namespace oi {
inline std::vector<int> bottom_up_mergesort(std::vector<int> &a) {
    size_t n = a.size();
    if (n < 2) return a;
    std::vector<int> aux(n), tmp(n);
    // copy to aux for merging
    for (size_t sz = 1; sz < n; sz *= 2) {
        for (size_t lo = 0; lo + sz < n; lo += 2 * sz) {
            size_t mid = lo + sz;
            size_t hi = std::min(lo + 2 * sz, n);
            size_t i = lo, j = mid, k = lo;
            while (i < mid && j < hi) {
                if (a[i] <= a[j]) aux[k++] = a[i++];
                else aux[k++] = a[j++];
            }
            while (i < mid) aux[k++] = a[i++];
            while (j < hi) aux[k++] = a[j++];
            for (size_t t = lo; t < hi; ++t) a[t] = aux[t];
        }
    }
    return a;
}
}
