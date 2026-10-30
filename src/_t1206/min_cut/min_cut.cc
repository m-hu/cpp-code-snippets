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
struct E{int u,v;long long c;};vector<E>es(m);
for(int i=0;i<m;i++)cin>>es[i].u>>es[i].v>>es[i].c;
vector<vector<long long>>res(n,vector<long long>(n,0));
for(auto e:es){res[e.u][e.v]+=e.c;res[e.v][e.u]+=e.c;}
long long flow=0;const long long INF=(long long)4e18;
for(;;){vector<int>par(n,-1);par[s]=s;deque<int>q={s};
while(!q.empty()&&par[t]==-1){int u=q.front();q.pop_front();
for(int v=0;v<n;v++)if(par[v]==-1&&res[u][v]>0){par[v]=u;q.push_back(v);}}
if(par[t]==-1)break;
long long b=INF;for(int v=t;v!=s;v=par[v])b=min(b,res[par[v]][v]);
for(int v=t;v!=s;v=par[v]){res[par[v]][v]-=b;res[v][par[v]]+=b;}
flow+=b;}
vector<vector<long long>>w(n,vector<long long>(n,0));
for(auto e:es){w[e.u][e.v]+=e.c;w[e.v][e.u]+=e.c;}
vector<char>alive(n,1);long long best=LLONG_MAX;int nn=n;
vector<char>added(n);vector<long long>ws(n);
while(nn>1){fill(added.begin(),added.end(),0);fill(ws.begin(),ws.end(),0);
int pre_last=-1,last=-1;
for(int k=0;k<nn;k++){int sel=-1;
for(int v=0;v<n;v++)if(alive[v]&&!added[v]&&(sel==-1||ws[v]>ws[sel]))sel=v;
added[sel]=1;
for(int v=0;v<n;v++)if(alive[v])ws[v]+=w[sel][v];
if(k==nn-2)pre_last=sel;if(k==nn-1)last=sel;}
long long coph=0;for(int v=0;v<n;v++)if(alive[v]&&v!=last)coph+=w[last][v];
best=min(best,coph);
for(int v=0;v<n;v++){w[pre_last][v]+=w[last][v];w[v][pre_last]+=w[v][last];}
alive[last]=0;nn--;}
cout<<flow<<"\n"<<best<<"\n";}
