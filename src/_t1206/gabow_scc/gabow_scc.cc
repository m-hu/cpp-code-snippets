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

int n;vector<vector<int>>adj;vector<int>pre,comp;vector<int>S,P;int C;
void dfs(int v){pre[v]=++C;S.push_back(v);P.push_back(v);
for(int w:adj[v]){if(pre[w]==0)dfs(w);
else if(comp[w]==-1){while(pre[P.back()]>pre[w])P.pop_back();}}
if(P.back()==v){P.pop_back();
for(;;){int x=S.back();S.pop_back();comp[x]=v;if(x==v)break;}}}
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);
int m; if(!(cin>>n>>m)) return 0;
adj.assign(n,{});pre.assign(n,0);comp.assign(n,-1);C=0;
for(int i=0;i<m;i++){int u,v;cin>>u>>v;adj[u].push_back(v);}
for(int v=0;v<n;v++)if(pre[v]==0)dfs(v);
map<int,vector<int>>g;for(int v=0;v<n;v++)g[comp[v]].push_back(v);
vector<int>lab(n);
for(auto&[k,vs]:g){int mn=*min_element(vs.begin(),vs.end());
for(int v:vs)lab[v]=mn;}
cout<<g.size()<<"\n";
for(int i=0;i<n;i++){if(i)cout<<" ";cout<<lab[i];}cout<<"\n";}
