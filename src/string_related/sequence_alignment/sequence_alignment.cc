#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int MATCH = 2;
const int MISMATCH = -1;
const int GAP = -2;

void solve_global(const string& s1, const string& s2) {
    size_t n = s1.size();
    size_t m = s2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (size_t i = 1; i <= n; ++i) dp[i][0] = dp[i - 1][0] + GAP;
    for (size_t j = 1; j <= m; ++j) dp[0][j] = dp[0][j - 1] + GAP;

    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= m; ++j) {
            int diag = dp[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? MATCH : MISMATCH);
            int up = dp[i - 1][j] + GAP;
            int left = dp[i][j - 1] + GAP;
            dp[i][j] = max({diag, up, left});
        }
    }

    // Traceback
    string a1 = "", a2 = "";
    size_t i = n, j = m;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? MATCH : MISMATCH)) {
            a1.push_back(s1[i - 1]);
            a2.push_back(s2[j - 1]);
            --i; --j;
        } else if (i > 0 && dp[i][j] == dp[i - 1][j] + GAP) {
            a1.push_back(s1[i - 1]);
            a2.push_back('-');
            --i;
        } else {
            a1.push_back('-');
            a2.push_back(s2[j - 1]);
            --j;
        }
    }

    reverse(a1.begin(), a1.end());
    reverse(a2.begin(), a2.end());

    cout << dp[n][m] << "\n";
    cout << a1 << "\n";
    cout << a2 << "\n";
}

void solve_local(const string& s1, const string& s2) {
    size_t n = s1.size();
    size_t m = s2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    int max_score = 0;
    size_t max_i = 0, max_j = 0;

    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= m; ++j) {
            int diag = dp[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? MATCH : MISMATCH);
            int up = dp[i - 1][j] + GAP;
            int left = dp[i][j - 1] + GAP;
            dp[i][j] = max({0, diag, up, left});

            if (dp[i][j] > max_score) {
                max_score = dp[i][j];
                max_i = i;
                max_j = j;
            }
        }
    }

    // Traceback from max_i, max_j until 0
    string a1 = "", a2 = "";
    size_t i = max_i, j = max_j;
    while (i > 0 && j > 0 && dp[i][j] > 0) {
        if (dp[i][j] == dp[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? MATCH : MISMATCH)) {
            a1.push_back(s1[i - 1]);
            a2.push_back(s2[j - 1]);
            --i; --j;
        } else if (dp[i][j] == dp[i - 1][j] + GAP) {
            a1.push_back(s1[i - 1]);
            a2.push_back('-');
            --i;
        } else {
            a1.push_back('-');
            a2.push_back(s2[j - 1]);
            --j;
        }
    }

    reverse(a1.begin(), a1.end());
    reverse(a2.begin(), a2.end());

    cout << max_score << "\n";
    cout << a1 << "\n";
    cout << a2 << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string mode, s1, s2;
    if (!(cin >> mode >> s1 >> s2)) return 0;

    if (mode == "GLOBAL") {
        solve_global(s1, s2);
    } else {
        solve_local(s1, s2);
    }

    return 0;
}
