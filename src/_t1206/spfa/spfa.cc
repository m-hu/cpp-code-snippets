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
int n,m,s; if(!(cin>>n>>m>>s)) return 0;
vector<vector<pair<int,long long>>>adj(n);
for(int i=0;i<m;i++){int u,v;long long w;cin>>u>>v>>w;adj[u].push_back({v,w});}
const long long INF=(long long)4e18;
vector<long long>dist(n,INF);dist[s]=0;
vector<char>inq(n,0);vector<int>cnt(n,0),par(n,-1);
deque<int>q={s};inq[s]=1;
auto cyc=[&](int v){int x=v;
for(int i=0;i<=n;i++){x=par[x];if(x==-1)return false;if(x==v)return true;}
return true;};
while(!q.empty()){int u=q.front();q.pop_front();inq[u]=0;
for(auto[v,w]:adj[u])if(dist[u]+w<dist[v]){dist[v]=dist[u]+w;par[v]=u;
if(cyc(v)){cout<<"NEGATIVE CYCLE\n";return 0;}
if(!inq[v]){q.push_back(v);inq[v]=1;if(++cnt[v]>=n){cout<<"NEGATIVE CYCLE\n";return 0;}}}}
for(int i=0;i<n;i++){if(i)cout<<" ";
if(dist[i]>=INF/2)cout<<"INF";else cout<<dist[i];}cout<<"\n";}
