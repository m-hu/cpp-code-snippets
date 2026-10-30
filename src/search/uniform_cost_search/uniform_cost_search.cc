
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
const int INF = 1000000000;
typedef pair<int,int> P;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int N,M,s,g; cin>>N>>M>>s>>g;
        vector<vector<P>> adj(N);
        for(int i=0;i<M;i++){int u,v,w;cin>>u>>v>>w;adj[u].push_back({v,w});adj[v].push_back({u,w});}
        for(int i=0;i<N;i++) sort(adj[i].begin(),adj[i].end());
        // Uniform-cost search (Dijkstra, tie-break lowest node id)
        vector<int> dist(N,INF),par(N,-1);
        dist[s]=0;
        priority_queue<P,vector<P>,greater<P>> pq;
        pq.push({0,s});
        while(!pq.empty()){
            P top=pq.top();pq.pop();
            int d=top.first,v=top.second;
            if(d!=dist[v])continue;
            if(v==g)break;
            for(auto &e:adj[v]){int to=e.first,w=e.second,nd=d+w;if(nd<dist[to]){dist[to]=nd;par[to]=v;pq.push({nd,to});}}
        }
        if(dist[g]>=INF){cout<<"UCS -1\n";}
        else{
            vector<int> path;for(int v=g;v!=-1;v=par[v])path.push_back(v);
            reverse(path.begin(),path.end());
            cout<<"UCS "<<dist[g];for(int v:path)cout<<' '<<v;cout<<"\n";
        }
        // Bidirectional Dijkstra: alternate sides, stop when tops sum >= best
        vector<int> ds(N,INF),dg(N,INF),ps(N,-1),pg(N,-1);
        vector<char> vs(N,0),vg(N,0);
        ds[s]=0;dg[g]=0;vs[s]=1;vg[g]=1;
        priority_queue<P,vector<P>,greater<P>> qs,qg;
        qs.push({0,s});qg.push({0,g});
        int best=INF,meet=-1;
        for(int turn=0;;turn++){
            while(!qs.empty()&&qs.top().first!=ds[qs.top().second])qs.pop();
            while(!qg.empty()&&qg.top().first!=dg[qg.top().second])qg.pop();
            if(qs.empty()&&qg.empty())break;
            int ts=qs.empty()?INF:qs.top().first;
            int tg=qg.empty()?INF:qg.top().first;
            if(best<INF&&ts+tg>=best)break;
            if(turn%2==0){
                if(qs.empty())continue;
                P top=qs.top();qs.pop();int d=top.first,v=top.second;
                if(d!=ds[v])continue;
                vs[v]=1;
                if(vg[v]&&ds[v]+dg[v]<best){best=ds[v]+dg[v];meet=v;}
                for(auto &e:adj[v]){int to=e.first,w=e.second,nd=d+w;
                    if(nd<ds[to]){ds[to]=nd;ps[to]=v;vs[to]=1;qs.push({nd,to});
                        if(vg[to]&&nd+dg[to]<best){best=nd+dg[to];meet=to;}}}
            }else{
                if(qg.empty())continue;
                P top=qg.top();qg.pop();int d=top.first,v=top.second;
                if(d!=dg[v])continue;
                vg[v]=1;
                if(vs[v]&&ds[v]+dg[v]<best){best=ds[v]+dg[v];meet=v;}
                for(auto &e:adj[v]){int to=e.first,w=e.second,nd=d+w;
                    if(nd<dg[to]){dg[to]=nd;pg[to]=v;vg[to]=1;qg.push({nd,to});
                        if(vs[to]&&ds[to]+nd<best){best=ds[to]+nd;meet=to;}}}
            }
        }
        if(meet<0){cout<<"BIDIR -1\n";}
        else{
            vector<int> left;for(int v=meet;v!=-1;v=ps[v])left.push_back(v);
            reverse(left.begin(),left.end());
            vector<int> right;for(int v=pg[meet];v!=-1;v=pg[v])right.push_back(v);
            cout<<"BIDIR "<<best;for(int v:left)cout<<' '<<v;for(int v:right)cout<<' '<<v;cout<<"\n";
        }
    }
    return 0;
}
