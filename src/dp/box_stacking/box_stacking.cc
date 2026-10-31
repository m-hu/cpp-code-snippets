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
int n; if(!(cin>>n)) return 0;
struct B{long long w,d,h;};
vector<B>r;
for(int i=0;i<n;i++){long long x,y,z;cin>>x>>y>>z;
long long t[3][3]={{x,y,z},{x,z,y},{y,z,x}};
for(auto&q:t){long long a=q[0],b=q[1];
if(a<b)swap(a,b);r.push_back({a,b,q[2]});}}
sort(r.begin(),r.end(),[](const B&A,const B&C){
if(A.w*A.d!=C.w*C.d)return A.w*A.d>C.w*C.d;
if(A.w!=C.w)return A.w>C.w;return A.d>C.d;});
int m=r.size();vector<long long>dp(m,0);
for(int i=0;i<m;i++)dp[i]=r[i].h;
for(int i=0;i<m;i++)for(int j=0;j<i;j++)
if(r[j].w>r[i].w&&r[j].d>r[i].d)dp[i]=max(dp[i],dp[j]+r[i].h);
long long ans=0;for(auto x:dp)ans=max(ans,x);
cout<<ans<<"\n";}
