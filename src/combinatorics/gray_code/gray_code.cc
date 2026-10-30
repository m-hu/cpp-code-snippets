#include <iostream>
#include <string>
using namespace std;
int grayToBin(int g) {
    int b = g;
    for (g >>= 1; g; g >>= 1) b ^= g;
    return b;
}
string fmtGray(int g, int n) {
    string s;
    for (int i = n - 1; i >= 0; i--) s.push_back(((g >> i) & 1) ? '1' : '0');
    return s;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string mode; if (!(cin >> mode)) return 0;
    if (mode == "G") {
        int n; cin >> n;
        for (int i = 0; i < (1 << n); i++) cout << fmtGray(i ^ (i >> 1), n) << "\n";
    } else if (mode == "R") {
        string g; cin >> g;
        int v = 0;
        for (char c : g) v = v * 2 + (c - '0');
        cout << grayToBin(v) << "\n";
    } else {
        int n, r; cin >> n >> r;
        cout << fmtGray(r ^ (r >> 1), n) << "\n";
    }
    return 0;
}
