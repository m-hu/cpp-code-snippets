// rt-scheduling: RMS Liu-Layland bound vs EDF utilization test (MOS 2.4.4).
// Pure C++14. Input: n; n lines C T. Output RMS YES/NO, EDF YES/NO.
// 2^(1/n) via Newton iteration (uniform across languages).
#include <iostream>
#include <vector>
static double npow2inv(int n) {
    double x = 1.0;
    for (int it = 0; it < 200; ++it) {
        double p = 1.0;
        for (int i = 0; i < n - 1; ++i) p *= x;
        double f = p * x - 2.0;
        double d = (double)n * p;
        x -= f / d;
    }
    return x;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n = 0;
    if (!(std::cin >> n)) return 0;
    double u = 0.0;
    for (int i = 0; i < n; ++i) {
        double c, t;
        std::cin >> c >> t;
        u += c / t;
    }
    double bound = (double)n * (npow2inv(n) - 1.0);
    std::cout << (u <= bound ? "RMS YES\n" : "RMS NO\n");
    std::cout << (u <= 1.0 ? "EDF YES\n" : "EDF NO\n");
    return 0;
}
