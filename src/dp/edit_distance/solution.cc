//https://www.hackerrank.com/contests/cse-830-homework-3/challenges/edit-distance/problem
#include <bits/stdc++.h>
#define rep(i, l, r) for ((i) = (l); (i) < (r); (i)++)
#define all(x) (x).begin(), (x).end()
using namespace std;

long edit_distance(const string & a, const string & b){
  long a_size = static_cast<long>(a.size());
  long b_size = static_cast<long>(b.size());
  vector<vector<long> >dp(2, vector<long>(a_size+1, 0));
  int i;
  rep(i, 0, a_size+1){
    dp[0][i] = i;
  }
  rep(i, 1, b_size+1){
    int j;
    rep(j, 0 , a_size+1){
      if(j==0)
        dp[i%2][j]=i;
      else if(a[j-1]==b[i-1]){
        dp[i%2][j] = dp[(i-1)%2][j-1];
      }else{
        dp[i%2][j] = 1 + min(
            dp[(i-1)%2][j],
            min(dp[i%2][j-1],
                dp[(i-1)%2][j-1])
        );
      }
    }
  }
  return dp[b_size%2][a_size];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int i;
    rep(i, 0 , n){
      string a;
      string b;
      cin >> a;
      cin >> b;
      cout << edit_distance(a, b) << endl;
    }
    return 0;
}
