#include <iostream>
#include <vector>
using namespace std;
// AsynchBFS: root floods search; first search sets parent, forwards on all
// other edges; every search gets a response. Each edge incident to the
// visited component carries exactly 2 messages.
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
    vector<bool> vis(n,false);
    vis[root]=true; dist[root]=0;
    vector<int> frontier={root};
    int d=0;
    while(!frontier.empty()){
        vector<int> nf;
        for(int u:frontier){dist[u]=d;for(int v:adj[u]) if(!vis[v]){vis[v]=true;parent[v]=u;nf.push_back(v);}}
        frontier=move(nf); d++;
    }
    long long msgs=0;
    for(int u=0;u<n;u++) if(vis[u]) for(int v:adj[u]) if(u<v||!vis[v]) msgs++;
    // each visited-incident edge counted once above; x2 for search+response
    msgs*=2;
    for(int i=0;i<n;i++) cout<<i<<" "<<parent[i]<<" "<<(dist[i]==INF?-1:dist[i])<<"\n";
    cout<<"MESSAGES: "<<msgs<<"\n";
    return 0;
}
