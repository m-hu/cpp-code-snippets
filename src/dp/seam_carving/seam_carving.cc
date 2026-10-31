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
int h,w; if(!(cin>>h>>w)) return 0;
vector<vector<long long>>e(h,vector<long long>(w));
for(int r=0;r<h;r++)for(int c=0;c<w;c++)cin>>e[r][c];
const long long INF=(long long)4e18;
vector<vector<long long>>dp(h,vector<long long>(w,INF));
vector<vector<int>>par(h,vector<int>(w,0));
for(int c=0;c<w;c++)dp[0][c]=e[0][c];
for(int r=1;r<h;r++)for(int c=0;c<w;c++){
long long best=INF;int bi=c;
for(int pc=c-1;pc<=c+1;pc++)if(pc>=0&&pc<w&&dp[r-1][pc]<best){best=dp[r-1][pc];bi=pc;}
dp[r][c]=e[r][c]+best;par[r][c]=bi;}
int mc=0;for(int c=1;c<w;c++)if(dp[h-1][c]<dp[h-1][mc])mc=c;
vector<int>seam(h);seam[h-1]=mc;
for(int r=h-1;r>0;r--)seam[r-1]=par[r][seam[r]];
cout<<dp[h-1][mc]<<"\n";
for(int r=0;r<h;r++){if(r)cout<<" ";cout<<seam[r];}cout<<"\n";}
