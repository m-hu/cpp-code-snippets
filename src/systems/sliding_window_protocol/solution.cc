// sliding-window-protocols: Stop-and-Wait, Go-Back-N, Selective Repeat.
// Pure C++14. Discrete-time simulation, RTT=2, TIMEOUT=4. Input:
// policy W (0 SW, 1 GBN, 2 SR); N L; L loss lines "F s"/"A s"
// (each consumed once). Output: "<frame_tx> <ack_tx>".
#include <iostream>
#include <map>
#include <string>
#include <vector>
const int TIMEOUT = 4;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int policy = 0;
    int64_t W = 1;
    if (!(std::cin >> policy >> W)) return 0;
    if (policy == 0) W = 1;
    int N = 0, L = 0;
    std::cin >> N >> L;
    std::map<int, int> floss, aloss;
    for (int i = 0; i < L; ++i) {
        char t; int s;
        std::cin >> t >> s;
        if (t == 'F') floss[s]++;
        else aloss[s]++;
    }
    int base = 0, nextToSend = 0;
    std::vector<int> sent(N, -1000000);
    std::vector<char> acked(N, 0);
    int expected = 0;
    std::vector<char> buffered(N, 0);
    std::vector<std::vector<int>> farr(100000);
    std::vector<std::vector<int>> aarr(100000);
    int64_t frameTx = 0, ackTx = 0;
    auto sendFrame = [&](int j, int now) {
        frameTx++;
        sent[j] = now;
        auto it = floss.find(j);
        if (it != floss.end() && it->second > 0) { it->second--; return; }
        if (now + 1 < (int)farr.size()) farr[now + 1].push_back(j);
    };
    auto sendAck = [&](int j, int now) {
        ackTx++;
        auto it = aloss.find(j);
        if (it != aloss.end() && it->second > 0) { it->second--; return; }
        if (now + 1 < (int)aarr.size()) aarr[now + 1].push_back(j);
    };
    int now = 0;
    for (; now < 90000; ++now) {
        for (int j : farr[now]) {
            if (j < 0 || j >= N) continue;
            if (policy == 2) {
                if (j == expected) {
                    ++expected;
                    while (expected < N && buffered[expected]) { buffered[expected] = 0; ++expected; }
                } else if (j > expected && j < expected + W) {
                    buffered[j] = 1;
                }
                sendAck(j, now);
            } else {
                if (j == expected) ++expected;
                if (expected > 0) sendAck(expected - 1, now);
            }
        }
        for (int j : aarr[now]) {
            if (policy == 2) {
                if (j >= 0 && j < N) acked[j] = 1;
            } else {
                for (int k = base; k <= j && k < N; ++k) acked[k] = 1;
            }
        }
        while (base < N && acked[base]) ++base;
        if (base >= N) break;
        if (policy == 2) {
            for (int j = base; j < nextToSend; ++j)
                if (!acked[j] && now - sent[j] >= TIMEOUT) sendFrame(j, now);
        } else {
            if (base < nextToSend && now - sent[base] >= TIMEOUT) nextToSend = base;
        }
        while (nextToSend < base + W && nextToSend < N) {
            sendFrame(nextToSend, now);
            ++nextToSend;
        }
    }
    std::cout << frameTx << " " << ackTx << "\n";
    return 0;
}
