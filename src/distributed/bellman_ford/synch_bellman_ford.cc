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
    struct E{int u,v; long long w;};
    vector<E> edges;
    for(int i=0;i<m;i++){int u,v;long long w;cin>>u>>v>>w;edges.push_back({u,v,w});}
    int src;cin>>src;
    const long long INF=(long long)4e18;
    vector<long long> dist(n,INF); dist[src]=0;
    for(int r=0;r<n-1;r++){bool ch=false; for(auto &e:edges) if(dist[e.u]!=INF&&dist[e.u]+e.w<dist[e.v]){dist[e.v]=dist[e.u]+e.w;ch=true;} if(!ch)break;}
    for(auto &e:edges) if(dist[e.u]!=INF&&dist[e.u]+e.w<dist[e.v]){cout<<"NEGATIVE CYCLE\n";return 0;}
    for(int i=0;i<n;i++){if(dist[i]==INF) cout<<i<<" INF\n"; else cout<<i<<" "<<dist[i]<<"\n";}
    return 0;
}
