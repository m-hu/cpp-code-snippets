#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; if (!(cin >> n)) return 0;
    vector<int> p(n), d(n, -1);
    for (int i = 0; i < n; i++) p[i] = i;
    auto print = [&]() {
        for (int i = 0; i < n; i++) { if (i) cout << ' '; cout << p[i]; }
        cout << "\n";
    };
    print();
    while (true) {
        int mob = -1, mobpos = -1;
        for (int i = 0; i < n; i++) {
            int v = p[i], j = i + d[v];
            if (j >= 0 && j < n && p[j] < v && v > mob) { mob = v; mobpos = i; }
        }
        if (mob < 0) break;
        int j = mobpos + d[mob];
        swap(p[mobpos], p[j]);
        for (int v = 0; v < n; v++) if (v > mob) d[v] = -d[v];
        print();
    }
    return 0;
}
