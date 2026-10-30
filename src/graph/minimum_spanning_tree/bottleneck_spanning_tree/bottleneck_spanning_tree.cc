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
D d(n);long long mw=0,bn=0;int cnt=0;
for(int i:o)if(d.u(es[i].u,es[i].v)){mw+=es[i].w;bn=max(bn,es[i].w);cnt++;}
if(n>0&&cnt!=n-1){cout<<"DISCONNECTED\n";return 0;}
cout<<bn<<"\n"<<mw<<"\n";}
