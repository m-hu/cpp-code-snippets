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

int n;vector<vector<int>>adj;vector<int>mtR;vector<char>seen;
bool bpm(int u){for(int v:adj[u]){if(seen[v])continue;
seen[v]=1;if(mtR[v]==-1||bpm(mtR[v])){mtR[v]=u;return true;}}
return false;}
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);
int m; if(!(cin>>n>>m)) return 0;
adj.assign(n,{});
for(int i=0;i<m;i++){int u,v;cin>>u>>v;adj[u].push_back(v);}
for(int u=0;u<n;u++)sort(adj[u].begin(),adj[u].end());
mtR.assign(n,-1);
for(int u=0;u<n;u++){seen.assign(n,0);bpm(u);}
vector<int>mtL(n,-1);
for(int v=0;v<n;v++)if(mtR[v]!=-1)mtL[mtR[v]]=v;
vector<vector<int>>paths;
for(int s=0;s<n;s++)if(mtR[s]==-1){vector<int>p={s};
while(mtL[p.back()]!=-1)p.push_back(mtL[p.back()]);
paths.push_back(p);}
sort(paths.begin(),paths.end(),[](auto&a,auto&b){return a[0]<b[0];});
cout<<paths.size()<<"\n";
for(auto&p:paths){for(size_t i=0;i<p.size();i++){if(i)cout<<" ";cout<<p[i];}cout<<"\n";}}
