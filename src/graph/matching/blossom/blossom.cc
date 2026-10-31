#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#include <iomanip>
#include <sstream>
#include <queue>
#include <map>
#include <set>
#include <list>
#include <deque>
#include <numeric>
#include <functional>
using namespace std;

int n;vector<vector<int>>g;vector<int>match_,p,base,used,bloss,used_lca;
int lca(int a,int b){fill(used_lca.begin(),used_lca.end(),0);
for(;;){a=base[a];used_lca[a]=1;if(match_[a]==-1)break;a=p[match_[a]];}
for(;;){b=base[b];if(used_lca[b])return b;
if(match_[b]==-1)break;b=p[match_[b]];}
return -1;}
void mark_path(int v,int b,int child){
while(base[v]!=b){bloss[base[v]]=1;bloss[base[match_[v]]]=1;
p[v]=child;child=match_[v];v=p[match_[v]];}}
bool find_path(int root){fill(p.begin(),p.end(),-1);
for(int i=0;i<n;i++){base[i]=i;used[i]=0;}
used[root]=1;deque<int>q={root};
while(!q.empty()){int v=q.front();q.pop_front();
for(int to:g[v]){if(base[v]==base[to]||match_[v]==to)continue;
if(to==root||(match_[to]!=-1&&p[match_[to]]!=-1)){
int cur=lca(v,to);fill(bloss.begin(),bloss.end(),0);
mark_path(v,cur,to);mark_path(to,cur,v);
for(int i=0;i<n;i++)if(bloss[base[i]]){base[i]=cur;
if(!used[i]){used[i]=1;q.push_back(i);}}}
else if(p[to]==-1){p[to]=v;
if(match_[to]==-1){int cur=to;
while(cur!=-1){int prev=p[cur];
int nxt=prev!=-1?match_[prev]:-1;
match_[cur]=prev;if(prev!=-1)match_[prev]=cur;cur=nxt;}
return true;}
else{int nxt=match_[to];used[nxt]=1;q.push_back(nxt);}}}}
return false;}
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);
int m; if(!(cin>>n>>m)) return 0;
g.assign(n,{});match_.assign(n,-1);p.assign(n,-1);base.assign(n,0);
used.assign(n,0);bloss.assign(n,0);used_lca.assign(n,0);
for(int i=0;i<m;i++){int u,v;cin>>u>>v;
if(u!=v){g[u].push_back(v);g[v].push_back(u);}}
for(int u=0;u<n;u++){sort(g[u].begin(),g[u].end());
g[u].erase(unique(g[u].begin(),g[u].end()),g[u].end());}
for(int v=0;v<n;v++)if(match_[v]==-1)find_path(v);
vector<pair<int,int>>prs;
for(int i=0;i<n;i++)if(match_[i]!=-1&&i<match_[i])
prs.push_back({i,match_[i]});
sort(prs.begin(),prs.end());
cout<<prs.size()<<"\n";
for(auto[u,v]:prs)cout<<u<<" "<<v<<"\n";}
