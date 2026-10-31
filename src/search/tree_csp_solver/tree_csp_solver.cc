
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool holds(int a,int b,int op){
    if(op==0)return a!=b; if(op==1)return a==b; if(op==2)return a<b; return a>b;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int N; cin>>N;
        vector<int> par(N);
        for(int i=0;i<N;i++)cin>>par[i];
        vector<vector<int>> dom(N);
        for(int i=0;i<N;i++){int s;cin>>s;dom[i].resize(s);for(int j=0;j<s;j++)cin>>dom[i][j];
            sort(dom[i].begin(),dom[i].end());}
        vector<int> op(N,-1);
        for(int i=0;i<N;i++) if(par[i]>=0) cin>>op[i];
        vector<vector<int>> kids(N);
        int root=-1;
        for(int i=0;i<N;i++){ if(par[i]<0)root=i; else kids[par[i]].push_back(i); }
        vector<int> order; vector<char> seen(N,0);
        vector<int> st; st.push_back(root);
        while(!st.empty()){int v=st.back();st.pop_back();order.push_back(v);
            for(int k:kids[v])st.push_back(k);}
        bool ok=true;
        for(int oi=(int)order.size()-1;oi>=0&&ok;oi--){
            int v=order[oi];
            if(par[v]<0)continue;
            int p=par[v];
            vector<int> nd;
            for(int x:dom[p]){
                bool sup=false;
                for(int y:dom[v]) if(holds(x,y,op[v])){sup=true;break;}
                if(sup)nd.push_back(x);
            }
            dom[p]=nd;
            if(nd.empty())ok=false;
        }
        vector<int> asn(N,-1);
        if(ok){
            for(int oi=0;oi<(int)order.size()&&ok;oi++){
                int v=order[oi];
                if(par[v]<0){ if(dom[v].empty())ok=false; else asn[v]=dom[v][0]; }
                else{
                    bool f=false;
                    for(int y:dom[v]) if(holds(asn[par[v]],y,op[v])){asn[v]=y;f=true;break;}
                    if(!f)ok=false;
                }
            }
        }
        if(!ok){cout<<"TREECSP INCONSISTENT\n";}
        else{cout<<"TREECSP";for(int v:asn)cout<<' '<<v;cout<<"\n";}
    }
    return 0;
}
