
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
const int INF = 1000000000;
int N; vector<vector<pair<int,int>>> adj; vector<int> hval; int goal;
vector<int> cur_path; vector<char> onpath;
int rbfs(int v, int g, int f_limit){
    if(v == goal) return -1;
    struct Succ{int f,to,w;};
    vector<Succ> succs;
    for(auto &e:adj[v]){
        if(onpath[e.first]) continue;
        succs.push_back({e.second+g+hval[e.first], e.first, e.second});
    }
    if(succs.empty()) return INF;
    for(auto &s:succs) s.f = max(s.f, g+hval[v]);
    while(true){
        sort(succs.begin(), succs.end(), [](const Succ&a,const Succ&b){
            if(a.f!=b.f) return a.f<b.f; return a.to<b.to; });
        int best = succs[0].f;
        if(best >= INF || best > f_limit) return best;
        int alt = succs.size()>1 ? succs[1].f : INF;
        int to=succs[0].to, w=succs[0].w;
        onpath[to]=1; cur_path.push_back(to);
        int r = rbfs(to, g+w, min(f_limit, alt));
        if(r < 0) return -1;
        cur_path.pop_back(); onpath[to]=0;
        succs[0].f = r;
    }
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int M,s; cin>>N>>M>>s>>goal;
        adj.assign(N,{});
        for(int i=0;i<M;i++){int u,v,w;cin>>u>>v>>w;adj[u].push_back({v,w});adj[v].push_back({u,w});}
        for(int i=0;i<N;i++) sort(adj[i].begin(),adj[i].end());
        hval.assign(N,0);
        for(int i=0;i<N;i++) cin>>hval[i];
        cur_path.clear(); cur_path.push_back(s);
        onpath.assign(N,0); onpath[s]=1;
        int dist=-1; vector<int> final_path;
        if(s==goal){dist=0;final_path.push_back(s);}
        else{
            int r = rbfs(s, 0, INF);
            if(r < 0){
                int g2=0;
                for(size_t i=1;i<cur_path.size();i++){
                    int a=cur_path[i-1],b=cur_path[i];
                    for(auto &e:adj[a]) if(e.first==b){g2+=e.second;break;}
                }
                dist=g2; final_path=cur_path;
            }
        }
        if(dist<0){cout<<"RBFS -1\n";}
        else{cout<<"RBFS "<<dist;for(int v:final_path)cout<<' '<<v;cout<<"\n";}
    }
    return 0;
}
