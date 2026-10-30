#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#include <iomanip>
#include <sstream>
#include <queue>
#include <map>
#include <set>
using namespace std;

int main(){ios::sync_with_stdio(false);cin.tie(nullptr);
int n; if(!(cin>>n)) return 0;
vector<long long>v(n);for(int i=0;i<n;i++)cin>>v[i];
if(n==0){cout<<0<<"\n";return 0;}
vector<vector<long long>>dp(n,vector<long long>(n,0));
for(int i=0;i<n;i++)dp[i][i]=v[i];
for(int L=2;L<=n;L++)for(int i=0;i+L-1<n;i++){int j=i+L-1;
long long a=(i+2<=j)?dp[i+2][j]:0;
long long b=(i+1<=j-1)?dp[i+1][j-1]:0;
long long c=(i<=j-2)?dp[i][j-2]:0;
dp[i][j]=max(v[i]+min(a,b),v[j]+min(b,c));}
cout<<dp[0][n-1]<<"\n";}
