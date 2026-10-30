#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, T; double eta;
    if (!(cin >> n >> T >> eta)) return 0;
    vector<vector<double>> g(T, vector<double>(n));
    for (int t = 0; t < T; t++) for (int i = 0; i < n; i++) cin >> g[t][i];
    vector<double> w(n, 1.0);
    for (int t = 0; t < T; t++)
        for (int i = 0; i < n; i++) w[i] *= 1 + eta * g[t][i];
    double s = 0;
    for (int i = 0; i < n; i++) s += w[i];
    cout << fixed << setprecision(6);
    for (int i = 0; i < n; i++) { if (i) cout << ' '; cout << w[i] / s + 0.0; }
    cout << "\n";
    return 0;
}
