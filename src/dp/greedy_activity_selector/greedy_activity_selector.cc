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
vector<long long>s(n),f(n);
for(int i=0;i<n;i++)cin>>s[i]>>f[i];
vector<int>o(n);for(int i=0;i<n;i++)o[i]=i;
sort(o.begin(),o.end(),[&](int a,int b){if(f[a]!=f[b])return f[a]<f[b];if(s[a]!=s[b])return s[a]<s[b];return a<b;});
vector<int>sel;long long last=-1;bool first=true;
for(int j:o){if(first||s[j]>=last){sel.push_back(j);last=f[j];first=false;}}
cout<<sel.size()<<"\n";
for(size_t i=0;i<sel.size();i++){if(i)cout<<" ";cout<<sel[i];}cout<<"\n";}
