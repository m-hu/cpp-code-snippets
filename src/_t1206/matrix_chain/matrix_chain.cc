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
int n; if(!(cin>>n)) return 0; vector<long long>d(n+1); for(int i=0;i<=n;i++)cin>>d[i];
if(n<=1){cout<<0<<"\n";return 0;} vector<vector<long long>>m(n,vector<long long>(n,0));
for(int l=2;l<=n;l++)for(int i=0;i<=n-l;i++){int j=i+l-1;m[i][j]=LLONG_MAX;
for(int k=i;k<j;k++){long long c=m[i][k]+m[k+1][j]+d[i]*d[k+1]*d[j+1];m[i][j]=min(m[i][j],c);}}
cout<<m[0][n-1]<<"\n";}