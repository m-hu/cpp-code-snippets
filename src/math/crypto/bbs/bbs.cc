#include <iostream>
#include <string>
using namespace std;
using int64 = long long;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int64 x0, M, cnt; if (!(cin >> x0 >> M >> cnt)) return 0;
    int64 x = x0;
    string bits;
    for (int64 i = 0; i < cnt; i++) {
        x = (int64)((__int128)x * x % M);
        bits.push_back((char)('0' + (x & 1)));
    }
    cout << bits << "\n" << x << "\n";
    return 0;
}
