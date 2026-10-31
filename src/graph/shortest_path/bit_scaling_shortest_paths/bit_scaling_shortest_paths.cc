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
vector<vector<pair<int,long long>>>adj(n);long long cmax=0;
for(int i=0;i<m;i++){int u,v;long long w;cin>>u>>v>>w;
adj[u].push_back({v,w});cmax=max(cmax,w);}
const long long INF=(long long)4e18;
vector<long long>dist(n,INF);dist[s]=0;
long long maxd=max(1LL,(long long)(n-1)*cmax);
vector<vector<int>>bk(maxd+1);bk[0].push_back(s);
vector<char>done(n,0);long long idx=0;long long pending=1;
while(pending>0){while(idx<=maxd&&bk[idx].empty())idx++;
if(idx>maxd)break;
int u=bk[idx].back();bk[idx].pop_back();
if(done[u])continue;done[u]=1;
for(auto[v,w]:adj[u])if(dist[u]+w<dist[v]){dist[v]=dist[u]+w;
bk[dist[v]].push_back(v);pending++;}
pending--;}
for(int i=0;i<n;i++){if(i)cout<<" ";
cout<<(dist[i]>=INF/2?"INF":to_string(dist[i]));}cout<<"\n";}
