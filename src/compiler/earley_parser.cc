#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <tuple>

using namespace std;

struct EarleyItem {
    int rule_id;  // index in rules
    int dot;      // index in rhs
    int origin;   // start index in input

    bool operator<(const EarleyItem& other) const {
        return tie(rule_id, dot, origin) < tie(other.rule_id, other.dot, other.origin);
    }
};

struct Production {
    char lhs;
    string rhs; // empty or "#" for epsilon
};

bool is_terminal_symbol(char c) {
    return (c < 'A' || c > 'Z') && c != '#';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int num_rules = 0;
    if (!(cin >> num_rules)) return 0;
    char start_symbol = 0;
    cin >> start_symbol;

    vector<Production> prods;
    // Add augmented start rule: gamma -> start_symbol
    prods.push_back({'@', string(1, start_symbol)});

    for (int i = 0; i < num_rules; ++i) {
        char lhs = 0;
        string arrow, rhs;
        cin >> lhs >> arrow >> rhs;
        if (rhs == "#") rhs = "";
        prods.push_back({lhs, rhs});
    }

    int num_queries = 0;
    if (cin >> num_queries) {
        for (int q = 0; q < num_queries; ++q) {
            string w;
            cin >> w;
            if (w == "EPS") w = "";

            size_t n = w.size();
            // Chart: S[0..n]
            vector<vector<EarleyItem>> chart(n + 1);
            vector<set<EarleyItem>> in_chart(n + 1);

            auto add_item = [&](size_t idx, const EarleyItem& item) {
                if (in_chart[idx].insert(item).second) {
                    chart[idx].push_back(item);
                }
            };

            // Initial state: (@ -> . start_symbol, 0) in chart[0]
            add_item(0, {0, 0, 0});

            size_t total_items = 0;

            for (size_t k = 0; k <= n; ++k) {
                for (size_t i = 0; i < chart[k].size(); ++i) {
                    EarleyItem it = chart[k][i];
                    const Production& prod = prods[static_cast<size_t>(it.rule_id)];

                    if (static_cast<size_t>(it.dot) < prod.rhs.size()) {
                        char next_sym = prod.rhs[static_cast<size_t>(it.dot)];

                        if (!is_terminal_symbol(next_sym)) {
                            // Predictor
                            for (size_t r = 0; r < prods.size(); ++r) {
                                if (prods[r].lhs == next_sym) {
                                    add_item(k, {static_cast<int>(r), 0, static_cast<int>(k)});
                                }
                            }
                        } else {
                            // Scanner
                            if (k < n && w[k] == next_sym) {
                                add_item(k + 1, {it.rule_id, it.dot + 1, it.origin});
                            }
                        }
                    } else {
                        // Completer
                        char completed_lhs = prod.lhs;
                        size_t origin_k = static_cast<size_t>(it.origin);
                        size_t origin_items = chart[origin_k].size();
                        for (size_t j = 0; j < origin_items; ++j) {
                            EarleyItem prev = chart[origin_k][j];
                            const Production& prev_prod = prods[static_cast<size_t>(prev.rule_id)];
                            if (static_cast<size_t>(prev.dot) < prev_prod.rhs.size() &&
                                prev_prod.rhs[static_cast<size_t>(prev.dot)] == completed_lhs) {
                                add_item(k, {prev.rule_id, prev.dot + 1, prev.origin});
                            }
                        }
                    }
                }
                total_items += chart[k].size();
            }

            bool accepted = false;
            for (const auto& it : chart[n]) {
                if (it.rule_id == 0 && static_cast<size_t>(it.dot) == 1 && it.origin == 0) {
                    accepted = true;
                    break;
                }
            }

            if (accepted) {
                cout << "ACCEPT " << total_items << "\n";
            } else {
                cout << "REJECT " << total_items << "\n";
            }
        }
    }

    return 0;
}
