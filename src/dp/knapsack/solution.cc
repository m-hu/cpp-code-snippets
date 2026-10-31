//https://www.hackerrank.com/contests/srin-aadc03/challenges/classic-01-knapsack/problem
#include <bits/stdc++.h>
#define rep(i, l, r) for ((i) = (l); (i) < (r); (i)++)
#define all(x) (x).begin(), (x).end()
using namespace std;

int knapsack(const vector<int> & w, const vector<int> & v, int s){
  int n =static_cast<int>(w.size());
  vector<vector<int>> dp(n+1, vector<int>(s+1, 0));
  int i;
  rep(i, 0, n+1){
    int j;
    rep(j, 0, s+1){
      if(i==0||j==0)
        dp[i][j] = 0;
      else if (w[i-1] <= j)
        dp[i][j] = max(v[i-1]+dp[i-1][j-w[i-1]], dp[i-1][j]);
      else
        dp[i][j] = dp[i-1][j];
    }
  }
  return dp[n][s];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    int i;
    rep(i, 0 , t){
      int s, n ;
      cin >> s >> n;
      vector<int> w(n);
      vector<int> v(n);
      int j;
      rep(j, 0, n){
        cin >> w[j] >> v[j];
      }
      cout << knapsack(w, v, s) << endl;
    }
    return 0;
}
