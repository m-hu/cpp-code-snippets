//https://www.hackerrank.com/challenges/unbounded-knapsack
#include <bits/stdc++.h>
#define rep(i, l, r) for ((i) = (l); (i) < (r); (i)++)
#define all(x) (x).begin(), (x).end()
using namespace std;

int unbounded_knapsack(const vector<int> & w, const vector<int> & v, int s){
  int n =static_cast<int>(w.size());
  vector<int> dp(s+1, 0);
  int i;
  rep(i, 0, s+1){
    int j;
    rep(j, 0, n){
      if(w[j] <= i){
        dp[i] = max(dp[i], dp[i-w[j]] + v[j]);
      }
    }
  }
  return dp[s];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    int i;
    rep(i, 0 , t){
      int s, n ;
      cin >> n >> s;
      vector<int> w(n);
      vector<int> v(n);
      int j;
      rep(j, 0, n){
        cin >> w[j];
        v[j] = w[j];
      }
      cout << unbounded_knapsack(w, v, s) << endl;
    }
    return 0;
}
