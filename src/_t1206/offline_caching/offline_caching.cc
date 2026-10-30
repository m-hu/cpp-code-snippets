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
using namespace std;

int main(){ios::sync_with_stdio(false);cin.tie(nullptr);
int k,m; if(!(cin>>k>>m)) return 0;
vector<long long>rq(m);for(int i=0;i<m;i++)cin>>rq[i];
const int INF=1e9;
if(k<=0){cout<<m<<"\n";return 0;}
set<long long>cache;int faults=0;
vector<int>nxt(m,INF);map<long long,int>last;
for(int i=m-1;i>=0;i--){auto it=last.find(rq[i]);nxt[i]=it==last.end()?INF:it->second;last[rq[i]]=i;}
vector<vector<int>>occ;map<long long,queue<int>>q;
for(auto&p:last){queue<int>qq;for(int i=0;i<m;i++)if(rq[i]==p.first)qq.push(i);q[p.first]=qq;}
for(int i=0;i<m;i++){long long p=rq[i];q[p].pop();
if(cache.count(p))continue;
faults++;
if((int)cache.size()<k){cache.insert(p);continue;}
long long best=0;int bestn=-1;bool f=true;
for(long long c:cache){int nu=q[c].empty()?INF:q[c].front();
if(f||nu>bestn||(nu==bestn&&c<best)){best=c;bestn=nu;f=false;}}
cache.erase(best);cache.insert(p);}
cout<<faults<<"\n";}
