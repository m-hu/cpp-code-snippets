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
vector<long long>fr(n);for(int i=0;i<n;i++)cin>>fr[i];
if(n==1){cout<<"0\n0\n";return 0;}
vector<long long>F=fr;vector<int>MS(n),L(n,-1),R(n,-1);
for(int i=0;i<n;i++)MS[i]=i;
using T=tuple<long long,int,int>;
priority_queue<T,vector<T>,greater<T>>pq;
for(int i=0;i<n;i++)pq.emplace(fr[i],i,i);
while(pq.size()>1){auto[f1,m1,a]=pq.top();pq.pop();auto[f2,m2,b]=pq.top();pq.pop();
int id=F.size();F.push_back(f1+f2);MS.push_back(min(m1,m2));L.push_back(a);R.push_back(b);
pq.emplace(f1+f2,min(m1,m2),id);}
int root=get<2>(pq.top());
vector<int>d(F.size(),0);vector<int>st;st.push_back(root);
vector<int>dd(F.size(),0);
while(!st.empty()){int u=st.back();st.pop_back();
if(L[u]!=-1){dd[L[u]]=dd[u]+1;dd[R[u]]=dd[u]+1;st.push_back(L[u]);st.push_back(R[u]);}}
long long cost=0;for(int i=0;i<n;i++)cost+=fr[i]*dd[i];
cout<<cost<<"\n";
for(int i=0;i<n;i++){if(i)cout<<" ";cout<<dd[i];}cout<<"\n";}
