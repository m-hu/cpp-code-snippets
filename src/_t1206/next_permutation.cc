#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string mode; if (!(cin >> mode)) return 0;
    if (mode == "P") {
        int n; cin >> n;
        vector<int> p(n);
        for (int i = 0; i < n; i++) cin >> p[i];
        int i = n - 2;
        while (i >= 0 && p[i] >= p[i+1]) i--;
        if (i < 0) { cout << "NONE\n"; return 0; }
        int j = n - 1;
        while (p[j] <= p[i]) j--;
        swap(p[i], p[j]);
        reverse(p.begin() + i + 1, p.end());
        for (int k = 0; k < n; k++) { if (k) cout << ' '; cout << p[k]; }
        cout << "\n";
    } else {
        int n, r; cin >> n >> r;
        vector<int> c(r);
        for (int i = 0; i < r; i++) cin >> c[i];
        int i = r - 1;
        while (i >= 0 && c[i] == n - r + i) i--;
        if (i < 0) { cout << "NONE\n"; return 0; }
        c[i]++;
        for (int j = i + 1; j < r; j++) c[j] = c[j-1] + 1;
        for (int k = 0; k < r; k++) { if (k) cout << ' '; cout << c[k]; }
        cout << "\n";
    }
    return 0;
}
