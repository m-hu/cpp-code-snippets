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
vector<vector<int>>t(n,vector<int>(n,0));
for(int i=0;i<n;i++)t[i][i]=1;
for(int i=0;i<m;i++){int u,v;cin>>u>>v;t[u][v]=1;}
for(int k=0;k<n;k++)for(int i=0;i<n;i++)if(t[i][k])
for(int j=0;j<n;j++)if(t[k][j])t[i][j]=1;
for(int i=0;i<n;i++){for(int j=0;j<n;j++){if(j)cout<<" ";cout<<t[i][j];}cout<<"\n";}}
