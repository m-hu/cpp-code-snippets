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
int n,m; if(!(cin>>n>>m)) return 0;
struct E{int u,v;double w;};vector<E>es;
for(int i=0;i<m;i++){int u,v;long long p,q;cin>>u>>v>>p>>q;
es.push_back({u,v,-log((double)p/(double)q)});}
vector<double>d(n,0);
for(int r=0;r<n;r++)for(auto e:es)if(d[e.u]+e.w<d[e.v])d[e.v]=d[e.u]+e.w;
for(auto e:es)if(d[e.u]+e.w<d[e.v]){cout<<"ARBITRAGE\n";return 0;}
cout<<"NO ARBITRAGE\n";}
