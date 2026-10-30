#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

struct NFATransition {
    char ch; // '#' denotes epsilon
    int to;
};

struct NFAState {
    vector<NFATransition> trans;
    bool is_accept = false;
};

// Compute epsilon-closure of a set of NFA states
set<int> epsilon_closure(const set<int>& states, const vector<NFAState>& nfa) {
    set<int> closure = states;
    queue<int> q;
    for (int s : states) {
        q.push(s);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const auto& tr : nfa[static_cast<size_t>(u)].trans) {
            if (tr.ch == '#' && closure.find(tr.to) == closure.end()) {
                closure.insert(tr.to);
                q.push(tr.to);
            }
        }
    }
    return closure;
}

// Move operation: transition on char 'c' from states
set<int> move_states(const set<int>& states, char c, const vector<NFAState>& nfa) {
    set<int> result;
    for (int s : states) {
        for (const auto& tr : nfa[static_cast<size_t>(s)].trans) {
            if (tr.ch == c) {
                result.insert(tr.to);
            }
        }
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n_states = 0;
    if (!(cin >> n_states)) return 0;
    int start_state = 0;
    cin >> start_state;
    int num_accept = 0;
    cin >> num_accept;
    set<int> nfa_accept;
    for (int i = 0; i < num_accept; ++i) {
        int acc = 0;
        cin >> acc;
        nfa_accept.insert(acc);
    }

    vector<NFAState> nfa(static_cast<size_t>(n_states));
    for (int acc : nfa_accept) {
        nfa[static_cast<size_t>(acc)].is_accept = true;
    }

    int num_transitions = 0;
    cin >> num_transitions;
    set<char> alphabet;
    for (int i = 0; i < num_transitions; ++i) {
        int u = 0, v = 0;
        char c = 0;
        cin >> u >> v >> c;
        nfa[static_cast<size_t>(u)].trans.push_back({c, v});
        if (c != '#') {
            alphabet.insert(c);
        }
    }

    // Subset Construction: NFA -> DFA
    map<set<int>, int> dfa_state_map;
    vector<set<int>> dfa_states;
    vector<bool> dfa_accept;
    vector<map<char, int>> dfa_trans;

    set<int> start_set = epsilon_closure({start_state}, nfa);
    dfa_state_map[start_set] = 0;
    dfa_states.push_back(start_set);
    dfa_trans.emplace_back();

    bool start_acc = false;
    for (int s : start_set) {
        if (nfa_accept.find(s) != nfa_accept.end()) {
            start_acc = true;
            break;
        }
    }
    dfa_accept.push_back(start_acc);

    queue<int> work_queue;
    work_queue.push(0);

    while (!work_queue.empty()) {
        int curr_id = work_queue.front();
        work_queue.pop();
        const set<int> curr_set = dfa_states[static_cast<size_t>(curr_id)];

        for (char c : alphabet) {
            set<int> nxt = epsilon_closure(move_states(curr_set, c, nfa), nfa);
            if (nxt.empty()) continue;

            int nxt_id = 0;
            auto it = dfa_state_map.find(nxt);
            if (it == dfa_state_map.end()) {
                nxt_id = static_cast<int>(dfa_states.size());
                dfa_state_map[nxt] = nxt_id;
                dfa_states.push_back(nxt);
                dfa_trans.emplace_back();

                bool is_acc = false;
                for (int s : nxt) {
                    if (nfa_accept.find(s) != nfa_accept.end()) {
                        is_acc = true;
                        break;
                    }
                }
                dfa_accept.push_back(is_acc);
                work_queue.push(nxt_id);
            } else {
                nxt_id = it->second;
            }
            dfa_trans[static_cast<size_t>(curr_id)][c] = nxt_id;
        }
    }

    cout << "DFA states: " << dfa_states.size() << "\n";
    int dfa_acc_count = 0;
    for (bool b : dfa_accept) if (b) ++dfa_acc_count;
    cout << "DFA accept states: " << dfa_acc_count << "\n";

    // Simulate queries on DFA
    int num_queries = 0;
    if (cin >> num_queries) {
        for (int q = 0; q < num_queries; ++q) {
            string w;
            cin >> w;
            if (w == "EPS") w = "";
            int state = 0;
            bool ok = true;
            for (char ch : w) {
                const auto& tr = dfa_trans[static_cast<size_t>(state)];
                auto it = tr.find(ch);
                if (it == tr.end()) {
                    ok = false;
                    break;
                }
                state = it->second;
            }
            if (ok && dfa_accept[static_cast<size_t>(state)]) {
                cout << "ACCEPT\n";
            } else {
                cout << "REJECT\n";
            }
        }
    }

    return 0;
}
