#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
int combinePos(const string& a, const string& b) {
    int diff = -1;
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            if (a[i] == '-' || b[i] == '-') return -1;
            if (diff >= 0) return -1;
            diff = (int)i;
        }
    }
    return diff;
}
bool covers(const string& imp, const string& mt) {
    for (size_t i = 0; i < imp.size(); i++)
        if (imp[i] != '-' && imp[i] != mt[i]) return false;
    return true;
}
string bitsOf(int m, int n) {
    string s;
    for (int i = n - 1; i >= 0; i--) s.push_back(((m >> i) & 1) ? '1' : '0');
    return s;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, k; if (!(cin >> n >> k)) return 0;
    vector<int> mts(k);
    for (int i = 0; i < k; i++) cin >> mts[i];
    sort(mts.begin(), mts.end());
    mts.erase(unique(mts.begin(), mts.end()), mts.end());
    vector<string> cur;
    for (int m : mts) cur.push_back(bitsOf(m, n));
    sort(cur.begin(), cur.end());
    vector<string> primes;
    while (true) {
        vector<vector<string>> groups(n + 1);
        for (auto& t : cur) {
            int c = 0;
            for (char ch : t) if (ch == '1') c++;
            groups[c].push_back(t);
        }
        set<string> used, nxt;
        for (int g = 0; g < n; g++) {
            for (auto& a : groups[g]) for (auto& b : groups[g + 1]) {
                int d = combinePos(a, b);
                if (d >= 0) {
                    used.insert(a); used.insert(b);
                    string c = a; c[(size_t)d] = '-';
                    nxt.insert(c);
                }
            }
        }
        for (auto& t : cur) if (!used.count(t)) primes.push_back(t);
        if (nxt.empty()) break;
        cur = vector<string>(nxt.begin(), nxt.end());
    }
    sort(primes.begin(), primes.end());
    primes.erase(unique(primes.begin(), primes.end()), primes.end());
    vector<string> mtbits;
    for (int m : mts) mtbits.push_back(bitsOf(m, n));
    vector<bool> unc(mts.size(), true);
    set<string> cover;
    for (size_t i = 0; i < mts.size(); i++) {
        vector<string> cov;
        for (auto& p : primes) if (covers(p, mtbits[i])) cov.push_back(p);
        if (cov.size() == 1) cover.insert(cov[0]);
    }
    auto applyCover = [&]() {
        for (size_t i = 0; i < mts.size(); i++) if (unc[i])
            for (auto& p : cover) if (covers(p, mtbits[i])) { unc[i] = false; break; }
    };
    applyCover();
    while (true) {
        bool any = false;
        for (bool u : unc) if (u) any = true;
        if (!any) break;
        string best; int bc = -1;
        for (auto& p : primes) {
            int c = 0;
            for (size_t i = 0; i < mts.size(); i++)
                if (unc[i] && covers(p, mtbits[i])) c++;
            if (c > bc || (c == bc && (bc < 0 || p < best))) { best = p; bc = c; }
        }
        cover.insert(best);
        applyCover();
    }
    vector<string> covv(cover.begin(), cover.end());
    cout << primes.size() << "\n" << covv.size() << "\n";
    for (auto& p : covv) cout << p << "\n";
    return 0;
}
