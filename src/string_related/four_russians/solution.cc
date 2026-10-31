#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <array>
#include <algorithm>
using namespace std;
// Four-Russians edit distance: 2x2 block decomposition with memoized
// block-transition lookup table (offsets in {-1,0,+1}, translation
// invariant). Odd fringe row/column via direct recurrence.
typedef array<int,8> Key; typedef array<int,4> Val;
map<Key,Val> memo;
Val solve_block(int a0,int a1,int b0,int b1,int t0,int t1,int l0,int l1){
    Key k{a0,a1,b0,b1,t0,t1,l0,l1};
    auto it=memo.find(k); if(it!=memo.end()) return it->second;
    int T0=0,T1=t0,T2=t0+t1,L0=0,L1=l0,L2=l0+l1;
    int x11=min(min(T1+1,L1+1),L0+(a0==b0?0:1));
    int x12=min(min(T2+1,x11+1),T1+(a0==b1?0:1));
    int x21=min(min(x11+1,L2+1),L1+(a1==b0?0:1));
    int x22=min(min(x12+1,x21+1),x11+(a1==b1?0:1));
    Val v{x21-L2,x22-x21,x12-T2,x22-x12};
    memo[k]=v; return v;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    string A,B; if(!(cin>>A>>B)) return 0;
    int n=(int)A.size(), m=(int)B.size();
    vector<vector<int>> dp(n+1,vector<int>(m+1,0));
    for(int i=0;i<=n;i++)dp[i][0]=i;
    for(int j=0;j<=m;j++)dp[0][j]=j;
    auto cell=[&](int i,int j){
        int c=(A[i-1]==B[j-1]?0:1);
        return min(min(dp[i-1][j]+1,dp[i][j-1]+1),dp[i-1][j-1]+c);
    };
    int nb=n/2, mb=m/2;
    for(int bi=0;bi<nb;bi++) for(int bj=0;bj<mb;bj++){
        int i0=2*bi,j0=2*bj;
        int t0=dp[i0][j0+1]-dp[i0][j0],t1=dp[i0][j0+2]-dp[i0][j0+1];
        int l0=dp[i0+1][j0]-dp[i0][j0],l1=dp[i0+2][j0]-dp[i0+1][j0];
        Val v=solve_block(A[i0],A[i0+1],B[j0],B[j0+1],t0,t1,l0,l1);
        dp[i0+2][j0+1]=dp[i0+2][j0]+v[0];
        dp[i0+2][j0+2]=dp[i0+2][j0+1]+v[1];
        dp[i0+1][j0+2]=dp[i0][j0+2]+v[2];
    }
    bool nodd=(n%2==1), modd=(m%2==1);
    if(nodd&&modd){
        for(int j=1;j<m;j++)dp[n][j]=cell(n,j);
        for(int i=1;i<=n;i++)dp[i][m]=cell(i,m);
    }else{
        if(modd)for(int i=1;i<=n;i++)dp[i][m]=cell(i,m);
        if(nodd)for(int j=1;j<=m;j++)dp[n][j]=cell(n,j);
    }
    cout<<dp[n][m]<<"\n";
    return 0;
}
