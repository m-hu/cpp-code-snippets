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
long long flow=0;const long long INF=(long long)4e18;
for(;;){vector<int>par(n,-1);par[s]=s;
deque<int>q={s};
while(!q.empty()&&par[t]==-1){int u=q.front();q.pop_front();
for(int v=0;v<n;v++)if(par[v]==-1&&res[u][v]>0){par[v]=u;q.push_back(v);}}
if(par[t]==-1)break;
long long b=INF;for(int v=t;v!=s;v=par[v])b=min(b,res[par[v]][v]);
for(int v=t;v!=s;v=par[v]){res[par[v]][v]-=b;res[v][par[v]]+=b;}
flow+=b;}
cout<<flow<<"\n";}
