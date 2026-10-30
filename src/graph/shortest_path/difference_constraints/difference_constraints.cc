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
struct C{int i,j;long long b;};vector<C>cs(m);
for(int k=0;k<m;k++)cin>>cs[k].i>>cs[k].j>>cs[k].b;
vector<long long>d(n,0);
for(int r=0;r<n;r++)for(auto c:cs)if(d[c.i]+c.b<d[c.j])d[c.j]=d[c.i]+c.b;
for(auto c:cs)if(d[c.i]+c.b<d[c.j]){cout<<"INFEASIBLE\n";return 0;}
for(int i=0;i<n;i++){if(i)cout<<" ";cout<<d[i];}cout<<"\n";}
