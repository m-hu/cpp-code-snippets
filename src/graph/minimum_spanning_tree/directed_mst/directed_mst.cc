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
int n,m,root; if(!(cin>>n>>m>>root)) return 0;
struct E{int u,v;long long w;};vector<E>es(m);
for(int i=0;i<m;i++)cin>>es[i].u>>es[i].v>>es[i].w;
const long long INF=(long long)4e18;
long long ans=0;
for(;;){vector<long long>inw(n,INF);vector<int>pre(n,-1);
for(auto e:es)if(e.u!=e.v&&e.w<inw[e.v]){inw[e.v]=e.w;pre[e.v]=e.u;}
inw[root]=0;
bool bad=false;for(auto x:inw)if(x==INF)bad=true;
if(bad){cout<<"NO ARBORESCENCE\n";return 0;}
vector<int>comp(n,-1),vis(n,-1);int cn=0;
for(int i=0;i<n;i++){int v=i;
while(vis[v]!=i&&comp[v]==-1&&v!=root){vis[v]=i;v=pre[v];}
if(v!=root&&comp[v]==-1){int j=pre[v];
while(j!=v){comp[j]=cn;j=pre[j];}
comp[v]=cn;cn++;}}
for(auto x:inw)ans+=x;
if(cn==0)break;
for(int i=0;i<n;i++)if(comp[i]==-1)comp[i]=cn++;
vector<E>ne;
for(auto e:es)if(comp[e.u]!=comp[e.v])ne.push_back({comp[e.u],comp[e.v],e.w-inw[e.v]});
root=comp[root];n=cn;es=ne;}
cout<<ans<<"\n";}
