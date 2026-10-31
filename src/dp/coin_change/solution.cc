//https://www.hackerrank.com/challenges/coin-change/submissions
#include <bits/stdc++.h>
#define rep(i, l, r) for ((i) = (l); (i) < (r); (i)++)
#define all(x) (x).begin(), (x).end()
using namespace std;

long coin_change(int n, const vector<int> & coins){
  int m = static_cast<int>(coins.size());
  vector<long> dp(n+1, 0);
  dp[0] = 1;
  int i;
  rep(i, 0, m){
    int j;
    rep(j, coins[i], n+1){
      dp[j] += dp[j-coins[i]];
    }
  }
  return dp[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<int> coins(m);
    int i;
    rep(i, 0, m){
      cin>>coins[i];
    }
    cout << coin_change(n, coins);
    return 0;
}
