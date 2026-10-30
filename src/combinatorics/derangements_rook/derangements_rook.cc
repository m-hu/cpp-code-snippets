#include <iostream>
#include <string>
#include <vector>
using namespace std;
using int64 = long long;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string mode; if (!(cin >> mode)) return 0;
    if (mode == "D") {
        int n; cin >> n;
        vector<int64> D(max(n + 1, 2), 0);
        D[0] = 1;
        if (n >= 1) D[1] = 0;
        for (int i = 2; i <= n; i++) D[i] = (int64)(i - 1) * (D[i-1] + D[i-2]);
        cout << D[n] << "\n";
    } else {
        int rows, cols; cin >> rows >> cols;
        vector<vector<int>> b(rows, vector<int>(cols));
        for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) cin >> b[i][j];
        vector<int64> dp(1 << cols, 0);
        dp[0] = 1;
        for (int i = 0; i < rows; i++) {
            vector<int64> ndp = dp;
            for (int mask = 0; mask < (1 << cols); mask++) {
                if (dp[mask] == 0) continue;
                for (int j = 0; j < cols; j++)
                    if (b[i][j] && !(mask & (1 << j))) ndp[(size_t)(mask | (1 << j))] += dp[mask];
            }
            dp = ndp;
        }
        int m = min(rows, cols);
        vector<int64> r(m + 1, 0);
        for (int mask = 0; mask < (1 << cols); mask++) {
            int c = 0;
            for (int j = 0; j < cols; j++) if (mask & (1 << j)) c++;
            r[c] += dp[mask];
        }
        for (int i = 0; i <= m; i++) { if (i) cout << ' '; cout << r[i]; }
        cout << "\n";
    }
    return 0;
}
