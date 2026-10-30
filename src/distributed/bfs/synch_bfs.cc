#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <string>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    if(!(cin>>n>>m)) return 0;
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){int u,v;cin>>u>>v;adj[u].push_back(v);adj[v].push_back(u);}
    int root;cin>>root;
    const int INF=1e9;
    vector<int> dist(n,INF),parent(n,-1);
    vector<bool> visited(n,false);
    visited[root]=true; dist[root]=0;
    vector<int> frontier={root};
    int d=0;
    while(!frontier.empty()){
        vector<int> nf;
        for(int u:frontier){dist[u]=d; for(int v:adj[u]) if(!visited[v]){visited[v]=true;parent[v]=u;nf.push_back(v);}}
        frontier=move(nf); d++;
    }
    for(int i=0;i<n;i++) cout<<i<<" "<<parent[i]<<" "<<(dist[i]==INF?-1:dist[i])<<"\n";
    return 0;
}
