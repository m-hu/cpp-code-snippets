// page-replacement: OPT, FIFO, Clock, LRU fault counts (Tanenbaum MOS 3.4).
// Pure C++14. Input: frames nrefs; reference string. Output one line:
// "<opt> <fifo> <clock> <lru>".
#include <iostream>
#include <vector>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int f = 0, n = 0;
    if (!(std::cin >> f >> n)) return 0;
    std::vector<int64_t> refs(n);
    for (int i = 0; i < n; ++i) std::cin >> refs[i];
    // OPT
    int opt = 0;
    {
        std::vector<int64_t> frames;
        for (int i = 0; i < n; ++i) {
            bool hit = false;
            for (auto p : frames) if (p == refs[i]) { hit = true; break; }
            if (hit) continue;
            ++opt;
            if ((int)frames.size() < f) { frames.push_back(refs[i]); continue; }
            int victim = 0, far = -1;
            for (size_t s = 0; s < frames.size(); ++s) {
                int nx = n + 1;
                for (int j = i + 1; j < n; ++j)
                    if (refs[j] == frames[s]) { nx = j; break; }
                if (nx > far) { far = nx; victim = (int)s; }
            }
            frames[victim] = refs[i];
        }
    }
    // FIFO
    int fifo = 0;
    {
        std::vector<int64_t> frames;
        size_t head = 0;
        for (int i = 0; i < n; ++i) {
            bool hit = false;
            for (auto p : frames) if (p == refs[i]) { hit = true; break; }
            if (hit) continue;
            ++fifo;
            if ((int)frames.size() < f) frames.push_back(refs[i]);
            else { frames[head] = refs[i]; head = (head + 1) % frames.size(); }
        }
    }
    // Clock
    int clock = 0;
    {
        std::vector<int64_t> frames(f, 0);
        std::vector<char> occ(f, 0), ref(f, 0);
        int hand = 0;
        for (int i = 0; i < n; ++i) {
            bool hit = false;
            for (int s = 0; s < f; ++s)
                if (occ[s] && frames[s] == refs[i]) { hit = true; ref[s] = 1; break; }
            if (hit) continue;
            ++clock;
            for (;;) {
                if (!occ[hand]) break;
                if (ref[hand]) { ref[hand] = 0; hand = (hand + 1) % f; }
                else break;
            }
            frames[hand] = refs[i]; occ[hand] = 1; ref[hand] = 1;
            hand = (hand + 1) % f;
        }
    }
    // LRU
    int lru = 0;
    {
        std::vector<int64_t> frames;
        for (int i = 0; i < n; ++i) {
            int at = -1;
            for (size_t s = 0; s < frames.size(); ++s)
                if (frames[s] == refs[i]) { at = (int)s; break; }
            if (at != -1) {
                int64_t p = frames[at];
                frames.erase(frames.begin() + at);
                frames.push_back(p);
                continue;
            }
            ++lru;
            if ((int)frames.size() < f) frames.push_back(refs[i]);
            else { frames.erase(frames.begin()); frames.push_back(refs[i]); }
        }
    }
    std::cout << opt << " " << fifo << " " << clock << " " << lru << "\n";
    return 0;
}
