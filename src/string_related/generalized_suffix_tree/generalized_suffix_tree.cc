#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k;
    if (!(cin >> k)) return 0;
    vector<string> strs(k);
    for (int i = 0; i < k; i++) cin >> strs[i];
    if (k == 0) { cout << "0\n\n"; return 0; }
    if (k == 1) { cout << strs[0].size() << "\n" << strs[0] << "\n"; return 0; }
    // Binary search on answer length; check existence of common substring of length L
    int lo = 0, hi = INT_MAX;
    for (auto &s : strs) hi = min(hi, (int)s.size());
    auto has_common = [&](int L, string *out) -> bool {
        if (L == 0) { if (out) *out = ""; return true; }
        unordered_set<string> common;
        for (int i = 0; i + L <= (int)strs[0].size(); i++) common.insert(strs[0].substr(i, L));
        for (int t = 1; t < k; t++) {
            unordered_set<string> cur;
            for (int i = 0; i + L <= (int)strs[t].size(); i++) {
                string sub = strs[t].substr(i, L);
                if (common.count(sub)) cur.insert(sub);
            }
            common = std::move(cur);
            if (common.empty()) return false;
        }
        if (out && !common.empty()) *out = *common.begin();
        return !common.empty();
    };
    string best_str = "";
    int best = 0;
    // Find maximum L with common substring
    int low = 0, high = hi;
    while (low <= high) {
        int mid = (low + high) / 2;
        string cur;
        if (has_common(mid, &cur)) { best = mid; best_str = cur; low = mid + 1; }
        else high = mid - 1;
    }
    // To ensure lexicographically smallest among max-length, re-derive
    if (best > 0) {
        unordered_set<string> common;
        for (int i = 0; i + best <= (int)strs[0].size(); i++) common.insert(strs[0].substr(i, best));
        for (int t = 1; t < k; t++) {
            unordered_set<string> cur;
            for (int i = 0; i + best <= (int)strs[t].size(); i++) {
                string sub = strs[t].substr(i, best);
                if (common.count(sub)) cur.insert(sub);
            }
            common = std::move(cur);
        }
        best_str = *min_element(common.begin(), common.end());
    }
    cout << best << "\n" << best_str << "\n";
    return 0;
}
