#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
// Byers-Waterman near-optimal alignments (Gusfield 13.2): forward and
// reverse edit DP; DFS tracks prefix cost g and prunes g+R > OPT+Delta
// (exact: every completion costs >= R). Paths sorted lexicographically.
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    string A,B;int D;
    if(!(cin>>A>>B>>D))return 0;
    int n=(int)A.size(),m=(int)B.size();
    vector<vector<int>>F(n+1,vector<int>(m+1,0));
    for(int i=0;i<=n;i++)F[i][0]=i;
    for(int j=0;j<=m;j++)F[0][j]=j;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
        int c=(A[i-1]==B[j-1]?0:1);
        F[i][j]=min(min(F[i-1][j]+1,F[i][j-1]+1),F[i-1][j-1]+c);
    }
    vector<vector<int>>R(n+1,vector<int>(m+1,0));
    for(int i=0;i<=n;i++)R[i][m]=n-i;
    for(int j=0;j<=m;j++)R[n][j]=m-j;
    for(int i=n-1;i>=0;i--)for(int j=m-1;j>=0;j--){
        int c=(A[i]==B[j]?0:1);
        R[i][j]=min(min(R[i+1][j]+1,R[i][j+1]+1),R[i+1][j+1]+c);
    }
    int OPT=F[n][m];
    vector<pair<string,string>>out;
    string ca,cb;
    vector<int>sti,stj,stmove,stg;
    sti.push_back(0);stj.push_back(0);stmove.push_back(0);stg.push_back(0);
    ca.reserve(n+m);cb.reserve(n+m);
    while(!sti.empty()){
        int i=sti.back(),j=stj.back(),mv=stmove.back(),g=stg.back();
        if(i==n&&j==m){out.push_back({ca,cb});sti.pop_back();stj.pop_back();stmove.pop_back();stg.pop_back();if(!ca.empty()){ca.pop_back();cb.pop_back();}continue;}
        if(mv>=3){sti.pop_back();stj.pop_back();stmove.pop_back();stg.pop_back();if(!ca.empty()&&(i+j>0)){ca.pop_back();cb.pop_back();}continue;}
        stmove.back()++;
        if(mv==0){ // diag
            if(i<n&&j<m){int g2=g+(A[i]==B[j]?0:1);if(g2+R[i+1][j+1]<=OPT+D){ca.push_back(A[i]);cb.push_back(B[j]);sti.push_back(i+1);stj.push_back(j+1);stmove.push_back(0);stg.push_back(g2);}}
        }else if(mv==1){ // down (gap in B)
            if(i<n){int g2=g+1;if(g2+R[i+1][j]<=OPT+D){ca.push_back(A[i]);cb.push_back('-');sti.push_back(i+1);stj.push_back(j);stmove.push_back(0);stg.push_back(g2);}}
        }else{ // right (gap in A)
            if(j<m){int g2=g+1;if(g2+R[i][j+1]<=OPT+D){ca.push_back('-');cb.push_back(B[j]);sti.push_back(i);stj.push_back(j+1);stmove.push_back(0);stg.push_back(g2);}}
        }
    }
    sort(out.begin(),out.end());
    cout<<out.size()<<"\n";
    for(auto&p:out)cout<<p.first<<"\n"<<p.second<<"\n";
    return 0;
}
