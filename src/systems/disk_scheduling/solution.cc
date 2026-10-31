// disk-scheduling: FCFS SSTF SCAN C-SCAN LOOK C-LOOK (Tanenbaum MOS 2.4).
// Pure C++14. Input: head maxc n; n requests. Output 6 lines:
// "<POLICY> <total movement> <service order>". SCAN/C-SCAN travel to
// maxc (C-SCAN counts the maxc->0 wrap); initial direction up.
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int64_t head = 0, maxc = 0;
    int n = 0;
    if (!(std::cin >> head >> maxc >> n)) return 0;
    std::vector<int64_t> req(n);
    for (int i = 0; i < n; ++i) std::cin >> req[i];
    // FCFS
    {
        int64_t tot = 0, h = head;
        for (int i = 0; i < n; ++i) { tot += std::llabs(req[i] - h); h = req[i]; }
        std::cout << "FCFS " << tot;
        for (int i = 0; i < n; ++i) std::cout << " " << req[i];
        std::cout << "\n";
    }
    // SSTF
    {
        std::vector<char> done(n, 0);
        int64_t tot = 0, h = head;
        std::vector<int64_t> ord;
        for (int k = 0; k < n; ++k) {
            int pick = -1;
            for (int i = 0; i < n; ++i) {
                if (done[i]) continue;
                if (pick == -1 || std::llabs(req[i] - h) < std::llabs(req[pick] - h) ||
                    (std::llabs(req[i] - h) == std::llabs(req[pick] - h) &&
                     (req[i] < req[pick] || (req[i] == req[pick] && i < pick))))
                    pick = i;
            }
            tot += std::llabs(req[pick] - h);
            h = req[pick];
            done[pick] = 1;
            ord.push_back(req[pick]);
        }
        std::cout << "SSTF " << tot;
        for (auto v : ord) std::cout << " " << v;
        std::cout << "\n";
    }
    std::vector<int64_t> up, down;
    for (int i = 0; i < n; ++i)
        if (req[i] >= head) up.push_back(req[i]);
        else down.push_back(req[i]);
    std::sort(up.begin(), up.end());
    std::sort(down.begin(), down.end());
    // SCAN
    {
        int64_t tot = maxc - head;
        if (!down.empty()) tot += maxc - down.front();
        std::cout << "SCAN " << tot;
        for (auto v : up) std::cout << " " << v;
        for (int i = (int)down.size() - 1; i >= 0; --i) std::cout << " " << down[i];
        std::cout << "\n";
    }
    // C-SCAN
    {
        int64_t tot = (maxc - head) + maxc;
        if (!down.empty()) tot += down.back();
        std::cout << "CSCAN " << tot;
        for (auto v : up) std::cout << " " << v;
        for (auto v : down) std::cout << " " << v;
        std::cout << "\n";
    }
    // LOOK
    {
        int64_t tot = 0;
        if (!up.empty() && !down.empty()) tot = (up.back() - head) + (up.back() - down.front());
        else if (!up.empty()) tot = up.back() - head;
        else if (!down.empty()) tot = head - down.front();
        std::cout << "LOOK " << tot;
        for (auto v : up) std::cout << " " << v;
        for (int i = (int)down.size() - 1; i >= 0; --i) std::cout << " " << down[i];
        std::cout << "\n";
    }
    // C-LOOK
    {
        int64_t tot = 0;
        if (!up.empty() && !down.empty())
            tot = (up.back() - head) + (up.back() - down.front()) + (down.back() - down.front());
        else if (!up.empty()) tot = up.back() - head;
        else if (!down.empty()) tot = (head - down.front()) + (down.back() - down.front());
        std::cout << "CLOOK " << tot;
        for (auto v : up) std::cout << " " << v;
        for (auto v : down) std::cout << " " << v;
        std::cout << "\n";
    }
    return 0;
}
