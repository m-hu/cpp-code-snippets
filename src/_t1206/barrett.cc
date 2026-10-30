#include <iostream>
using namespace std;
using int64 = long long;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int64 x, m; if (!(cin >> x >> m)) return 0;
    int64 mu = ((int64)1 << 32) / m;
    int64 q = (x * mu) >> 32;
    int64 r = x - q * m;
    while (r < 0) { r += m; q--; }
    while (r >= m) { r -= m; q++; }
    cout << q << " " << r << "\n";
    return 0;
}
