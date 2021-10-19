//https://www.hackerrank.com/challenges/no-prefix-set/problem

#include <bits/stdc++.h>
#define rep(i, l, r) for ((i) = (l); (i) < (r); (i)++)
#define all(x) (x).begin(), (x).end()
using namespace std;

class node{
 public:
  unordered_map<char, shared_ptr<node>> children;
  bool end_node;
  node(): children(unordered_map<char, shared_ptr<node>>()), end_node(false){
  }
};

class trie{
public:
  shared_ptr<node> root;
  trie(): root(make_shared<node>()){

  }
  bool add_word(const string & w){
    bool is_prefix_or_prefixed = false;
    shared_ptr<node> current = root;
    for (char c : w){
      if(current->children.find(c)==current->children.end())
        current->children[c] = make_shared<node>();
      current = current->children[c];
      if (current->end_node)
        is_prefix_or_prefixed = true;
    }
    if (!current->children.empty()){
      is_prefix_or_prefixed= true;
    }
    current->end_node = true;
    return is_prefix_or_prefixed;
  }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    trie t;
    int n;
    cin >> n;
    int i;
    rep(i, 0, n){
      string s;
      cin >> s;
      if(t.add_word(s)){
        cout << "BAD SET" << endl;
        cout << s << endl;
        return 0;
      }
    }
    cout << "GOOD SET" << endl;
    return 0;
}
