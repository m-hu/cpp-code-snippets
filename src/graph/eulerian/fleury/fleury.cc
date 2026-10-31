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

int n,m;vector<vector<pair<int,int>>>adj;vector<char>alive;
int reach(int s){vector<char>sn(n,0);sn[s]=1;vector<int>st={s};int c=0;
while(!st.empty()){int u=st.back();st.pop_back();c++;
for(auto[w,e]:adj[u])if(alive[e]&&!sn[w]){sn[w]=1;st.push_back(w);}}
return c;}
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);
if(!(cin>>n>>m)) return 0;
adj.assign(n,{});vector<pair<int,int>>es(m);
for(int i=0;i<m;i++){int u,v;cin>>u>>v;es[i]={u,v};
adj[u].push_back({v,i});adj[v].push_back({u,i});}
vector<int>odd;for(int i=0;i<n;i++)if(adj[i].size()%2)odd.push_back(i);
if(odd.size()!=0&&odd.size()!=2){cout<<"NO EULERIAN TRAIL\n";return 0;}
int src=-1;for(int i=0;i<n;i++)if(!adj[i].empty()){src=i;break;}
if(src==-1){cout<<0<<"\n";return 0;}
alive.assign(m,1);
vector<char>sn(n,0);sn[src]=1;vector<int>st={src};
while(!st.empty()){int u=st.back();st.pop_back();
for(auto[w,e]:adj[u])if(!sn[w]){sn[w]=1;st.push_back(w);}}
for(int i=0;i<n;i++)if(!adj[i].empty()&&!sn[i]){cout<<"NO EULERIAN TRAIL\n";return 0;}
int start=odd.empty()?src:odd[0];
vector<int>trail={start};int u=start;
for(;;){vector<pair<int,int>>cands;
for(auto[w,e]:adj[u])if(alive[e])cands.push_back({w,e});
if(cands.empty())break;
sort(cands.begin(),cands.end());
int w=cands[0].first,e=cands[0].second;
if(cands.size()>1){int base=reach(u);
for(auto[nw,ne]:cands){alive[ne]=0;
if(reach(u)>=base){alive[ne]=1;w=nw;e=ne;break;}
alive[ne]=1;}}
alive[e]=0;trail.push_back(w);u=w;}
for(char a:alive)if(a){cout<<"NO EULERIAN TRAIL\n";return 0;}
for(size_t i=0;i<trail.size();i++){if(i)cout<<" ";cout<<trail[i];}cout<<"\n";}
