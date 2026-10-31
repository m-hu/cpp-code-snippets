//https://www.hackerrank.com/challenges/count-strings
#include <bits/stdc++.h>
#define rep(i, l, r) for ((i) = (l); (i) < (r); (i)++)
#define all(x) (x).begin(), (x).end()
#define MOD 1000000007
using namespace std;

enum Operation {
  Concat,
  Closure,
  Union,
};

class node {
 private:
  vector<node*> &node_tracker;
  size_t index;
 public:
  Operation op;
  char ch;
  vector<node*> children;
  node(vector<node*> &tracker)
      :
      node_tracker(tracker),
      op(Operation::Concat),
      ch(-1) {
    node_tracker.push_back(this);
    index = node_tracker.size() - 1;
  }

  node(const node &rhs)
      :
      node(rhs.node_tracker) {
  }

  node& operator=(const node &rhs) {
    if (this != &rhs) {
      op = rhs.op;
      ch = rhs.ch;
      children = rhs.children;
    }
    return *this;
  }

  ~node() {
    if (node_tracker[index] != nullptr) {
      node_tracker[index] = nullptr;
    }
  }

  /*
   * a: 1
   * b: 2
   * e: 0
   * Any two nodes can be connected by multiple edges
   * refer to regex to NFA and NFA to DFA method
   * */
  pair<int, int> generate_nfa(vector<vector<pair<int, int>>> &nfa) {
    int in = static_cast<int>(nfa.size());
    nfa.push_back(vector<pair<int, int>>());
    int out = static_cast<int>(nfa.size());
    nfa.push_back(vector<pair<int, int>>());

    if (op == Concat) {
      if (children.empty()) {
        assert(ch != -1);
        if (ch == 'a') {
          nfa[in].push_back( { out, 1 });
        } else if (ch == 'b') {
          nfa[in].push_back( { out, 2 });
        }
      } else {
        int prev_in = -1;
        int prev_out = -1;
        for (node *child : children) {
          pair<int, int> in_out = child->generate_nfa(nfa);

          if (prev_in == -1 && prev_out == -1) {  // connect in
            nfa[in].push_back( { in_out.first, 0 });
          } else {
            nfa[prev_out].push_back( { in_out.first, 0 });
          }
          prev_in = in_out.first;
          prev_out = in_out.second;
        }
        nfa[prev_out].push_back( { out, 0 });
      }
    } else if (op == Closure) {
      if (children.empty()) {
        assert(ch != -1);
        int sub_in = static_cast<int>(nfa.size());
        nfa.push_back(vector<pair<int, int>>());
        int sub_out = static_cast<int>(nfa.size());
        nfa.push_back(vector<pair<int, int>>());
        if (ch == 'a') {
          nfa[sub_in].push_back( { sub_out, 1 });
        } else if (ch == 'b') {
          nfa[sub_in].push_back( { sub_out, 2 });
        }

        nfa[in].push_back( { sub_in, 0 });
        nfa[in].push_back( { out, 0 });
        nfa[sub_out].push_back( { sub_in, 0 });
        nfa[sub_out].push_back( { out, 0 });
      } else {
        int prev_in = -1;
        int prev_out = -1;
        int sub_in = -1;
        int sub_out = -1;
        for (node *child : children) {
          pair<int, int> in_out = child->generate_nfa(nfa);
          if (prev_in == -1 && prev_out == -1) {  // connect in
            sub_in = in_out.first;
            nfa[in].push_back( { sub_in, 0 });
          } else {
            nfa[prev_out].push_back( { in_out.first, 0 });
          }
          prev_in = in_out.first;
          prev_out = in_out.second;
        }
        sub_out = prev_out;
        nfa[in].push_back( { out, 0 });
        nfa[sub_out].push_back( { out, 0 });
        nfa[sub_out].push_back( { sub_in, 0 });
      }
    } else if (op == Union) {
      assert(children.size() == 2 && ch == -1);
      pair<int, int> lhs_in_out = children[0]->generate_nfa(nfa);
      pair<int, int> rhs_in_out = children[1]->generate_nfa(nfa);

      nfa[in].push_back( { lhs_in_out.first, 0 });
      nfa[in].push_back( { rhs_in_out.first, 0 });

      nfa[lhs_in_out.second].push_back( { out, 0 });
      nfa[rhs_in_out.second].push_back( { out, 0 });
    }
    return {in, out};
  }
};

