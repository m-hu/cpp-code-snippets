#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
// Center-star 2-approximation for MSA: min-total-distance center,
// pairwise alignments merged with "once a gap, always a gap".
int edist(const string&a,const string&b){
    int n=(int)a.size(),m=(int)b.size();
    vector<vector<int>>dp(n+1,vector<int>(m+1,0));
    for(int i=0;i<=n;i++)dp[i][0]=i;
    for(int j=0;j<=m;j++)dp[0][j]=j;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
        int c=(a[i-1]==b[j-1]?0:1);
        dp[i][j]=min(min(dp[i-1][j]+1,dp[i][j-1]+1),dp[i-1][j-1]+c);
    }
    return dp[n][m];
}
pair<string,string> align2(const string&c,const string&s){
    int n=(int)c.size(),m=(int)s.size();
    vector<vector<int>>dp(n+1,vector<int>(m+1,0));
    for(int i=0;i<=n;i++)dp[i][0]=i;
    for(int j=0;j<=m;j++)dp[0][j]=j;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
        int cc=(c[i-1]==s[j-1]?0:1);
        dp[i][j]=min(min(dp[i-1][j]+1,dp[i][j-1]+1),dp[i-1][j-1]+cc);
    }
    string rc,rs;int i=n,j=m;
    while(i>0||j>0){
        int cur=dp[i][j];
        if(i>0&&j>0&&cur==dp[i-1][j-1]+(c[i-1]==s[j-1]?0:1)){rc.push_back(c[i-1]);rs.push_back(s[j-1]);i--;j--;}
        else if(i>0&&cur==dp[i-1][j]+1){rc.push_back(c[i-1]);rs.push_back('-');i--;}
        else{rc.push_back('-');rs.push_back(s[j-1]);j--;}
    }
    reverse(rc.begin(),rc.end());reverse(rs.begin(),rs.end());
    return {rc,rs};
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;if(!(cin>>n))return 0;
    vector<string>strs(n);for(int i=0;i<n;i++)cin>>strs[i];
    int best=0;long besttot=-1;
    for(int c=0;c<n;c++){long tot=0;for(int i=0;i<n;i++)tot+=edist(strs[c],strs[i]);if(besttot<0||tot<besttot){besttot=tot;best=c;}}
    vector<string>rows;rows.push_back(strs[best]);
    vector<int>rowpos(n,-1);rowpos[best]=0;
    for(int idx=0;idx<n;idx++){
        if(idx==best)continue;
        auto pr=align2(strs[best],strs[idx]);
        string R=rows[0],N=pr.first,S=pr.second;
        vector<string>nr(rows.size()+1);
        size_t i=0,j=0;
        while(i<R.size()||j<N.size()){
            if(j<N.size()&&N[j]=='-'){
                for(size_t r=0;r<rows.size();r++)nr[r].push_back('-');
                nr[rows.size()].push_back(S[j]);j++;
            }else if(i<R.size()&&R[i]=='-'){
                for(size_t r=0;r<rows.size();r++)nr[r].push_back(rows[r][i]);
                nr[rows.size()].push_back('-');i++;
            }else{
                for(size_t r=0;r<rows.size();r++)nr[r].push_back(rows[r][i]);
                nr[rows.size()].push_back(S[j]);i++;j++;
            }
        }
        rows.swap(nr);rowpos[idx]=(int)rows.size()-1;
    }
    int L=(int)rows[0].size();long sp=0;
    for(int c=0;c<L;c++)for(size_t a=0;a<rows.size();a++)for(size_t b=a+1;b<rows.size();b++)if(rows[a][c]!=rows[b][c])sp++;
    cout<<sp<<"\n";
    for(int i=0;i<n;i++)cout<<rows[rowpos[i]]<<"\n";
    return 0;
}
