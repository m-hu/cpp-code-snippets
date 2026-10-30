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

int main(){ios::sync_with_stdio(false);cin.tie(nullptr);
int n,m,s,t; if(!(cin>>n>>m>>s>>t)) return 0;
vector<vector<long long>>res(n,vector<long long>(n,0)),cost(n,vector<long long>(n,0));
for(int i=0;i<m;i++){int u,v;long long c,w;cin>>u>>v>>c>>w;
res[u][v]+=c;cost[u][v]=w;cost[v][u]=-w;}
const long long INF=(long long)4e18;
vector<long long>pi(n,0);
for(int r=0;r<n;r++)for(int u=0;u<n;u++)for(int v=0;v<n;v++)
if(res[u][v]>0&&pi[u]+cost[u][v]<pi[v])pi[v]=pi[u]+cost[u][v];
long long flow=0,tot=0;
using P=pair<long long,int>;
for(;;){vector<long long>dist(n,INF);vector<int>par(n,-1);
dist[s]=0;priority_queue<P,vector<P>,greater<P>>h;h.push({0,s});
while(!h.empty()){auto[du,u]=h.top();h.pop();
if(du!=dist[u])continue;
for(int v=0;v<n;v++)if(res[u][v]>0){long long rc=cost[u][v]+pi[u]-pi[v];
if(dist[u]+rc<dist[v]){dist[v]=dist[u]+rc;par[v]=u;h.push({dist[v],v});}}}
if(par[t]==-1)break;
for(int v=0;v<n;v++)if(dist[v]<INF)pi[v]+=dist[v];
long long b=INF;for(int v=t;v!=s;v=par[v])b=min(b,res[par[v]][v]);
for(int v=t;v!=s;v=par[v]){res[par[v]][v]-=b;res[v][par[v]]+=b;tot+=b*cost[par[v]][v];}
flow+=b;}
cout<<flow<<" "<<tot<<"\n";}
