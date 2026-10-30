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

long long dinic(int N,vector<vector<long long>>cap,int s,int t){
long long flow=0;const long long INF=(long long)4e18;
vector<int>lvl(N),it(N);
function<long long(int,long long)>dfs=[&](int u,long long f)->long long{
if(u==t)return f;
for(int &i=it[u];i<N;i++){int v=i;
if(lvl[v]==lvl[u]+1&&cap[u][v]>0){long long r=dfs(v,min(f,cap[u][v]));
if(r){cap[u][v]-=r;cap[v][u]+=r;return r;}}}
return 0;};
for(;;){fill(lvl.begin(),lvl.end(),-1);lvl[s]=0;
deque<int>q={s};
while(!q.empty()){int u=q.front();q.pop_front();
for(int v=0;v<N;v++)if(lvl[v]==-1&&cap[u][v]>0){lvl[v]=lvl[u]+1;q.push_back(v);}}
if(lvl[t]==-1)return flow;
fill(it.begin(),it.end(),0);
for(;;){long long r=dfs(s,INF);if(!r)break;flow+=r;}}}
long long gg(long long a,long long b){while(b){long long t=a%b;a=b;b=t;}return a;}
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);
int n,m; if(!(cin>>n>>m)) return 0;
vector<pair<int,int>>es(m);vector<long long>deg(n,0);
for(int i=0;i<m;i++){cin>>es[i].first>>es[i].second;
deg[es[i].first]++;deg[es[i].second]++;}
int N=n+2,S=n,T=n+1;
vector<pair<long long,long long>>cands;
for(int p=0;p<=m;p++)for(int q=1;q<=n;q++)cands.push_back({p,q});
sort(cands.begin(),cands.end(),[](auto&a,auto&b){
__int128 l=(__int128)a.first*b.second,r=(__int128)b.first*a.second;
if(l!=r)return l<r;return a<b;});
cands.erase(unique(cands.begin(),cands.end()),cands.end());
for(auto[p,q]:cands){vector<vector<long long>>cap(N,vector<long long>(N,0));
for(int v=0;v<n;v++){cap[S][v]+=(long long)m*q;
cap[v][T]+=(long long)m*q+2*p-q*deg[v];}
for(auto[u,v]:es){cap[u][v]+=q;cap[v][u]+=q;}
if(dinic(N,cap,S,T)==q*(long long)n*m){long long g=gg(p,q);
cout<<p/g<<"/"<<q/g<<"\n";return 0;}}
cout<<"0/1\n";}
