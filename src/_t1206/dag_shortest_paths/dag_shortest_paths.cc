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
vector<vector<pair<int,long long>>>adj(n);vector<int>ind(n,0);
for(int i=0;i<m;i++){int u,v;long long w;cin>>u>>v>>w;
adj[u].push_back({v,w});ind[v]++;}
priority_queue<int,vector<int>,greater<int>>h;
for(int i=0;i<n;i++)if(ind[i]==0)h.push(i);
vector<int>topo;
while(!h.empty()){int u=h.top();h.pop();topo.push_back(u);
for(auto[v,w]:adj[u])if(--ind[v]==0)h.push(v);}
const long long INF=(long long)4e18;
vector<long long>ds(n,INF),dl(n,-INF);ds[s]=0;dl[s]=0;
for(int u:topo)for(auto[v,w]:adj[u]){
if(ds[u]+w<ds[v])ds[v]=ds[u]+w;
if(dl[u]>-INF/2&&dl[u]+w>dl[v])dl[v]=dl[u]+w;}
for(int i=0;i<n;i++){if(i)cout<<" ";
cout<<(ds[i]>=INF/2?"INF":to_string(ds[i]));}cout<<"\n";
for(int i=0;i<n;i++){if(i)cout<<" ";
cout<<(dl[i]<=-INF/2?"-INF":to_string(dl[i]));}cout<<"\n";}
