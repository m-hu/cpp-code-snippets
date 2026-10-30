#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0;
    if (!(cin >> n)) return 0;
    int start_state = 0;
    cin >> start_state;
    int num_accept = 0;
    cin >> num_accept;
    set<int> accept_states;
    for (int i = 0; i < num_accept; ++i) {
        int a = 0;
        cin >> a;
        accept_states.insert(a);
    }

    int alpha_size = 0;
    cin >> alpha_size;
    vector<char> alphabet(static_cast<size_t>(alpha_size));
    for (int i = 0; i < alpha_size; ++i) {
        cin >> alphabet[static_cast<size_t>(i)];
    }

    int num_trans = 0;
    cin >> num_trans;
    // trans[u][c] = v (-1 if none)
    vector<map<char, int>> trans(static_cast<size_t>(n));
    // rev_trans[v][c] = list of u
    vector<map<char, vector<int>>> rev_trans(static_cast<size_t>(n));

    for (int i = 0; i < num_trans; ++i) {
        int u = 0, v = 0;
        char c = 0;
        cin >> u >> v >> c;
        trans[static_cast<size_t>(u)][c] = v;
        rev_trans[static_cast<size_t>(v)][c].push_back(u);
    }

    // Step 1: Reachability from start_state
    vector<bool> reachable(static_cast<size_t>(n), false);
    queue<int> q;
    reachable[static_cast<size_t>(start_state)] = true;
    q.push(start_state);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const auto& kv : trans[static_cast<size_t>(u)]) {
            int v = kv.second;
            if (!reachable[static_cast<size_t>(v)]) {
                reachable[static_cast<size_t>(v)] = true;
                q.push(v);
            }
        }
    }

    // Filter states to reachable only
    vector<int> states;
    for (int i = 0; i < n; ++i) {
        if (reachable[static_cast<size_t>(i)]) {
            states.push_back(i);
        }
    }

    // Step 2: Initial partition P = { F, S \ F }
    set<int> F, nonF;
    for (int s : states) {
        if (accept_states.find(s) != accept_states.end()) {
            F.insert(s);
        } else {
            nonF.insert(s);
        }
    }

    vector<set<int>> P;
    queue<set<int>> W;
    if (!F.empty()) {
        P.push_back(F);
    }
    if (!nonF.empty()) {
        P.push_back(nonF);
    }
    if (!F.empty() && !nonF.empty()) {
        if (F.size() <= nonF.size()) {
            W.push(F);
        } else {
            W.push(nonF);
        }
    } else if (!F.empty()) {
        W.push(F);
    } else if (!nonF.empty()) {
        W.push(nonF);
    }

    // Step 3: Hopcroft's refinement loop
    while (!W.empty()) {
        set<int> A = W.front();
        W.pop();

        for (char c : alphabet) {
            // X = { u | delta(u, c) in A }
            set<int> X;
            for (int a : A) {
                auto it = rev_trans[static_cast<size_t>(a)].find(c);
                if (it != rev_trans[static_cast<size_t>(a)].end()) {
                    for (int u : it->second) {
                        if (reachable[static_cast<size_t>(u)]) {
                            X.insert(u);
                        }
                    }
                }
            }

            if (X.empty()) continue;

            vector<set<int>> new_P;
            for (const auto& Y : P) {
                set<int> intersection_set;
                set<int> difference_set;
                for (int y : Y) {
                    if (X.find(y) != X.end()) {
                        intersection_set.insert(y);
                    } else {
                        difference_set.insert(y);
                    }
                }

                if (!intersection_set.empty() && !difference_set.empty()) {
                    new_P.push_back(intersection_set);
                    new_P.push_back(difference_set);

                    // Update W: replace Y with both, or add smaller
                    // Since W holds copies, we check whether Y was in W
                    // A standard Hopcroft queue check:
                    queue<set<int>> next_W;
                    bool in_W = false;
                    while (!W.empty()) {
                        set<int> item = W.front();
                        W.pop();
                        if (item == Y) {
                            in_W = true;
                            next_W.push(intersection_set);
                            next_W.push(difference_set);
                        } else {
                            next_W.push(item);
                        }
                    }
                    W = next_W;

                    if (!in_W) {
                        if (intersection_set.size() <= difference_set.size()) {
                            W.push(intersection_set);
                        } else {
                            W.push(difference_set);
                        }
                    }
                } else {
                    new_P.push_back(Y);
                }
            }
            P = std::move(new_P);
        }
    }

    // Map each state to its partition ID
    vector<int> state_to_part(static_cast<size_t>(n), -1);
    for (size_t pid = 0; pid < P.size(); ++pid) {
        for (int s : P[pid]) {
            state_to_part[static_cast<size_t>(s)] = static_cast<int>(pid);
        }
    }

    int min_start = state_to_part[static_cast<size_t>(start_state)];
    set<int> min_accept;
    for (size_t pid = 0; pid < P.size(); ++pid) {
        for (int s : P[pid]) {
            if (accept_states.find(s) != accept_states.end()) {
                min_accept.insert(static_cast<int>(pid));
                break;
            }
        }
    }

    cout << "Minimal DFA states: " << P.size() << "\n";
    cout << "Accept states: " << min_accept.size() << "\n";

    // Build transitions for minimized DFA
    vector<map<char, int>> min_trans(P.size());
    for (size_t pid = 0; pid < P.size(); ++pid) {
        int rep = *P[pid].begin();
        for (const auto& kv : trans[static_cast<size_t>(rep)]) {
            char c = kv.first;
            int v = kv.second;
            if (reachable[static_cast<size_t>(v)]) {
                min_trans[pid][c] = state_to_part[static_cast<size_t>(v)];
            }
        }
    }

    // Queries
    int num_queries = 0;
    if (cin >> num_queries) {
        for (int q_idx = 0; q_idx < num_queries; ++q_idx) {
            string w;
            cin >> w;
            if (w == "EPS") w = "";
            int curr = min_start;
            bool ok = true;
            for (char ch : w) {
                if (curr < 0 || static_cast<size_t>(curr) >= min_trans.size()) {
                    ok = false;
                    break;
                }
                auto it = min_trans[static_cast<size_t>(curr)].find(ch);
                if (it == min_trans[static_cast<size_t>(curr)].end()) {
                    ok = false;
                    break;
                }
                curr = it->second;
            }
            if (ok && min_accept.find(curr) != min_accept.end()) {
                cout << "ACCEPT\n";
            } else {
                cout << "REJECT\n";
            }
        }
    }

    return 0;
}
