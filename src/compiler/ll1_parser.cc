#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

struct Production {
    char lhs;
    string rhs; // "#" for epsilon
};

bool is_terminal(char c) {
    return (c < 'A' || c > 'Z') && c != '#';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int num_prods = 0;
    if (!(cin >> num_prods)) return 0;
    char start_symbol = 0;
    cin >> start_symbol;

    vector<Production> prods(static_cast<size_t>(num_prods));
    set<char> non_terminals;
    set<char> terminals;
    terminals.insert('$');

    for (int i = 0; i < num_prods; ++i) {
        char lhs = 0;
        string arrow, rhs;
        cin >> lhs >> arrow >> rhs;
        prods[static_cast<size_t>(i)] = {lhs, rhs};
        non_terminals.insert(lhs);
        for (char c : rhs) {
            if (is_terminal(c)) {
                terminals.insert(c);
            } else if (c != '#') {
                non_terminals.insert(c);
            }
        }
    }

    // Step 1: FIRST sets
    map<char, set<char>> first;
    for (char t : terminals) {
        first[t].insert(t);
    }

    bool changed = true;
    while (changed) {
        changed = false;
        for (const auto& prod : prods) {
            char A = prod.lhs;
            const string& rhs = prod.rhs;
            size_t old_size = first[A].size();

            if (rhs == "#") {
                first[A].insert('#');
            } else {
                bool all_eps = true;
                for (char sym : rhs) {
                    bool sym_has_eps = false;
                    for (char f : first[sym]) {
                        if (f == '#') {
                            sym_has_eps = true;
                        } else {
                            first[A].insert(f);
                        }
                    }
                    if (!sym_has_eps) {
                        all_eps = false;
                        break;
                    }
                }
                if (all_eps) {
                    first[A].insert('#');
                }
            }

            if (first[A].size() > old_size) {
                changed = true;
            }
        }
    }

    // Function to compute FIRST of a string of symbols
    auto first_of_string = [&](const string& s) -> set<char> {
        set<char> res;
        if (s == "#" || s.empty()) {
            res.insert('#');
            return res;
        }
        bool all_eps = true;
        for (char sym : s) {
            bool sym_has_eps = false;
            for (char f : first[sym]) {
                if (f == '#') {
                    sym_has_eps = true;
                } else {
                    res.insert(f);
                }
            }
            if (!sym_has_eps) {
                all_eps = false;
                break;
            }
        }
        if (all_eps) {
            res.insert('#');
        }
        return res;
    };

    // Step 2: FOLLOW sets
    map<char, set<char>> follow;
    follow[start_symbol].insert('$');

    changed = true;
    while (changed) {
        changed = false;
        for (const auto& prod : prods) {
            char A = prod.lhs;
            const string& rhs = prod.rhs;
            if (rhs == "#") continue;

            for (size_t i = 0; i < rhs.size(); ++i) {
                char B = rhs[i];
                if (is_terminal(B)) continue;

                size_t old_size = follow[B].size();
                string rest = rhs.substr(i + 1);
                set<char> first_rest = first_of_string(rest);

                for (char f : first_rest) {
                    if (f != '#') {
                        follow[B].insert(f);
                    }
                }

                if (first_rest.find('#') != first_rest.end()) {
                    for (char fol : follow[A]) {
                        follow[B].insert(fol);
                    }
                }

                if (follow[B].size() > old_size) {
                    changed = true;
                }
            }
        }
    }

    // Step 3: LL(1) Table construction
    map<pair<char, char>, int> table;
    bool is_ll1 = true;

    for (size_t idx = 0; idx < prods.size(); ++idx) {
        char A = prods[idx].lhs;
        set<char> f_rhs = first_of_string(prods[idx].rhs);

        for (char a : f_rhs) {
            if (a != '#') {
                auto key = make_pair(A, a);
                if (table.find(key) != table.end() && table[key] != static_cast<int>(idx)) {
                    is_ll1 = false;
                }
                table[key] = static_cast<int>(idx);
            }
        }

        if (f_rhs.find('#') != f_rhs.end()) {
            for (char b : follow[A]) {
                auto key = make_pair(A, b);
                if (table.find(key) != table.end() && table[key] != static_cast<int>(idx)) {
                    is_ll1 = false;
                }
                table[key] = static_cast<int>(idx);
            }
        }
    }

    if (!is_ll1) {
        cout << "GRAMMAR IS NOT LL1\n";
        return 0;
    }
    cout << "GRAMMAR IS LL1\n";

    // Step 4: Parse queries
    int num_queries = 0;
    if (cin >> num_queries) {
        for (int q = 0; q < num_queries; ++q) {
            string w;
            cin >> w;
            w.push_back('$');

            vector<char> stack;
            stack.push_back('$');
            stack.push_back(start_symbol);

            size_t ip = 0;
            vector<int> derivations;
            bool ok = true;

            while (!stack.empty()) {
                char X = stack.back();
                stack.pop_back();

                char a = (ip < w.size()) ? w[ip] : '$';

                if (X == a) {
                    ++ip;
                    if (X == '$') break;
                } else if (is_terminal(X)) {
                    ok = false;
                    break;
                } else {
                    auto key = make_pair(X, a);
                    if (table.find(key) == table.end()) {
                        ok = false;
                        break;
                    }
                    int rule_idx = table[key];
                    derivations.push_back(rule_idx);
                    const string& rhs = prods[static_cast<size_t>(rule_idx)].rhs;
                    if (rhs != "#") {
                        for (int k = static_cast<int>(rhs.size()) - 1; k >= 0; --k) {
                            stack.push_back(rhs[static_cast<size_t>(k)]);
                        }
                    }
                }
            }

            if (ok && ip == w.size()) {
                for (size_t d = 0; d < derivations.size(); ++d) {
                    if (d > 0) cout << " ";
                    cout << "r" << derivations[d];
                }
                cout << "\n";
            } else {
                cout << "SYNTAX ERROR\n";
            }
        }
    }

    return 0;
}
