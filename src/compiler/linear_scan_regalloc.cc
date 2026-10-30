#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

struct Interval {
    int id;
    int start;
    int end;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0, k_regs = 0;
    if (!(cin >> n >> k_regs)) return 0;

    vector<Interval> intervals(static_cast<size_t>(n));
    for (int i = 0; i < n; ++i) {
        int id = 0, s = 0, e = 0;
        cin >> id >> s >> e;
        intervals[static_cast<size_t>(i)] = {id, s, e};
    }

    // Sort intervals by start time
    vector<Interval> sorted_intervals = intervals;
    sort(sorted_intervals.begin(), sorted_intervals.end(), [](const Interval& a, const Interval& b) {
        if (a.start != b.start) return a.start < b.start;
        return a.end < b.end;
    });

    // Free register pool (0 .. k_regs - 1)
    set<int> free_regs;
    for (int r = 0; r < k_regs; ++r) {
        free_regs.insert(r);
    }

    // Active intervals: list of (end_time, interval_id, reg)
    struct ActiveItem {
        int end;
        int id;
        int reg;
    };
    vector<ActiveItem> active;

    // Results
    vector<int> assigned_reg(static_cast<size_t>(n), -1);
    vector<bool> is_spilled(static_cast<size_t>(n), false);

    for (const auto& cur : sorted_intervals) {
        // Expire old intervals
        vector<ActiveItem> new_active;
        for (const auto& act : active) {
            if (act.end < cur.start) {
                free_regs.insert(act.reg);
            } else {
                new_active.push_back(act);
            }
        }
        active = std::move(new_active);

        if (static_cast<int>(active.size()) == k_regs) {
            // Spill at interval: compare current with the one in active ending latest
            // Active is sorted by end
            auto latest_it = max_element(active.begin(), active.end(), [](const ActiveItem& a, const ActiveItem& b) {
                return a.end < b.end;
            });

            if (latest_it != active.end() && latest_it->end > cur.end) {
                // Spill the latest active interval
                int spilled_id = latest_it->id;
                int reg = latest_it->reg;
                is_spilled[static_cast<size_t>(spilled_id)] = true;
                assigned_reg[static_cast<size_t>(spilled_id)] = -1;

                active.erase(latest_it);
                assigned_reg[static_cast<size_t>(cur.id)] = reg;
                active.push_back({cur.end, cur.id, reg});
            } else {
                // Spill current interval
                is_spilled[static_cast<size_t>(cur.id)] = true;
            }
        } else {
            // Allocate free register
            int reg = *free_regs.begin();
            free_regs.erase(free_regs.begin());
            assigned_reg[static_cast<size_t>(cur.id)] = reg;
            active.push_back({cur.end, cur.id, reg});
        }

        // Keep active sorted by end
        sort(active.begin(), active.end(), [](const ActiveItem& a, const ActiveItem& b) {
            return a.end < b.end;
        });
    }

    int allocated_cnt = 0;
    int spilled_cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (is_spilled[static_cast<size_t>(i)]) {
            cout << "v" << i << ": SPILL\n";
            ++spilled_cnt;
        } else {
            cout << "v" << i << ": R" << assigned_reg[static_cast<size_t>(i)] << "\n";
            ++allocated_cnt;
        }
    }
    cout << "Allocated: " << allocated_cnt << " Spilled: " << spilled_cnt << "\n";

    return 0;
}
