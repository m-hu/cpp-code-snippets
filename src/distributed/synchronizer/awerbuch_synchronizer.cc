#include <iostream>
#include <vector>
#include <queue>
using namespace std;
// Awerbuch's synchronizers: alpha (ack every message: 2m msgs/pulse, time 1),
// beta (convergecast+broadcast over BFS tree: 2(n-1) msgs, time 2*depth),
// gamma (alpha inside clusters + beta over cluster tree).
int bfs_depth(const vector<vector<int>>& adj,int s){
    int n=adj.size(); vector<int> d(n,-1); queue<int> q; d[s]=0; q.push(s);
    int mx=0;
    while(!q.empty()){int u=q.front();q.pop();for(int v:adj[u]) if(d[v]<0){d[v]=d[u]+1;mx=max(mx,d[v]);q.push(v);}}
    return mx;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m; if(!(cin>>n>>m)) return 0;
    vector<vector<int>> adj(n);
    vector<pair<int,int>> edges;
    for(int i=0;i<m;i++){int u,v;cin>>u>>v;adj[u].push_back(v);adj[v].push_back(u);edges.push_back({u,v});}
    long long P;cin>>P;
    int nc;cin>>nc;
    vector<int> cl(n);
    for(int i=0;i<n;i++) cin>>cl[i];
    vector<vector<int>> cadj(nc);
    for(int i=0;i<nc-1;i++){int a,b;cin>>a>>b;cadj[a].push_back(b);cadj[b].push_back(a);}
    int depth=bfs_depth(adj,0);
    int cdepth=(nc>0?bfs_depth(cadj,0):0);
    long long minintra=0;
    for(auto &e:edges) if(cl[e.first]==cl[e.second]) minintra++;
    cout<<"ALPHA MESSAGES: "<<2LL*m*P<<" TIME: "<<P<<"\n";
    cout<<"BETA MESSAGES: "<<2LL*(n-1)*P<<" TIME: "<<2LL*depth*P<<"\n";
    cout<<"GAMMA MESSAGES: "<<(2*minintra+2*(nc-1))*P<<" TIME: "<<(2+2*cdepth)*P<<"\n";
    return 0;
}
