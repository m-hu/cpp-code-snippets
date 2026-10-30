#include <iostream>
#include <vector>
using namespace std;
// AsynchBellmanFord: super-round simulation; every node sends its distance
// on all outgoing edges each round until quiescence (update messages only).
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    if(!(cin>>n>>m)) return 0;
    struct E{int u,v; long long w;};
    vector<E> edges;
    for(int i=0;i<m;i++){int u,v;long long w;cin>>u>>v>>w;edges.push_back({u,v,w});}
    int src;cin>>src;
    const long long INF=(long long)4e18;
    vector<long long> dist(n,INF); dist[src]=0;
    int rounds=0;
    for(int r=0;r<n-1;r++){
        rounds++;
        bool ch=false;
        for(auto &e:edges) if(dist[e.u]!=INF&&dist[e.u]+e.w<dist[e.v]){dist[e.v]=dist[e.u]+e.w;ch=true;}
        if(!ch) break;
    }
    bool neg=false;
    for(auto &e:edges) if(dist[e.u]!=INF&&dist[e.u]+e.w<dist[e.v]){neg=true;break;}
    if(neg){ cout<<"NEGATIVE CYCLE\n"; cout<<"MESSAGES: "<<(long long)m*n<<"\n"; return 0; }
    for(int i=0;i<n;i++){if(dist[i]==INF) cout<<i<<" INF\n"; else cout<<i<<" "<<dist[i]<<"\n";}
    cout<<"MESSAGES: "<<(long long)m*rounds<<"\n";
    return 0;
}
