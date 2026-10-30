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
vector<long long>s(n),f(n),w(n);
for(int i=0;i<n;i++)cin>>s[i]>>f[i]>>w[i];
vector<int>o(n);for(int i=0;i<n;i++)o[i]=i;
sort(o.begin(),o.end(),[&](int a,int b){if(f[a]!=f[b])return f[a]<f[b];if(s[a]!=s[b])return s[a]<s[b];return a<b;});
vector<int>p(n,-1);
for(int j=0;j<n;j++){int lo=0,hi=j-1,ans=-1;
while(lo<=hi){int m=(lo+hi)/2;if(f[o[m]]<=s[o[j]]){ans=m;lo=m+1;}else hi=m-1;}
p[j]=ans;}
vector<long long>M(n,0);
for(int j=0;j<n;j++){long long incl=w[o[j]]+(p[j]>=0?M[p[j]]:0);
long long excl=j>0?M[j-1]:0;M[j]=incl>excl?incl:excl;}
vector<int>sel;int j=n-1;
while(j>=0){long long incl=w[o[j]]+(p[j]>=0?M[p[j]]:0);
long long excl=j>0?M[j-1]:0;
if(incl>excl){sel.push_back(o[j]);j=p[j];}else j--;}
sort(sel.begin(),sel.end());
cout<<(n?M[n-1]:0)<<"\n";
for(size_t i=0;i<sel.size();i++){if(i)cout<<" ";cout<<sel[i];}cout<<"\n";}
