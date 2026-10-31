#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;

    string t = "^";
    for (char c : s) {
        t += "#";
        t += c;
    }
    t += "#$";

    size_t m = t.size();
    vector<int> p(m, 0);
    int c = 0, r = 0;

    for (size_t i = 1; i < m - 1; ++i) {
        int i_mirror = 2 * c - static_cast<int>(i);
        if (static_cast<int>(i) < r) {
            p[i] = min(r - static_cast<int>(i), p[static_cast<size_t>(i_mirror)]);
        }

        while (t[i + 1 + static_cast<size_t>(p[i])] == t[i - 1 - static_cast<size_t>(p[i])]) {
            ++p[i];
        }

        if (static_cast<int>(i) + p[i] > r) {
            c = static_cast<int>(i);
            r = static_cast<int>(i) + p[i];
        }
    }

    int max_len = 0;
    size_t center_idx = 0;
    long long total_palindromes = 0;

    for (size_t i = 1; i < m - 1; ++i) {
        if (p[i] > max_len) {
            max_len = p[i];
            center_idx = i;
        }
        total_palindromes += (p[i] + 1) / 2;
    }

    size_t start_pos = (center_idx - static_cast<size_t>(max_len)) / 2;
    string longest_pal = s.substr(start_pos, static_cast<size_t>(max_len));

    cout << max_len << "\n";
    cout << longest_pal << "\n";
    cout << total_palindromes << "\n";

    return 0;
}
