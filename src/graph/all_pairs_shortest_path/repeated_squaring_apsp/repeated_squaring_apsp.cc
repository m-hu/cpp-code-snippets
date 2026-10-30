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
const long long INF=(long long)4e14;
vector<vector<long long>>L(n,vector<long long>(n));
for(int i=0;i<n;i++)for(int j=0;j<n;j++){long long x;cin>>x;
L[i][j]=(x==999999?INF:x);}
int m=1;
while(m<n-1){vector<vector<long long>>N(n,vector<long long>(n,INF));
for(int i=0;i<n;i++)for(int j=0;j<n;j++){long long b=INF;
for(int k=0;k<n;k++)b=min(b,L[i][k]+L[k][j]);
N[i][j]=b;}
L=N;m*=2;}
if(n==1)L[0][0]=0;
for(int i=0;i<n;i++){for(int j=0;j<n;j++){if(j)cout<<" ";
cout<<(L[i][j]>=INF/2?"INF":to_string(L[i][j]));}cout<<"\n";}}
