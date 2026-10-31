// bankers-algorithm: deadlock avoidance safety check (Tanenbaum MOS 6.5).
// Pure C++14. Input: n r; available; n alloc rows; n max rows.
// Output: SAFE + sequence, or UNSAFE + completed count.
#include <iostream>
#include <vector>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n = 0, r = 0;
    if (!(std::cin >> n >> r)) return 0;
    std::vector<int64_t> avail(r);
    for (int j = 0; j < r; ++j) std::cin >> avail[j];
    std::vector<std::vector<int64_t>> alloc(n, std::vector<int64_t>(r)), mx(n, std::vector<int64_t>(r));
    for (int i = 0; i < n; ++i) for (int j = 0; j < r; ++j) std::cin >> alloc[i][j];
    for (int i = 0; i < n; ++i) for (int j = 0; j < r; ++j) std::cin >> mx[i][j];
    std::vector<int64_t> work = avail;
    std::vector<char> done(n, 0);
    std::vector<int> seq;
    for (;;) {
        int pick = -1;
        for (int i = 0; i < n; ++i) {
            if (done[i]) continue;
            bool ok = true;
            for (int j = 0; j < r; ++j)
                if (mx[i][j] - alloc[i][j] > work[j]) { ok = false; break; }
            if (ok) { pick = i; break; }
        }
        if (pick == -1) break;
        done[pick] = 1;
        seq.push_back(pick);
        for (int j = 0; j < r; ++j) work[j] += alloc[pick][j];
    }
    if ((int)seq.size() == n) {
        std::cout << "SAFE";
        for (int i : seq) std::cout << " " << i;
        std::cout << "\n";
    } else {
        std::cout << "UNSAFE " << seq.size() << "\n";
    }
    return 0;
}
