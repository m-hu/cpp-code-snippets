#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>

using namespace std;

// Grammar:
// 1: E -> E + T
// 2: E -> T
// 3: T -> T * F
// 4: T -> F
// 5: F -> ( E )
// 6: F -> id

struct Production {
    string lhs;
    size_t len;
};

vector<Production> prods = {
    {"", 0},
    {"E -> E + T", 3},
    {"E -> T", 1},
    {"T -> T * F", 3},
    {"T -> F", 1},
    {"F -> ( E )", 3},
    {"F -> id", 1}
};

// SLR(1) Action: positive: shift state, negative: reduce prod -val, 1000: accept, 0: error
map<pair<int, string>, int> action_table;
map<pair<int, string>, int> goto_table;

void init_tables() {
    action_table[{0, "id"}] = 5;
    action_table[{0, "("}] = 4;
    goto_table[{0, "E"}] = 1;
    goto_table[{0, "T"}] = 2;
    goto_table[{0, "F"}] = 3;

    action_table[{1, "+"}] = 6;
    action_table[{1, "$"}] = 1000; // ACC

    action_table[{2, "+"}] = -2; // r(E -> T)
    action_table[{2, "*"}] = 7;
    action_table[{2, ")"}] = -2;
    action_table[{2, "$"}] = -2;

    action_table[{3, "+"}] = -4; // r(T -> F)
    action_table[{3, "*"}] = -4;
    action_table[{3, ")"}] = -4;
    action_table[{3, "$"}] = -4;

    action_table[{4, "id"}] = 5;
    action_table[{4, "("}] = 4;
    goto_table[{4, "E"}] = 8;
    goto_table[{4, "T"}] = 2;
    goto_table[{4, "F"}] = 3;

    action_table[{5, "+"}] = -6; // r(F -> id)
    action_table[{5, "*"}] = -6;
    action_table[{5, ")"}] = -6;
    action_table[{5, "$"}] = -6;

    action_table[{6, "id"}] = 5;
    action_table[{6, "("}] = 4;
    goto_table[{6, "T"}] = 9;
    goto_table[{6, "F"}] = 3;

    action_table[{7, "id"}] = 5;
    action_table[{7, "("}] = 4;
    goto_table[{7, "F"}] = 10;

    action_table[{8, "+"}] = 6;
    action_table[{8, ")"}] = 11;

    action_table[{9, "+"}] = -1; // r(E -> E + T)
    action_table[{9, "*"}] = 7;
    action_table[{9, ")"}] = -1;
    action_table[{9, "$"}] = -1;

    action_table[{10, "+"}] = -3; // r(T -> T * F)
    action_table[{10, "*"}] = -3;
    action_table[{10, ")"}] = -3;
    action_table[{10, "$"}] = -3;

    action_table[{11, "+"}] = -5; // r(F -> ( E ))
    action_table[{11, "*"}] = -5;
    action_table[{11, ")"}] = -5;
    action_table[{11, "$"}] = -5;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init_tables();

    vector<string> tokens;
    string tok;
    while (cin >> tok) {
        tokens.push_back(tok);
    }
    if (tokens.empty()) return 0;
    if (tokens.back() != "$") tokens.push_back("$");

    stack<int> state_stack;
    state_stack.push(0);
    size_t ip = 0;

    while (true) {
        int s = state_stack.top();
        string a = tokens[ip];
        if (!action_table.count({s, a})) {
            cout << "SYNTAX_ERROR\n";
            return 0;
        }
        int act = action_table[{s, a}];
        if (act == 1000) {
            cout << "ACCEPTED\n";
            break;
        } else if (act > 0) { // Shift
            state_stack.push(act);
            ip++;
        } else if (act < 0) { // Reduce
            size_t prod_idx = static_cast<size_t>(-act);
            cout << prods[prod_idx].lhs << "\n";
            for (size_t k = 0; k < prods[prod_idx].len; ++k) {
                state_stack.pop();
            }
            int t = state_stack.top();
            string lhs = prods[prod_idx].lhs.substr(0, 1);
            if (!goto_table.count({t, lhs})) {
                cout << "SYNTAX_ERROR\n";
                return 0;
            }
            state_stack.push(goto_table[{t, lhs}]);
        } else {
            cout << "SYNTAX_ERROR\n";
            return 0;
        }
    }
    return 0;
}
