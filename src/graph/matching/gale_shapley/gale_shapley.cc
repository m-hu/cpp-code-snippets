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
int n; if(!(cin>>n)) return 0;
vector<vector<int>>mp(n,vector<int>(n)),wp(n,vector<int>(n));
for(int i=0;i<n;i++)for(int j=0;j<n;j++)cin>>mp[i][j];
for(int i=0;i<n;i++)for(int j=0;j<n;j++)cin>>wp[i][j];
vector<vector<int>>rank(n,vector<int>(n));
for(int w=0;w<n;w++)for(int r=0;r<n;r++)rank[w][wp[w][r]]=r;
vector<int>wife(n,-1),husb(n,-1),nxt(n,0);
deque<int>free;for(int m=0;m<n;m++)free.push_back(m);
while(!free.empty()){int m=free.front();free.pop_front();
int w=mp[m][nxt[m]++];
if(husb[w]==-1){wife[m]=w;husb[w]=m;}
else if(rank[w][m]<rank[w][husb[w]]){wife[husb[w]]=-1;free.push_back(husb[w]);
wife[m]=w;husb[w]=m;}
else free.push_back(m);}
for(int m=0;m<n;m++)cout<<m<<" "<<wife[m]<<"\n";}
