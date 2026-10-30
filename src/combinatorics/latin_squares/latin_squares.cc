#include <iostream>
#include <vector>
#include <set>
using namespace std;
bool isPrime(int n) {
    if (n < 2) return false;
    for (int d = 2; d * d <= n; d++) if (n % d == 0) return false;
    return true;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; if (!(cin >> n)) return 0;
    if (n == 6) { cout << "NONE\n"; return 0; }
    if (isPrime(n)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) { if (j) cout << ' '; cout << (i + j) % n; }
            cout << "\n";
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) { if (j) cout << ' '; cout << (i + 2 * j) % n; }
            cout << "\n";
        }
        cout << "ORTHOGONAL\n";
    } else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) { if (j) cout << ' '; cout << (i + j) % n; }
            cout << "\n";
        }
        cout << "NO_PAIR\n";
    }
    return 0;
}
