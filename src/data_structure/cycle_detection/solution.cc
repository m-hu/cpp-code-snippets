#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0;
    int s = 0;
    if (!(cin >> n >> s) || n <= 0 || s < 0 || s >= n) {
        return 0;
    }

    vector<int> nxt(static_cast<size_t>(n));
    for (int i = 0; i < n; ++i) {
        cin >> nxt[static_cast<size_t>(i)];
    }

    int tortoise = s;
    int hare = s;
    bool has_cycle = false;

    while (true) {
        if (hare == -1 || nxt[static_cast<size_t>(hare)] == -1) {
            has_cycle = false;
            break;
        }
        int next_hare = nxt[static_cast<size_t>(hare)];
        if ( nxt[static_cast<size_t>(next_hare)] == -1) {
            has_cycle = false;
            break;
        }
        tortoise = nxt[static_cast<size_t>(tortoise)];
        hare = nxt[static_cast<size_t>(next_hare)];
        if (tortoise == hare) {
            has_cycle = true;
            break;
        }
    }

    if (!has_cycle) {
        int steps = 0;
        int cur = s;
        while (cur != -1) {
            cur = nxt[static_cast<size_t>(cur)];
            ++steps;
        }
        cout << "NO CYCLE " << steps << "\n";
        return 0;
    }

    int mu = 0;
    tortoise = s;
    while (tortoise != hare) {
        tortoise = nxt[static_cast<size_t>(tortoise)];
        hare = nxt[static_cast<size_t>(hare)];
        ++mu;
    }
    int entry_node = tortoise;

    int lambda = 1;
    hare = nxt[static_cast<size_t>(tortoise)];
    while (tortoise != hare) {
        hare = nxt[static_cast<size_t>(hare)];
        ++lambda;
    }

    cout << "CYCLE " << mu << " " << lambda << " " << entry_node << "\n";
    return 0;
}
