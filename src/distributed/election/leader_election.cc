#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// LeLann-Chang-Roberts (LCR) algorithm simulation
int simulate_lcr(const vector<int>& ring) {
    size_t n = ring.size();
    int messages = 0;

    for (size_t i = 0; i < n; ++i) {
        int uid = ring[i];
        size_t cur = i;
        while (true) {
            ++messages;
            size_t nxt = (cur + 1) % n;
            if (nxt == i) break; // Traversed entire ring
            if (ring[nxt] > uid) {
                // Dropped
                break;
            }
            cur = nxt;
        }
    }
    return messages;
}

// Hirschberg-Sinclair (HS) algorithm simulation
int simulate_hs(const vector<int>& ring) {
    size_t n = ring.size();
    int max_uid = *max_element(ring.begin(), ring.end());
    int messages = 0;

    int phase = 0;
    while (true) {
        int limit = 1 << phase;
        bool leader_found = false;

        for (size_t i = 0; i < n; ++i) {
            int uid = ring[i];
            // Send outward in both directions
            for (int dir : {-1, 1}) {
                int dist = 0;
                size_t cur = i;
                bool ok = true;
                while (dist < limit) {
                    ++dist;
                    ++messages;
                    cur = static_cast<size_t>((static_cast<long long>(cur) + dir + static_cast<long long>(n)) % static_cast<long long>(n));
                    if (cur == i) {
                        leader_found = true;
                        break;
                    }
                    if (ring[cur] > uid) {
                        ok = false;
                        break;
                    }
                }
                if (leader_found) break;
                // Return message back to origin
                if (ok) {
                    messages += dist;
                }
            }
            if (leader_found) break;
        }

        if (leader_found || static_cast<size_t>(limit) >= n / 2) {
            break;
        }
        ++phase;
    }
    (void)max_uid;
    return messages;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0;
    if (!(cin >> n)) return 0;

    vector<int> ring(static_cast<size_t>(n));
    int leader_id = -1;
    for (int i = 0; i < n; ++i) {
        cin >> ring[static_cast<size_t>(i)];
        leader_id = max(leader_id, ring[static_cast<size_t>(i)]);
    }

    int lcr_msgs = simulate_lcr(ring);
    int hs_msgs = simulate_hs(ring);

    cout << "LEADER: " << leader_id << "\n";
    cout << "LCR MESSAGES: " << lcr_msgs << "\n";
    cout << "HS MESSAGES: " << hs_msgs << "\n";

    return 0;
}
