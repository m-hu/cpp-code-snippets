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
vector<long long>a(n);for(int i=0;i<n;i++)cin>>a[i];
int N=1;while(N<n)N*=2;
vector<long long>t(N,0);for(int i=0;i<n;i++)t[i]=a[i];
for(int d=1;d<N;d*=2)for(int k=0;k<N;k+=2*d)t[k+2*d-1]+=t[k+d-1];
t[N-1]=0;
for(int d=N/2;d>=1;d/=2)for(int k=0;k<N;k+=2*d){
long long tmp=t[k+d-1];t[k+d-1]=t[k+2*d-1];t[k+2*d-1]+=tmp;}
for(int i=0;i<n;i++){if(i)cout<<" ";cout<<t[i];}cout<<"\n";
for(int i=0;i<n;i++){if(i)cout<<" ";cout<<t[i]+a[i];}cout<<"\n";}
