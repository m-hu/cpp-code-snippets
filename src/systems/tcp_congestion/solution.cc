// tcp-congestion: slow start, AIMD, fast retransmit/recovery (Reno-lite).
// Pure C++14. Integer-exact (MSS=1; CA grows 1 MSS per cwnd ACKs).
// Input: q; q events A (new ACK), D (3 dupACKs), T (timeout).
// Output per event: "cwnd ssthresh".
#include <iostream>
#include <string>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int q = 0;
    if (!(std::cin >> q)) return 0;
    int64_t cwnd = 1, ssthresh = 64, ackCount = 0;
    for (int i = 0; i < q; ++i) {
        char e;
        std::cin >> e;
        if (e == 'A') {
            if (cwnd < ssthresh) {
                cwnd += 1;
            } else {
                ackCount += 1;
                if (ackCount >= cwnd) { cwnd += 1; ackCount = 0; }
            }
        } else if (e == 'D') {
            ssthresh = cwnd / 2;
            if (ssthresh < 1) ssthresh = 1;
            cwnd = ssthresh;
            ackCount = 0;
        } else if (e == 'T') {
            ssthresh = cwnd / 2;
            if (ssthresh < 1) ssthresh = 1;
            cwnd = 1;
            ackCount = 0;
        }
        std::cout << cwnd << " " << ssthresh << "\n";
    }
    return 0;
}
