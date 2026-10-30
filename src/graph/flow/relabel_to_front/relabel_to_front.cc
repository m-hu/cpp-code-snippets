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
vector<vector<long long>>res(n,vector<long long>(n,0));
for(int i=0;i<m;i++){int u,v;long long c;cin>>u>>v>>c;res[u][v]+=c;}
vector<long long>h(n,0),e(n,0);h[s]=n;
for(int v=0;v<n;v++)if(res[s][v]>0){e[v]=res[s][v];e[s]-=res[s][v];
res[v][s]+=res[s][v];res[s][v]=0;}
vector<int>L;for(int v=0;v<n;v++)if(v!=s&&v!=t)L.push_back(v);
vector<int>cur(n,0);size_t p=0;
while(p<L.size()){int u=L[p];long long old=h[u];
while(e[u]>0){int v=cur[u];
if(v==n){long long mn=LLONG_MAX;
for(int w=0;w<n;w++)if(res[u][w]>0)mn=min(mn,h[w]);
h[u]=mn+1;cur[u]=0;}
else if(res[u][v]>0&&h[u]==h[v]+1){long long d=min(e[u],res[u][v]);
res[u][v]-=d;res[v][u]+=d;e[u]-=d;e[v]+=d;}
else cur[u]++;}
if(h[u]>old){L.erase(L.begin()+p);L.insert(L.begin(),u);p=0;}
else p++;}
cout<<e[t]<<"\n";}
