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

struct D{vector<int>p,r;D(int n):p(n),r(n,0){for(int i=0;i<n;i++)p[i]=i;}
int f(int x){return p[x]==x?x:p[x]=f(p[x]);}
bool u(int a,int b){a=f(a);b=f(b);if(a==b)return false;
if(r[a]<r[b])swap(a,b);p[b]=a;if(r[a]==r[b])r[a]++;return true;}};
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);
int n,m; if(!(cin>>n>>m)) return 0;
struct E{int u,v;long long w;};vector<E>es(m);
for(int i=0;i<m;i++)cin>>es[i].u>>es[i].v>>es[i].w;
vector<int>o(m);for(int i=0;i<m;i++)o[i]=i;
sort(o.begin(),o.end(),[&](int a,int b){if(es[a].w!=es[b].w)return es[a].w<es[b].w;
if(es[a].u!=es[b].u)return es[a].u<es[b].u;return es[a].v<es[b].v;});
D d(n);vector<char>used(m,0);long long mw=0;int cnt=0;
for(int i:o)if(d.u(es[i].u,es[i].v)){used[i]=1;mw+=es[i].w;cnt++;}
if(cnt!=n-1){cout<<"DISCONNECTED\n";return 0;}
vector<vector<pair<int,long long>>>ta(n);
for(int i=0;i<m;i++)if(used[i]){ta[es[i].u].push_back({es[i].v,es[i].w});
ta[es[i].v].push_back({es[i].u,es[i].w});}
auto maxe=[&](int s,int t){if(s==t)return 0LL;
vector<int>par(n,-1);vector<long long>pw(n,0);
vector<int>q={s};par[s]=s;size_t h=0;
while(h<q.size()){int u=q[h++];if(u==t)break;
for(auto[w,c]:ta[u])if(par[w]==-1){par[w]=u;pw[w]=c;q.push_back(w);}}
long long mx=0;int x=t;while(x!=s){mx=max(mx,pw[x]);x=par[x];}
return mx;};
long long best=LLONG_MAX;bool any=false;
for(int i=0;i<m;i++)if(!used[i]){long long c=mw+es[i].w-maxe(es[i].u,es[i].v);
if(!any||c<best){best=c;any=true;}}
cout<<mw<<"\n";
if(any)cout<<best<<"\n";else cout<<"NO SECOND\n";}
