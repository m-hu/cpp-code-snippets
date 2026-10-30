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
vector<int>d(n);vector<long long>w(n);
int mx=0;for(int i=0;i<n;i++){cin>>d[i]>>w[i];mx=max(mx,d[i]);}
vector<int>o(n);for(int i=0;i<n;i++)o[i]=i;
sort(o.begin(),o.end(),[&](int a,int b){if(w[a]!=w[b])return w[a]>w[b];return a<b;});
vector<int>slot(mx+1,-1);vector<char>ins(n,0);
for(int i:o){int t=min(d[i],mx);while(t>=1&&slot[t]!=-1)t--;
if(t>=1){slot[t]=i;ins[i]=1;}}
long long pen=0;vector<int>sel;
for(int i=0;i<n;i++){if(ins[i])sel.push_back(i);else pen+=w[i];}
cout<<pen<<"\n";
for(size_t i=0;i<sel.size();i++){if(i)cout<<" ";cout<<sel[i];}cout<<"\n";}
