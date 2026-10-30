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
int n;long long target; if(!(cin>>n>>target)) return 0;
vector<long long>v(n);for(int i=0;i<n;i++)cin>>v[i];
auto poss=[&](long long t){if(t<0)return false;
vector<char>dp(t+1,0);dp[0]=1;
for(long long x:v){if(x<0||x>t)continue;
for(long long s=t;s>=x;s--)if(dp[s-x])dp[s]=1;}
return (bool)dp[t];};
long long tot=0;for(auto x:v)tot+=x;
cout<<(poss(target)?"YES":"NO")<<"\n";
cout<<((tot%2==0&&poss(tot/2))?"YES":"NO")<<"\n";}
