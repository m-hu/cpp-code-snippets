#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#include <iomanip>
#include <sstream>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);
int n; if(!(cin>>n)) return 0; vector<int>p(n); for(int i=0;i<n;i++)cin>>p[i];
vector<int>dp(n+1,0); for(int i=1;i<=n;i++){int b=INT_MIN; for(int j=1;j<=i;j++)if(j<=n)b=max(b,p[j-1]+dp[i-j]); dp[i]=b==-2147483648?0:b;}
cout<<dp[n]<<"\n";}