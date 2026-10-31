#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, d, k, iters;
    if (!(cin >> n >> d >> k >> iters)) return 0;
    vector<vector<double>> pts(n, vector<double>(d));
    for (int i = 0; i < n; i++) for (int j = 0; j < d; j++) cin >> pts[i][j];
    vector<vector<double>> c(k, vector<double>(d));
    for (int j = 0; j < d; j++) for (int cc = 0; cc < k; cc++) c[cc][j] = pts[cc][j];
    vector<int> asg(n, 0);
    for (int t = 0; t < iters; t++) {
        for (int i = 0; i < n; i++) {
            double best = -1; int bi = 0;
            for (int cc = 0; cc < k; cc++) {
                double dd = 0;
                for (int j = 0; j < d; j++) dd += (pts[i][j]-c[cc][j])*(pts[i][j]-c[cc][j]);
                if (best < 0 || dd < best) { best = dd; bi = cc; }
            }
            asg[i] = bi;
        }
        for (int cc = 0; cc < k; cc++) {
            vector<double> s(d, 0); int cnt = 0;
            for (int i = 0; i < n; i++) if (asg[i] == cc) {
                for (int j = 0; j < d; j++) s[j] += pts[i][j];
                cnt++;
            }
            if (cnt) for (int j = 0; j < d; j++) c[cc][j] = s[j] / cnt;
        }
    }
    for (int i = 0; i < n; i++) { if (i) cout << ' '; cout << asg[i]; }
    cout << "\n" << fixed << setprecision(4);
    for (int cc = 0; cc < k; cc++) {
        for (int j = 0; j < d; j++) { if (j) cout << ' '; cout << c[cc][j] + 0.0; }
        cout << "\n";
    }
    return 0;
}
