#include <iostream>
#include <string>
#include <vector>
using namespace std;
using u32 = unsigned int;
struct MT {
    vector<u32> mt;
    int idx;
    MT(u32 seed) : mt(624), idx(624) {
        mt[0] = seed;
        for (int i = 1; i < 624; i++)
            mt[i] = 1812433253u * (mt[i-1] ^ (mt[i-1] >> 30)) + (u32)i;
    }
    void twist() {
        for (int i = 0; i < 624; i++) {
            u32 y = (mt[i] & 0x80000000u) | (mt[(i+1)%624] & 0x7fffffffu);
            mt[i] = mt[(i+397)%624] ^ (y >> 1);
            if (y & 1) mt[i] ^= 0x9908b0dfu;
        }
        idx = 0;
    }
    u32 next() {
        if (idx >= 624) twist();
        u32 y = mt[idx++];
        y ^= y >> 11; y ^= (y << 7) & 0x9d2c5680u;
        y ^= (y << 15) & 0xefc60000u; y ^= y >> 18;
        return y;
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string mode; if (!(cin >> mode)) return 0;
    if (mode == "L") {
        long long a, c, m, seed; int n;
        cin >> a >> c >> m >> seed >> n;
        long long x = seed;
        for (int i = 0; i < n; i++) {
            x = (a * x + c) % m;
            if (i) cout << ' ';
            cout << x;
        }
        cout << "\n";
    } else {
        unsigned int seed; int n;
        cin >> seed >> n;
        MT mt(seed);
        for (int i = 0; i < n; i++) {
            if (i) cout << ' ';
            cout << mt.next();
        }
        cout << "\n";
    }
    return 0;
}
