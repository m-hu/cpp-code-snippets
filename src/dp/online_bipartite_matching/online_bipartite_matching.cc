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
int nU,nV,m; if(!(cin>>nU>>nV>>m)) return 0;
vector<vector<int>>adj(nU);
for(int i=0;i<m;i++){int u,v;cin>>u>>v;adj[u].push_back(v);}
long long x=42;
auto rnd=[&](long long n){x=(1103515245*x+12345)%(1LL<<31);return (int)(x%n);};
vector<int>rk(nV);for(int i=0;i<nV;i++)rk[i]=i;
for(int i=nV-1;i>0;i--){int j=rnd(i+1);swap(rk[i],rk[j]);}
vector<int>pos(nV);for(int r=0;r<nV;r++)pos[rk[r]]=r;
vector<int>mate(nU,-1);vector<char>used(nV,0);
for(int u=0;u<nU;u++){int best=-1,bp=nV+1;
for(int v:adj[u])if(!used[v]&&pos[v]<bp){best=v;bp=pos[v];}
if(best!=-1){mate[u]=best;used[best]=1;}}
vector<pair<int,int>>pr;
for(int u=0;u<nU;u++)if(mate[u]!=-1)pr.emplace_back(u,mate[u]);
cout<<pr.size()<<"\n";
for(auto[u,v]:pr)cout<<u<<" "<<v<<"\n";}
