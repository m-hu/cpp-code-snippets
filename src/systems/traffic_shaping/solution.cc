// traffic-shaping: token bucket, leaky bucket, WFQ/virtual-clock.
// Pure C++14. Line1 policy (0 token, 1 leaky, 2 wfq).
// 0/1: rate depth n; packets time size -> CONFORM/DROP each.
// 2: F n; F weights; packets flow arrival size -> finish num/den per
// packet (common denominator), then ORDER line. Integer math only.
#include <algorithm>
#include <iostream>
#include <vector>
static int64_t igcd(int64_t a, int64_t b) {
    while (b) { int64_t t = a % b; a = b; b = t; }
    return a;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int policy = 0;
    if (!(std::cin >> policy)) return 0;
    if (policy == 0) {
        int64_t rate, depth;
        int n;
        std::cin >> rate >> depth >> n;
        int64_t tokens = depth, last = 0;
        bool first = true;
        for (int i = 0; i < n; ++i) {
            int64_t t, s;
            std::cin >> t >> s;
            if (first) { last = t; first = false; }
            tokens += rate * (t - last);
            if (tokens > depth) tokens = depth;
            last = t;
            if (tokens >= s) { tokens -= s; std::cout << "CONFORM\n"; }
            else std::cout << "DROP\n";
        }
    } else if (policy == 1) {
        int64_t rate, depth;
        int n;
        std::cin >> rate >> depth >> n;
        int64_t content = 0, last = 0;
        bool first = true;
        for (int i = 0; i < n; ++i) {
            int64_t t, s;
            std::cin >> t >> s;
            if (first) { last = t; first = false; }
            content -= rate * (t - last);
            if (content < 0) content = 0;
            last = t;
            if (content + s <= depth) { content += s; std::cout << "CONFORM\n"; }
            else std::cout << "DROP\n";
        }
    } else {
        int F, n;
        std::cin >> F >> n;
        std::vector<int64_t> w(F);
        for (int f = 0; f < F; ++f) std::cin >> w[f];
        int64_t L = 1;
        for (int f = 0; f < F; ++f) L = L / igcd(L, w[f]) * w[f];
        struct Pkt { int flow; int64_t arr, size; };
        std::vector<Pkt> pk(n);
        for (int i = 0; i < n; ++i) std::cin >> pk[i].flow >> pk[i].arr >> pk[i].size;
        std::vector<int64_t> prevF(F, 0), fnum(n);
        for (int i = 0; i < n; ++i) {
            int64_t start = pk[i].arr * L;
            if (prevF[pk[i].flow] > start) start = prevF[pk[i].flow];
            int64_t fin = start + pk[i].size * (L / w[pk[i].flow]);
            prevF[pk[i].flow] = fin;
            fnum[i] = fin;
        }
        for (int i = 0; i < n; ++i) std::cout << fnum[i] << "/" << L << "\n";
        std::vector<int> ord(n);
        for (int i = 0; i < n; ++i) ord[i] = i;
        std::sort(ord.begin(), ord.end(), [&](int x, int y) {
            if (fnum[x] != fnum[y]) return fnum[x] < fnum[y];
            if (pk[x].flow != pk[y].flow) return pk[x].flow < pk[y].flow;
            return x < y;
        });
        std::cout << "ORDER";
        for (int i : ord) std::cout << " " << i;
        std::cout << "\n";
    }
    return 0;
}
