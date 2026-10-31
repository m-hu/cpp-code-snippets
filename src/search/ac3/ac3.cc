
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
bool holds(int a,int b,int op){
    if(op==0)return a!=b; if(op==1)return a==b; if(op==2)return a<b; return a>b;
}
int flipop(int op){ if(op==2)return 3; if(op==3)return 2; return op; }
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int N; cin>>N;
        vector<vector<int>> dom(N);
        for(int i=0;i<N;i++){int s;cin>>s;dom[i].resize(s);for(int j=0;j<s;j++)cin>>dom[i][j];
            sort(dom[i].begin(),dom[i].end());}
        int C; cin>>C;
        vector<vector<pair<int,int>>> nbr(N);
        for(int k=0;k<C;k++){int i,j,op;cin>>i>>j>>op;
            nbr[i].push_back({j,op}); nbr[j].push_back({i,flipop(op)});}
        struct Arc{int i,j,op;};
        queue<Arc> q;
        for(int i=0;i<N;i++) for(auto &e:nbr[i]) q.push({i,e.first,e.second});
        bool ok=true;
        while(!q.empty()&&ok){
            Arc a=q.front();q.pop();
            vector<int> nd; bool ch=false;
            for(int x:dom[a.i]){
                bool sup=false;
                for(int y:dom[a.j]) if(holds(x,y,a.op)){sup=true;break;}
                if(sup) nd.push_back(x); else ch=true;
            }
            if(ch){
                dom[a.i]=nd;
                if(nd.empty()){ok=false;break;}
                for(auto &e:nbr[a.i]) if(e.first!=a.j) q.push({e.first,a.i,e.second});
            }
        }
        if(!ok){ cout<<"AC3 INCONSISTENT\n"; }
        else{
            cout<<"AC3\n";
            for(int i=0;i<N;i++){
                for(size_t k=0;k<dom[i].size();k++){ if(k)cout<<' '; cout<<dom[i][k]; }
                cout<<"\n";
            }
        }
    }
    return 0;
}