node* parse_string(string r, vector<node*> &tracker) {
  node *root = new node(tracker);
  root->op = Operation::Concat;
  stack<node*> par_stack;
  int size = static_cast<int>(r.size());
  for (int i = 0; i < size; ++i) {
    if (r[i] == '(') {
      node *current = new node(tracker);
      current->op = Operation::Concat;
      par_stack.push(current);
    } else if (r[i] == ')') {
      node *current = par_stack.top();
      par_stack.pop();
      node *parent = NULL;
      if (!par_stack.empty()) {
        parent = par_stack.top();
      } else {
        parent = root;
      }
      if (!parent->children.empty()
          && parent->children.back()->op == Operation::Union
          && parent->children.back()->children.size() == 1) {
        parent->children.back()->children.push_back(current);
      } else {
        parent->children.push_back(current);
      }
    } else {
      node *parent = NULL;
      if (par_stack.empty()) {
        parent = root;
      } else {
        parent = par_stack.top();
      }
      if (r[i] == '*') {
        parent->children.back()->op = Operation::Closure;
      } else if (r[i] == '|') {
        node *current = new node(tracker);
        current->op = Operation::Union;
        current->children.push_back(parent->children.back());
        parent->children.back() = current;
      } else {
        node *current = new node(tracker);
        current->ch = r[i];
        current->op = Operation::Concat;
        if (!parent->children.empty()
            && parent->children.back()->op == Operation::Union
            && parent->children.back()->children.size() == 1) {
          parent->children.back()->children.push_back(current);
        } else {
          parent->children.push_back(current);
        }
      }
    }
  }
  return root;
}

void print_nfa(const vector<vector<pair<int, int>>> &nfa_adj) {
  for (int from = 0; from < static_cast<int>(nfa_adj.size()); ++from) {
    for (pair<int, int> to : nfa_adj[from]) {
      cout << from << " -> " << to.first << "(" << to.second << ")" << endl;
    }
  }
}

void print_dfa(const vector<unordered_map<int, int>> &dfa) {
  for (int from = 0; from < static_cast<int>(dfa.size()); ++from) {
    for (auto it = dfa[from].begin(); it != dfa[from].end(); ++it) {
      cout << from << " -> " << it->second << "(" << it->first << ")" << endl;
    }
  }
}

set<int> e_closure(const vector<vector<pair<int, int>>> &nfa_adj, int state) {
  set<int> reachable;
  unordered_set<int> state_set;
  queue<int> q;
  q.push(state);
  while (!q.empty()) {
    int current = q.front();
    q.pop();
    reachable.insert(current);
    state_set.insert(current);
    for (pair<int, int> adj : nfa_adj[current]) {
      if (adj.second == 0 && state_set.find(adj.first) == state_set.end()) {
        q.push(adj.first);
      }
    }
  }
  return reachable;
}

set<int> transition(const vector<vector<pair<int, int>>> &nfa_adj,
                    const set<int> &from, int tr) {
  set<int> states;
  for (int f : from) {
    for (pair<int, int> adj : nfa_adj[f]) {
      if (adj.second == tr) {
        states.insert(adj.first);
      }
    }
  }
  return states;
}

class DFA {
 public:
  int start;
  int phi;
  unordered_set<int> end;
  vector<unordered_map<int, int>> adj_list;
  int count(int l) {
    vector<vector<int>> matrix(adj_list.size(),
                               vector<int>(adj_list.size(), 0));

    for (int i = 0; i < static_cast<int>(adj_list.size()); ++i) {
      for (auto it = adj_list[i].begin(); it != adj_list[i].end(); ++it) {
        ++matrix[i][it->second];
      }
    }
    /* calculate the l power of the matrix which contains the number of walks
     * between any two vertices */
    mexp(matrix, l);

    long long s = 0;
    for (int j : end) {
      s += matrix[start][j];
    }
    return static_cast<int>(s % MOD);
  }

