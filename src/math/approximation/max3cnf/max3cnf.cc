#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
double expectedOf(const vector<vector<int>>& cls, const vector<int>& asg) {
    double tot = 0;
    for (auto& cl : cls) {
        bool sat = false;
        int open = 0;
        for (int lit : cl) {
            int v = abs(lit);
            if (asg[v] >= 0) {
                if ((lit > 0) == (asg[v] == 1)) { sat = true; break; }
            } else open++;
        }
        if (sat) tot += 1.0;
        else if (open > 0) tot += 1.0 - pow(0.5, open);
    }
    return tot;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; if (!(cin >> n >> m)) return 0;
    vector<vector<int>> cls(m, vector<int>(3));
    for (int i = 0; i < m; i++) for (int j = 0; j < 3; j++) cin >> cls[i][j];
    vector<int> asg(n + 1, -1);
    for (int v = 1; v <= n; v++) {
        asg[v] = 1;
        double e1 = expectedOf(cls, asg);
        asg[v] = 0;
        double e0 = expectedOf(cls, asg);
        asg[v] = (e1 >= e0) ? 1 : 0;
    }
    int sat = 0;
    for (auto& cl : cls) {
        bool s = false;
        for (int lit : cl) if ((lit > 0) == (asg[abs(lit)] == 1)) { s = true; break; }
        if (s) sat++;
    }
    for (int v = 1; v <= n; v++) { if (v > 1) cout << ' '; cout << asg[v]; }
    cout << "\n" << sat << "\n";
    return 0;
}
