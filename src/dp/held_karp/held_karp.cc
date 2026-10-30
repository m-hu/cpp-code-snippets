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
vector<vector<long long>>d(n,vector<long long>(n));
for(int i=0;i<n;i++)for(int j=0;j<n;j++)cin>>d[i][j];
if(n==1){cout<<0<<"\n";return 0;}
const long long INF=(long long)4e18;
int N=1<<n;vector<vector<long long>>dp(N,vector<long long>(n,INF));
dp[1][0]=0;
for(int mask=0;mask<N;mask++){if(!(mask&1))continue;
for(int u=0;u<n;u++){if(!(mask&(1<<u))||dp[mask][u]==INF)continue;
for(int v=1;v<n;v++){if(mask&(1<<v))continue;
int nm=mask|(1<<v);dp[nm][v]=min(dp[nm][v],dp[mask][u]+d[u][v]);}}}
long long ans=INF;int full=N-1;
for(int u=0;u<n;u++)ans=min(ans,dp[full][u]+d[u][0]);
cout<<ans<<"\n";}