 private:
  void mexp(vector<vector<int>> &M, int power) {
    vector<vector<int>> R(M.size(), vector<int>(M.size()));
    for (size_t i = 0; i < M.size(); i++)
      R[i][i] = 1;

    while (power > 0) {
      if (power & 1)
        mmult(R, M);
      power >>= 1;
      if (power > 0)
        mmult(M, M);
    }
    swap(R, M);
  }

  void mmult(vector<vector<int>> &D, vector<vector<int>> &S) {
    vector<vector<int>> R(D.size(), vector<int>(D.size()));
    for (size_t x = 0; x < D.size(); x++)
      for (size_t y = 0; y < D.size(); y++) {
        long long s = 0;
        for (size_t i = 0; i < D.size(); i++)
          s = (s + D[x][i] * 1ll * S[i][y]) % MOD;
        R[x][y] = (int) s;
      }
    swap(D, R);
  }
};

/**
 * a: 1
 * b: 2
 */
DFA nfa_to_dfa(const vector<vector<pair<int, int>>> &nfa_adj, int in, int out) {
  vector<unordered_map<int, int>> dfa;
  vector<set<int>> states;
  vector<bool> visited;
  map<set<int>, int> state_index;
  int start = static_cast<int>(states.size());
  int phi = -1;
  unordered_set<int> end;
  states.push_back(e_closure(nfa_adj, in));
  visited.push_back(false);
  state_index[states[start]] = start;
  if (states[start].find(out) != states[start].end()) {
    end.insert(start);
  }
  if (states[start].empty()) {
    phi = start;
  }
  dfa.push_back(unordered_map<int, int>());
  queue<int> q;
  q.push(start);
  while (!q.empty()) {
    int current = q.front();
    q.pop();
    for (int tr : { 1, 2 }) {
      set<int> transition_states = transition(nfa_adj, states[current], tr);
      set<int> to_states;
      for (int s : transition_states) {
        for (int e_s : e_closure(nfa_adj, s)) {
          to_states.insert(e_s);
        }
      }
      int child = -1;
      if (state_index.find(to_states) != state_index.end()) {
        child = state_index[to_states];
      } else {
        child = static_cast<int>(states.size());
        states.push_back(to_states);
        if (to_states.find(out) != to_states.end()) {
          end.insert(child);
          // end = child;
        }
        state_index[states[child]] = child;
        dfa.push_back(unordered_map<int, int>());
        visited.push_back(false);
      }
      if (to_states.empty()) {
        phi = child;
      }
      dfa[current][tr] = child;
      if (!visited[child]) {
        q.push(child);
      }
    }
    visited[current] = true;
  }
  DFA dfa_inst;
  dfa_inst.start = start;
  dfa_inst.end = end;
  dfa_inst.phi = phi;
  dfa_inst.adj_list = dfa;
  return dfa_inst;
}

/*
 * Complete the countStrings function below.
 */
int countStrings(string r, int l) {
  /*
   * Write your code here.
   */
  vector<node*> node_tracker;
  node *ast = parse_string(r, node_tracker);
  vector<vector<pair<int, int>>> nfa_adj;
  pair<int, int> nfa_in_out = ast->generate_nfa(nfa_adj);
  DFA dfa = nfa_to_dfa(nfa_adj, nfa_in_out.first, nfa_in_out.second);
  int ans = dfa.count(l);
  for (node *n_p : node_tracker) {
    if (n_p != nullptr) {
      delete n_p;
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  int i;
  rep(i, 0 , t)
  {
    string r;
    int l;
    cin >> r >> l;
    cout << countStrings(r, l) << endl;
  }
  return 0;
}
