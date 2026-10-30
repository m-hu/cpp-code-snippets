#include <iostream>
#include <vector>
using namespace std;
using int64 = long long;
bool ll_prime(int64 p) {
    if (p == 2) return true;
    int64 M = ((int64)1 << p) - 1;
    int64 s = 4;
    for (int64 i = 0; i < p - 2; i++) s = (int64)((__int128)s * s % M + M - 2) % M;
    return s == 0;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int64 p;
    bool any = false;
    while (cin >> p) { any = true; cout << (ll_prime(p) ? "PRIME" : "COMPOSITE") << "\n"; }
    return 0;
}
