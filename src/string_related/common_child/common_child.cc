// https://www.hackerrank.com/challenges/common-child/problem
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string A, B;
    if (!(cin >> A >> B)) return 0;

    size_t n = A.length();
    size_t m = B.length();

    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= m; j++) {
            if (A[i - 1] == B[j - 1]) {
                curr[j] = prev[j - 1] + 1;
            } else {
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }
        prev = curr;
    }

    cout << prev[m] << "\n";
    return 0;
}
