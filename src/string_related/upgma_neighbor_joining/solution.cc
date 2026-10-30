#include <iostream>
#include <vector>
#include <string>
#include <utility>
using namespace std;
// UPGMA + Neighbor-Joining tree reconstruction (Gusfield 17.2-17.3).
// Output: UPGMA merge pairs (n-1 lines) then NJ merge pairs (n-1 lines).
// Cluster ids: leaves 0..n-1, new nodes n, n+1, ...; ties: lowest (i,j).
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;if(!(cin>>n))return 0;
    int N=2*n;
    vector<vector<double>>d0(N,vector<double>(N,0));
    for(int i=0;i<n;i++)for(int j=0;j<n;j++){cin>>d0[i][j];}
    // UPGMA
    {
        vector<vector<double>>d=d0;
        vector<int>sz(N,1);vector<char>on(N,0);
        for(int i=0;i<n;i++)on[i]=1;
        int cnt=n,nid=n;
        vector<pair<int,int>>out;
        while(cnt>1){
            int bi=-1,bj=-1;double bd=0;bool first=true;
            for(int i=0;i<nid;i++)if(on[i])for(int j=i+1;j<nid;j++)if(on[j]){
                if(first||d[i][j]<bd){first=false;bd=d[i][j];bi=i;bj=j;}
            }
            out.push_back({bi,bj});
            for(int k=0;k<nid;k++)if(on[k]&&k!=bi&&k!=bj){
                double v=(sz[bi]*d[bi][k]+sz[bj]*d[bj][k])/(sz[bi]+sz[bj]);
                d[nid][k]=d[k][nid]=v;
            }
            sz[nid]=sz[bi]+sz[bj];on[bi]=on[bj]=0;on[nid]=1;nid++;cnt--;
        }
        for(auto&p:out)cout<<p.first<<" "<<p.second<<"\n";
    }
    // Neighbor-Joining
    {
        vector<vector<double>>d=d0;
        vector<char>on(N,0);
        for(int i=0;i<n;i++)on[i]=1;
        int cnt=n,nid=n;
        vector<pair<int,int>>out;
        vector<double>R(N,0);
        while(cnt>2){
            for(int i=0;i<nid;i++)if(on[i]){R[i]=0;for(int k=0;k<nid;k++)if(on[k])R[i]+=d[i][k];}
            int bi=-1,bj=-1;double bq=0;bool first=true;
            for(int i=0;i<nid;i++)if(on[i])for(int j=i+1;j<nid;j++)if(on[j]){
                double q=(cnt-2)*d[i][j]-R[i]-R[j];
                if(first||q<bq){first=false;bq=q;bi=i;bj=j;}
            }
            out.push_back({bi,bj});
            for(int k=0;k<nid;k++)if(on[k]&&k!=bi&&k!=bj){
                double v=(d[bi][k]+d[bj][k]-d[bi][bj])/2.0;
                d[nid][k]=d[k][nid]=v;
            }
            on[bi]=on[bj]=0;on[nid]=1;nid++;cnt--;
        }
        int a=-1,b=-1;
        for(int i=0;i<nid;i++)if(on[i]){if(a<0)a=i;else b=i;}
        out.push_back({a,b});
        for(auto&p:out)cout<<p.first<<" "<<p.second<<"\n";
    }
    return 0;
}
