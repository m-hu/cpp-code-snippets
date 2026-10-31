// cpu-scheduling: FCFS, SJF, Round-Robin (Tanenbaum MOS 2.4). Pure C++14.
// Line1: policy (0 FCFS, 1 SJF nonpreemptive, 2 RR). RR: line2 quantum.
// Then n, n arrival/burst lines (id = input order). Output: completion
// order line, total waiting time line. RR re-queues current after arrivals.
#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int policy = 0;
    if (!(std::cin >> policy)) return 0;
    int64_t quantum = 1;
    if (policy == 2) std::cin >> quantum;
    int n = 0;
    std::cin >> n;
    std::vector<int64_t> arr(n), burst(n);
    for (int i = 0; i < n; ++i) std::cin >> arr[i] >> burst[i];
    std::vector<int> order;
    std::vector<int64_t> comp(n, -1);
    std::vector<int> idx(n);
    for (int i = 0; i < n; ++i) idx[i] = i;
    std::sort(idx.begin(), idx.end(), [&](int x, int y) {
        if (arr[x] != arr[y]) return arr[x] < arr[y];
        return x < y;
    });
    if (policy == 0) {
        int64_t now = 0;
        for (int id : idx) {
            if (now < arr[id]) now = arr[id];
            now += burst[id];
            comp[id] = now;
            order.push_back(id);
        }
    } else if (policy == 1) {
        std::vector<char> done(n, 0);
        int64_t now = 0;
        int left = n;
        while (left > 0) {
            int pick = -1;
            for (int id = 0; id < n; ++id) {
                if (done[id] || arr[id] > now) continue;
                if (pick == -1 || burst[id] < burst[pick] ||
                    (burst[id] == burst[pick] && (arr[id] < arr[pick] ||
                     (arr[id] == arr[pick] && id < pick))))
                    pick = id;
            }
            if (pick == -1) {
                int64_t nx = -1;
                for (int id = 0; id < n; ++id)
                    if (!done[id] && (nx == -1 || arr[id] < nx)) nx = arr[id];
                now = nx;
                continue;
            }
            now += burst[pick];
            comp[pick] = now;
            done[pick] = 1;
            order.push_back(pick);
            --left;
        }
    } else {
        std::vector<int64_t> rem = burst;
        std::vector<char> added(n, 0);
        std::deque<int> ready;
        int64_t now = 0;
        size_t ap = 0;
        int left = n;
        while (left > 0) {
            while (ap < idx.size() && arr[idx[ap]] <= now) { ready.push_back(idx[ap]); added[idx[ap]] = 1; ++ap; }
            if (ready.empty()) { now = arr[idx[ap]]; continue; }
            int id = ready.front(); ready.pop_front();
            int64_t run = rem[id] < quantum ? rem[id] : quantum;
            now += run;
            rem[id] -= run;
            while (ap < idx.size() && arr[idx[ap]] <= now) { ready.push_back(idx[ap]); added[idx[ap]] = 1; ++ap; }
            if (rem[id] > 0) ready.push_back(id);
            else { comp[id] = now; order.push_back(id); --left; }
        }
    }
    for (size_t i = 0; i < order.size(); ++i) {
        if (i) std::cout << " ";
        std::cout << order[i];
    }
    std::cout << "\n";
    int64_t tot = 0;
    for (int i = 0; i < n; ++i) tot += comp[i] - arr[i] - burst[i];
    std::cout << tot << "\n";
    return 0;
}
