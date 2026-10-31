#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    string s1,s2; int k;
    if(!(cin>>s1>>s2>>k)) return 0;
    int n=s1.size(),m=s2.size();
    const int INF=1e9;
    vector<vector<int>> dp(n+1,vector<int>(m+1,INF));
    dp[0][0]=0;
    for(int i=0;i<=n;i++) for(int j=0;j<=m;j++){
        if(abs(i-j)>k) continue;
        if(i==0&&j==0) continue;
        int best=INF;
        if(i>0&&abs((i-1)-j)<=k) best=min(best,dp[i-1][j]+1);
        if(j>0&&abs(i-(j-1))<=k) best=min(best,dp[i][j-1]+1);
        if(i>0&&j>0&&abs((i-1)-(j-1))<=k){ int cost=(s1[i-1]==s2[j-1]?0:1); best=min(best,dp[i-1][j-1]+cost); }
        if(best<INF) dp[i][j]=best;
    }
    int ans=dp[n][m];
    cout<<(ans>=INF?-1:ans)<<"\n";
    return 0;
}
