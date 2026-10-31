#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#include <iomanip>
#include <sstream>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);
int n,m; if(!(cin>>n>>m)) return 0;
vector<vector<pair<int,double>>>adj(n);
for(int i=0;i<m;i++){int u,v;double p;cin>>u>>v>>p;adj[u].push_back({v,p});}
int s,t;cin>>s>>t;
const double NEG=-1e100;
vector<double>best(n,NEG); best[s]=0;
for(int u=0;u<n;u++){if(best[u]==NEG) continue;
for(auto [v,p]:adj[u]) if(p>0){double c=best[u]+log(p);best[v]=max(best[v],c);}}
if(best[t]==NEG) cout<<fixed<<setprecision(6)<<-1.0<<"\n";
else cout<<fixed<<setprecision(6)<<best[t]<<"\n";}
