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
long long k,n; if(!(cin>>k>>n)) return 0;
if(n<=0){cout<<0<<"\n";return 0;}
if(k<=0){cout<<-1<<"\n";return 0;}
if(k==1){cout<<n<<"\n";return 0;}
vector<long long>dp(k+1,0);
long long m=0;
while(dp[k]<n){m++;
for(long long e=k;e>=1;e--){__int128 v=(__int128)dp[e]+dp[e-1]+1;
dp[e]=v>n? (long long)(n+1):(long long)v;}}
cout<<m<<"\n";}
