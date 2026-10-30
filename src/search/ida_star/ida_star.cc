
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
const int INF = 1000000000;
int N; vector<vector<pair<int,int>>> adj; vector<int> hval; int goal;
vector<int> stack_path; vector<char> onpath;
int dfs(int v, int g, int bound){
    int f = g + hval[v];
    if(f > bound) return f;
    if(v == goal) return -1;
    int best = INF;
    for(auto &e : adj[v]){
        int to=e.first, w=e.second;
        if(onpath[to]) continue;
        onpath[to]=1; stack_path.push_back(to);
        int r = dfs(to, g+w, bound);
        if(r < 0) return -1;
        stack_path.pop_back(); onpath[to]=0;
        if(r < best) best = r;
    }
    return best;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int M,s; cin>>N>>M>>s>>goal;
        adj.assign(N, {});
        for(int i=0;i<M;i++){int u,v,w;cin>>u>>v>>w;adj[u].push_back({v,w});adj[v].push_back({u,w});}
        for(int i=0;i<N;i++) sort(adj[i].begin(),adj[i].end());
        hval.assign(N,0);
        for(int i=0;i<N;i++) cin>>hval[i];
        stack_path.clear(); stack_path.push_back(s);
        onpath.assign(N,0); onpath[s]=1;
        int bound = hval[s], dist = -1;
        vector<int> final_path;
        if(s == goal){ dist = 0; final_path.push_back(s); }
        else {
            for(int iter=0; iter<100000; iter++){
                int r = dfs(s, 0, bound);
                if(r < 0){
                    int g2=0;
                    for(size_t i=1;i<stack_path.size();i++){
                        int a=stack_path[i-1], b=stack_path[i];
                        for(auto &e:adj[a]) if(e.first==b){g2+=e.second;break;}
                    }
                    dist=g2; final_path=stack_path; break;
                }
                if(r >= INF) break;
                bound = r;
            }
        }
        if(dist < 0){ cout<<"IDA -1\n"; }
        else{ cout<<"IDA "<<dist; for(int v:final_path) cout<<' '<<v; cout<<"\n"; }
    }
    return 0;
}
