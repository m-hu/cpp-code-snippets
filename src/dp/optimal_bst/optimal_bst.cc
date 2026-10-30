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
int n; if(!(cin>>n)) return 0;
vector<double>p(n+1),q(n+1);
for(int i=1;i<=n;i++) cin>>p[i];
for(int i=0;i<=n;i++) cin>>q[i];
vector<vector<double>>e(n+2,vector<double>(n+2,0)),w(n+2,vector<double>(n+2,0));
for(int i=1;i<=n+1;i++){e[i][i-1]=q[i-1];w[i][i-1]=q[i-1];}
for(int l=1;l<=n;l++)for(int i=1;i<=n-l+1;i++){int j=i+l-1;
w[i][j]=w[i][j-1]+p[j]+q[j];e[i][j]=1e100;
for(int r=i;r<=j;r++){double c=e[i][r-1]+e[r+1][j]+w[i][j];e[i][j]=min(e[i][j],c);}
}
cout.setf(ios::fixed);cout<<setprecision(6)<<e[1][n]<<"\n";}
