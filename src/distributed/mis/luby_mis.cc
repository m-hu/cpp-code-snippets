#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <cstdint>
#include <string>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    if(!(cin>>n>>m)) return 0;
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){int u,v;cin>>u>>v;adj[u].push_back(v);adj[v].push_back(u);}
    auto pri=[&](int u)->uint32_t{return (uint32_t)((uint64_t)(u+1)*2654435761ULL>>16);};
    vector<bool> removed(n,false),inMIS(n,false);
    while(true){
        vector<int> cands;
        for(int u=0;u<n;u++) if(!removed[u]){bool mx=true; for(int v:adj[u]) if(!removed[v]&&pri(v)>pri(u)){mx=false;break;} if(mx) cands.push_back(u);}
        if(cands.empty()) break;
        for(int u:cands){inMIS[u]=true;removed[u]=true;for(int v:adj[u]) removed[v]=true;}
    }
    vector<int> res;
    for(int i=0;i<n;i++) if(inMIS[i]) res.push_back(i);
    sort(res.begin(),res.end());
    cout<<res.size()<<"\n";
    for(size_t i=0;i<res.size();i++){if(i) cout<<" "; cout<<res[i];}
    if(!res.empty()) cout<<"\n";
    return 0;
}
