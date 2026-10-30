#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

struct Rule {
    char lhs;
    char rhs1;
    char rhs2; // 0 if terminal rule
    char term; // 0 if nonterminal rule
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int num_rules = 0;
    if (!(cin >> num_rules)) return 0;
    char start_symbol = 0;
    cin >> start_symbol;

    vector<Rule> rules;
    for (int i = 0; i < num_rules; ++i) {
        char lhs = 0;
        string arrow, rhs;
        cin >> lhs >> arrow >> rhs;
        if (rhs.size() == 1) {
            rules.push_back({lhs, 0, 0, rhs[0]});
        } else if (rhs.size() == 2) {
            rules.push_back({lhs, rhs[0], rhs[1], 0});
        }
    }

    int num_queries = 0;
    if (cin >> num_queries) {
        for (int q = 0; q < num_queries; ++q) {
            string w;
            cin >> w;
            int n = static_cast<int>(w.size());
            if (n == 0) {
                cout << "NO 0\n";
                continue;
            }

            // dp[len][i][A] = number of parse trees for substring of length len starting at i
            // len in 1..n, i in 0..n-len
            // Let's use 256 for ASCII char index
            vector<vector<vector<long long>>> dp(
                static_cast<size_t>(n + 1),
                vector<vector<long long>>(static_cast<size_t>(n), vector<long long>(256, 0))
            );

            // Base case: length 1
            for (int i = 0; i < n; ++i) {
                char ch = w[static_cast<size_t>(i)];
                for (const auto& r : rules) {
                    if (r.term == ch) {
                        dp[1][static_cast<size_t>(i)][static_cast<unsigned char>(r.lhs)] += 1;
                    }
                }
            }

            // DP transitions: len 2 to n
            const long long MOD = 1000000007;
            for (int len = 2; len <= n; ++len) {
                for (int i = 0; i <= n - len; ++i) {
                    for (int k = 1; k < len; ++k) {
                        int left_len = k;
                        int right_len = len - k;
                        int left_start = i;
                        int right_start = i + k;

                        for (const auto& r : rules) {
                            if (r.rhs1 != 0) {
                                long long left_ways = dp[static_cast<size_t>(left_len)][static_cast<size_t>(left_start)][static_cast<unsigned char>(r.rhs1)];
                                if (left_ways == 0) continue;
                                long long right_ways = dp[static_cast<size_t>(right_len)][static_cast<size_t>(right_start)][static_cast<unsigned char>(r.rhs2)];
                                if (right_ways == 0) continue;

                                long long add = (left_ways % MOD) * (right_ways % MOD) % MOD;
                                dp[static_cast<size_t>(len)][static_cast<size_t>(i)][static_cast<unsigned char>(r.lhs)] =
                                    (dp[static_cast<size_t>(len)][static_cast<size_t>(i)][static_cast<unsigned char>(r.lhs)] + add) % MOD;
                            }
                        }
                    }
                }
            }

            long long ways = dp[static_cast<size_t>(n)][0][static_cast<unsigned char>(start_symbol)];
            if (ways > 0) {
                cout << "YES " << ways << "\n";
            } else {
                cout << "NO 0\n";
            }
        }
    }

    return 0;
}
