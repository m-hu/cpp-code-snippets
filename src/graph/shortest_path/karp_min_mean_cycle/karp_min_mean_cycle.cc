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

long long gg(long long a,long long b){if(a<0)a=-a;if(b<0)b=-b;
while(b){long long t=a%b;a=b;b=t;}return a;}
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);
int n,m; if(!(cin>>n>>m)) return 0;
struct E{int u,v;long long w;};vector<E>es(m);
for(int i=0;i<m;i++)cin>>es[i].u>>es[i].v>>es[i].w;
const long long INF=(long long)4e18;
vector<vector<long long>>F(n+1,vector<long long>(n,INF));
for(int v=0;v<n;v++)F[0][v]=0;
for(int k=1;k<=n;k++)for(auto e:es)
if(F[k-1][e.u]+e.w<F[k][e.v])F[k][e.v]=F[k-1][e.u]+e.w;
bool any=false;long long bn=0,bd=1;
for(int v=0;v<n;v++){if(F[n][v]>=INF/2)continue;
bool av=false;long long vn=0,vd=1;
for(int k=0;k<n;k++){if(F[k][v]>=INF/2)continue;
long long num=F[n][v]-F[k][v],den=n-k;
if(!av||(__int128)num*vd>(__int128)vn*den){vn=num;vd=den;av=true;}}
if(!av)continue;
if(!any||(__int128)vn*bd<(__int128)bn*vd){bn=vn;bd=vd;any=true;}}
if(!any){cout<<"NO CYCLE\n";return 0;}
long long g=gg(bn,bd);
cout<<bn/g<<"/"<<bd/g<<"\n";}
