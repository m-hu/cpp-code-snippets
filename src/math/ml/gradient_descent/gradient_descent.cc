#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; if (!(cin >> n)) return 0;
    vector<vector<double>> A(n, vector<double>(n));
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> A[i][j];
    vector<double> b(n), x(n);
    for (int i = 0; i < n; i++) cin >> b[i];
    for (int i = 0; i < n; i++) cin >> x[i];
    double lr; int iters; cin >> lr >> iters;
    for (int t = 0; t < iters; t++) {
        vector<double> g(n, 0);
        for (int i = 0; i < n; i++) {
            double s = 0;
            for (int j = 0; j < n; j++) s += A[i][j] * x[j];
            g[i] = 2 * s + b[i];
        }
        for (int i = 0; i < n; i++) x[i] -= lr * g[i];
    }
    double f = 0;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) f += x[i] * A[i][j] * x[j];
    for (int i = 0; i < n; i++) f += b[i] * x[i];
    cout << fixed << setprecision(6);
    for (int i = 0; i < n; i++) { if (i) cout << ' '; cout << x[i] + 0.0; }
    cout << "\n" << f + 0.0 << "\n";
    return 0;
}
