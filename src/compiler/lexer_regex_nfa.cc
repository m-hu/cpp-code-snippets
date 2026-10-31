#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <set>
#include <queue>

using namespace std;

struct Transition {
    char ch; // 0 for epsilon
    int to;
};

struct State {
    vector<Transition> trans;
};

vector<State> nfa;

int add_state() {
    nfa.emplace_back();
    return (int)nfa.size() - 1;
}

void add_trans(int from, int to, char ch) {
    nfa[static_cast<size_t>(from)].trans.push_back({ch, to});
}

struct Frag {
    int start;
    int end;
};

int get_prec(char c) {
    if (c == '*') return 3;
    if (c == '.') return 2; // explicit concat
    if (c == '|') return 1;
    return 0;
}

string insert_concat(const string& regex) {
    string res = "";
    for (size_t i = 0; i < regex.size(); ++i) {
        char c1 = regex[i];
        res += c1;
        if (i + 1 < regex.size()) {
            char c2 = regex[i + 1];
            bool c1_can_end = (isalnum(c1) || c1 == '*' || c1 == ')');
            bool c2_can_start = (isalnum(c2) || c2 == '(');
            if (c1_can_end && c2_can_start) {
                res += '.';
            }
        }
    }
    return res;
}

string to_postfix(const string& infix) {
    string postfix = "";
    stack<char> op_stack;
    for (char c : infix) {
        if (isalnum(c)) {
            postfix += c;
        } else if (c == '(') {
            op_stack.push(c);
        } else if (c == ')') {
            while (!op_stack.empty() && op_stack.top() != '(') {
                postfix += op_stack.top();
                op_stack.pop();
            }
            if (!op_stack.empty()) op_stack.pop();
        } else {
            while (!op_stack.empty() && op_stack.top() != '(' &&
                   get_prec(op_stack.top()) >= get_prec(c)) {
                postfix += op_stack.top();
                op_stack.pop();
            }
            op_stack.push(c);
        }
    }
    while (!op_stack.empty()) {
        postfix += op_stack.top();
        op_stack.pop();
    }
    return postfix;
}

Frag build_nfa(const string& postfix) {
    stack<Frag> st;
    for (char c : postfix) {
        if (c == '.') {
            Frag f2 = st.top(); st.pop();
            Frag f1 = st.top(); st.pop();
            add_trans(f1.end, f2.start, 0);
            st.push({f1.start, f2.end});
        } else if (c == '|') {
            Frag f2 = st.top(); st.pop();
            Frag f1 = st.top(); st.pop();
            int s = add_state();
            int e = add_state();
            add_trans(s, f1.start, 0);
            add_trans(s, f2.start, 0);
            add_trans(f1.end, e, 0);
            add_trans(f2.end, e, 0);
            st.push({s, e});
        } else if (c == '*') {
            Frag f = st.top(); st.pop();
            int s = add_state();
            int e = add_state();
            add_trans(s, f.start, 0);
            add_trans(s, e, 0);
            add_trans(f.end, f.start, 0);
            add_trans(f.end, e, 0);
            st.push({s, e});
        } else {
            int s = add_state();
            int e = add_state();
            add_trans(s, e, c);
            st.push({s, e});
        }
    }
    return st.top();
}

void get_closure(int s, set<int>& closure) {
    if (closure.count(s)) return;
    closure.insert(s);
    for (auto& tr : nfa[static_cast<size_t>(s)].trans) {
        if (tr.ch == 0) {
            get_closure(tr.to, closure);
        }
    }
}

bool match(const Frag& nfa_frag, const string& s) {
    set<int> current;
    get_closure(nfa_frag.start, current);

    for (char c : s) {
        set<int> next_states;
        for (int state : current) {
            for (auto& tr : nfa[static_cast<size_t>(state)].trans) {
                if (tr.ch == c) {
                    get_closure(tr.to, next_states);
                }
            }
        }
        current = std::move(next_states);
        if (current.empty()) return false;
    }
    return current.count(nfa_frag.end) > 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string pattern;
    if (!(cin >> pattern)) return 0;
    string infix = insert_concat(pattern);
    string postfix = to_postfix(infix);
    nfa.clear();
    Frag frag = build_nfa(postfix);

    int k;
    if (cin >> k) {
        for (int i = 0; i < k; ++i) {
            string test_str;
            cin >> test_str;
            if (test_str == "EPS") test_str = "";
            cout << (match(frag, test_str) ? "MATCH" : "NO_MATCH") << "\n";
        }
    }
    return 0;
}
