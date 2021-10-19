//https://www.hackerrank.com/challenges/dynamic-programming-classics-the-longest-common-subsequence/problem
#include <bits/stdc++.h>
#define rep(i, l, r) for ((i) = (l); (i) < (r); (i)++)
#define all(x) (x).begin(), (x).end()
using namespace std;

vector<int> lcs(const vector<int> & a, const vector<int> & b, int m, int n){
  vector<vector<int>> L(m+1, vector<int>(n+1, 0));
  for (int i=0; i<=m; i++)
  {
    for (int j=0; j<=n; j++)
    {
    if (i == 0 || j == 0)
      L[i][j] = 0;
    else if (a[i-1] == b[j-1])
      L[i][j] = L[i-1][j-1] + 1;
    else
      L[i][j] = max(L[i-1][j], L[i][j-1]);
    }
  }
  int index = L[m][n];
  vector<int> lcs(index);
  int i = m, j = n;
  while (i > 0 && j > 0)
  {
    if (a[i-1] == b[j-1])
    {
      lcs[index-1] = a[i-1];
      i--; j--; index--;
    }
    else if (L[i-1][j] > L[i][j-1])
      i--;
    else
      j--;
  }
  return lcs;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<int> a(n, 0);
    vector<int> b(m, 0);
    int i;
    rep(i, 0, n){
      cin >> a[i];
    }
    rep(i, 0, m){
      cin >> b[i];
    }
    for (int num: lcs(b, a, m, n)){
      cout << num << " ";
    }
    cout << endl;
    return 0;
}
