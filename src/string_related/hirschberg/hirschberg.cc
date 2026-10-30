#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int MATCH = 2;
const int MISMATCH = -1;
const int GAP = -2;

vector<int> nw_score(const string& x, const string& y) {
    size_t m = y.size();
    vector<int> prev(m + 1, 0);
    vector<int> curr(m + 1, 0);

    for (size_t j = 1; j <= m; ++j) {
        prev[j] = prev[j - 1] + GAP;
    }

    for (size_t i = 1; i <= x.size(); ++i) {
        curr[0] = prev[0] + GAP;
        for (size_t j = 1; j <= m; ++j) {
            int diag = prev[j - 1] + (x[i - 1] == y[j - 1] ? MATCH : MISMATCH);
            int up = prev[j] + GAP;
            int left = curr[j - 1] + GAP;
            curr[j] = max({diag, up, left});
        }
        prev = curr;
    }
    return prev;
}

pair<string, string> hirschberg(const string& x, const string& y) {
    if (x.empty()) {
        return {string(y.size(), '-'), y};
    }
    if (y.empty()) {
        return {x, string(x.size(), '-')};
    }
    if (x.size() == 1 || y.size() == 1) {
        // Base case: small enough for standard NW
        size_t n = x.size(), m = y.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (size_t i = 1; i <= n; ++i) dp[i][0] = dp[i - 1][0] + GAP;
        for (size_t j = 1; j <= m; ++j) dp[0][j] = dp[0][j - 1] + GAP;
        for (size_t i = 1; i <= n; ++i) {
            for (size_t j = 1; j <= m; ++j) {
                int diag = dp[i - 1][j - 1] + (x[i - 1] == y[j - 1] ? MATCH : MISMATCH);
                int up = dp[i - 1][j] + GAP;
                int left = dp[i][j - 1] + GAP;
                dp[i][j] = max({diag, up, left});
            }
        }
        string a1, a2;
        size_t i = n, j = m;
        while (i > 0 || j > 0) {
            if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + (x[i - 1] == y[j - 1] ? MATCH : MISMATCH)) {
                a1.push_back(x[i - 1]);
                a2.push_back(y[j - 1]);
                --i; --j;
            } else if (i > 0 && dp[i][j] == dp[i - 1][j] + GAP) {
                a1.push_back(x[i - 1]);
                a2.push_back('-');
                --i;
            } else {
                a1.push_back('-');
                a2.push_back(y[j - 1]);
                --j;
            }
        }
        reverse(a1.begin(), a1.end());
        reverse(a2.begin(), a2.end());
        return {a1, a2};
    }

    size_t xlen = x.size();
    size_t xmid = xlen / 2;

    string x_left = x.substr(0, xmid);
    string x_right = x.substr(xmid);
    string rev_x_right = x_right;
    reverse(rev_x_right.begin(), rev_x_right.end());

    string rev_y = y;
    reverse(rev_y.begin(), rev_y.end());

    vector<int> score_l = nw_score(x_left, y);
    vector<int> score_r = nw_score(rev_x_right, rev_y);

    size_t m = y.size();
    int best_score = -1e9;
    size_t best_j = 0;

    for (size_t j = 0; j <= m; ++j) {
        int total = score_l[j] + score_r[m - j];
        if (total > best_score) {
            best_score = total;
            best_j = j;
        }
    }

    auto left_res = hirschberg(x_left, y.substr(0, best_j));
    auto right_res = hirschberg(x_right, y.substr(best_j));

    return {left_res.first + right_res.first, left_res.second + right_res.second};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s1, s2;
    if (!(cin >> s1 >> s2)) return 0;

    auto res = hirschberg(s1, s2);
    int score = 0;
    for (size_t i = 0; i < res.first.size(); ++i) {
        if (res.first[i] == '-' || res.second[i] == '-') {
            score += GAP;
        } else if (res.first[i] == res.second[i]) {
            score += MATCH;
        } else {
            score += MISMATCH;
        }
    }

    cout << score << "\n";
    cout << res.first << "\n";
    cout << res.second << "\n";

    return 0;
}
