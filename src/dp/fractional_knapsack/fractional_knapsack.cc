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
int n;long long cap; if(!(cin>>n>>cap)) return 0;
vector<long long>v(n),w(n);
for(int i=0;i<n;i++)cin>>v[i]>>w[i];
vector<int>o(n);for(int i=0;i<n;i++)o[i]=i;
sort(o.begin(),o.end(),[&](int a,int b){__int128 l=(__int128)v[a]*w[b],r=(__int128)v[b]*w[a];
if(l!=r)return l>r;return a<b;});
double tot=0,rem=(double)cap;
for(int i:o){if(rem<=0)break;
if((double)w[i]<=rem){tot+=(double)v[i];rem-=(double)w[i];}
else{tot+=(double)v[i]*(rem/(double)w[i]);rem=0;}}
cout.setf(ios::fixed);cout<<setprecision(6)<<tot<<"\n";}
