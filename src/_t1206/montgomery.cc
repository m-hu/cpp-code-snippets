#include <iostream>
using namespace std;
using int64 = long long;
const int64 R = 256;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int64 a, b, m; if (!(cin >> a >> b >> m)) return 0;
    int64 minv = 1;
    for (int64 x = 1; x < R; x++) if ((m * x) % R == 1) { minv = x; break; }
    int64 mp = (R - minv) % R;
    auto redc = [&](int64 T) {
        int64 q = ((T & 255) * mp) & 255;
        int64 t = (T + q * m) >> 8;
        if (t >= m) t -= m;
        return t;
    };
    int64 aM = ((a % m) * R) % m, bM = ((b % m) * R) % m;
    int64 abM = redc(aM * bM), ab = redc(abM);
    cout << aM << " " << bM << "\n" << abM << "\n" << ab << "\n";
    return 0;
}
