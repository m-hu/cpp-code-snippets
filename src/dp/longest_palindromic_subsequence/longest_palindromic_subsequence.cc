#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#include <iomanip>
#include <sstream>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);
string s; if(!(cin>>s)) return 0;
int n=s.size(); if(n==0){cout<<0<<"\n";return 0;}
vector<vector<int>>dp(n,vector<int>(n,0));
for(int i=0;i<n;i++)dp[i][i]=1;
for(int len=2;len<=n;len++)for(int i=0;i+len-1<n;i++){int j=i+len-1;
if(s[i]==s[j])dp[i][j]=(len>2?dp[i+1][j-1]:0)+2;
else dp[i][j]=max(dp[i+1][j],dp[i][j-1]);}
cout<<dp[0][n-1]<<"\n";}
