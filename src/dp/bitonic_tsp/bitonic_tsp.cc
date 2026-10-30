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
int n; if(!(cin>>n)) return 0;
vector<double>x(n),y(n);
for(int i=0;i<n;i++) cin>>x[i]>>y[i];
if(n<=1){cout<<fixed<<setprecision(6)<<0.0<<"\n";return 0;}
if(n==2){double d=hypot(x[1]-x[0],y[1]-y[0]);cout<<fixed<<setprecision(6)<<2*d<<"\n";return 0;}
auto dist=[&](int a,int b){return hypot(x[a]-x[b],y[a]-y[b]);};
vector<vector<double>>dp(n,vector<double>(n,1e100));
dp[0][1]=dist(0,1);
for(int j=2;j<n;j++){
for(int i=0;i<j-1;i++) dp[i][j]=dp[i][j-1]+dist(j-1,j);
double best=1e100;for(int k=0;k<j-1;k++) best=min(best,dp[k][j-1]+dist(k,j));
dp[j-1][j]=best;
}
double ans=dp[n-2][n-1]+dist(n-2,n-1);
cout<<fixed<<setprecision(6)<<ans<<"\n";}
