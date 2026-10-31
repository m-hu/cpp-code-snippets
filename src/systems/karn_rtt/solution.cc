// karn-rtt: Karn + Jacobson/Karels RTO estimator (RFC 6298 integers).
// Pure C++14. G=1, RTO in [1,60000], init RTO 1000. Input: q events:
// S <rtt> <retrans> (retrans samples ignored per Karn), T (timeout
// doubles RTO). Output per event: "SRTT RTTVAR RTO".
#include <cstdlib>
#include <iostream>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int q = 0;
    if (!(std::cin >> q)) return 0;
    int64_t srtt = 0, rttvar = 0, rto = 1000;
    bool haveSample = false;
    for (int i = 0; i < q; ++i) {
        char e;
        std::cin >> e;
        if (e == 'S') {
            int64_t r = 0;
            int ret = 0;
            std::cin >> r >> ret;
            if (ret == 0) {
                if (!haveSample) {
                    haveSample = true;
                    srtt = r;
                    rttvar = r / 2;
                } else {
                    rttvar = (3 * rttvar + std::llabs(srtt - r)) / 4;
                    srtt = (7 * srtt + r) / 8;
                }
                int64_t x = 4 * rttvar;
                if (x < 1) x = 1;
                rto = srtt + x;
                if (rto < 1) rto = 1;
                if (rto > 60000) rto = 60000;
            }
        } else if (e == 'T') {
            rto *= 2;
            if (rto > 60000) rto = 60000;
        }
        std::cout << srtt << " " << rttvar << " " << rto << "\n";
    }
    return 0;
}
