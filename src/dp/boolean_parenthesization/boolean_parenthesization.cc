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
string syms,ops; if(!(cin>>syms)) return 0;
int n=syms.size();
if(n>1)cin>>ops;
vector<vector<long long>>T(n,vector<long long>(n,0)),F(n,vector<long long>(n,0));
for(int i=0;i<n;i++){if(syms[i]=='T')T[i][i]=1;else F[i][i]=1;}
for(int L=2;L<=n;L++)for(int i=0;i+L-1<n;i++){int j=i+L-1;
long long t=0,f=0;
for(int k=i;k<j;k++){char op=ops[k];
long long lt=T[i][k],lf=F[i][k],rt=T[k+1][j],rf=F[k+1][j];
long long tot=(lt+lf)*(rt+rf),tt=0;
if(op=='&')tt=lt*rt;else if(op=='|')tt=tot-lf*rf;else tt=lt*rf+lf*rt;
t+=tt;f+=tot-tt;}
T[i][j]=t;F[i][j]=f;}
cout<<T[0][n-1]<<"\n";}
