#include <iostream>
#include <string>
#include <vector>
using namespace std;
using int64 = long long;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string mode; if (!(cin >> mode)) return 0;
    if (mode == "S2") {
        int n, k; cin >> n >> k;
        vector<vector<int64>> S(n + 1, vector<int64>(k + 1, 0));
        S[0][0] = 1;
        for (int i = 1; i <= n; i++) for (int j = 1; j <= min(i, k); j++)
            S[i][j] = (int64)j * S[i-1][j] + S[i-1][j-1];
        cout << S[n][k] << "\n";
    } else if (mode == "S1") {
        int n, k; cin >> n >> k;
        vector<vector<int64>> s(n + 1, vector<int64>(k + 1, 0));
        s[0][0] = 1;
        for (int i = 1; i <= n; i++) for (int j = 1; j <= min(i, k); j++)
            s[i][j] = -(int64)(i - 1) * s[i-1][j] + s[i-1][j-1];
        cout << s[n][k] << "\n";
    } else {
        int n; cin >> n;
        vector<vector<int64>> S(n + 1, vector<int64>(n + 1, 0));
        S[0][0] = 1;
        for (int i = 1; i <= n; i++) for (int j = 1; j <= i; j++)
            S[i][j] = (int64)j * S[i-1][j] + S[i-1][j-1];
        int64 b = 0;
        for (int j = 0; j <= n; j++) b += S[n][j];
        cout << b << "\n";
    }
    return 0;
}
