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

int N;vector<vector<int>>adj;vector<int>idx,low,on,comp,st;int C,T;
void dfs(int v){idx[v]=low[v]=++T;st.push_back(v);on[v]=1;
for(int w:adj[v]){if(idx[w]==0){dfs(w);low[v]=min(low[v],low[w]);}
else if(on[w])low[v]=min(low[v],idx[w]);}
if(low[v]==idx[v]){for(;;){int x=st.back();st.pop_back();
on[x]=0;comp[x]=C;if(x==v)break;}C++;}}
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);
int n,m; if(!(cin>>n>>m)) return 0;
N=2*n;adj.assign(N,{});
auto lit=[&](int k){int v=abs(k)-1;return k>0?2*v+1:2*v;};
for(int i=0;i<m;i++){int a,b;cin>>a>>b;
adj[lit(-a)].push_back(lit(b));adj[lit(-b)].push_back(lit(a));}
idx.assign(N,0);low.assign(N,0);on.assign(N,0);comp.assign(N,-1);C=0;T=0;
for(int v=0;v<N;v++)if(idx[v]==0)dfs(v);
for(int i=0;i<n;i++)if(comp[2*i]==comp[2*i+1]){
cout<<"UNSATISFIABLE\n";return 0;}
cout<<"SATISFIABLE\n";
for(int i=0;i<n;i++){if(i)cout<<" ";
cout<<(comp[2*i]>comp[2*i+1]?1:0);}cout<<"\n";}
