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
vector<vector<int>>g(h,vector<int>(w));
for(int r=0;r<h;r++)for(int c=0;c<w;c++)cin>>g[r][c];
vector<vector<int>>dp(h,vector<int>(w,0));int ms=0;
for(int r=0;r<h;r++)for(int c=0;c<w;c++)if(g[r][c]){
if(r==0||c==0)dp[r][c]=1;else dp[r][c]=1+min({dp[r-1][c],dp[r][c-1],dp[r-1][c-1]});
ms=max(ms,dp[r][c]);}
auto hist=[&](vector<int>hh){hh.push_back(0);vector<int>st;int best=0;
for(int i=0;i<(int)hh.size();i++){while(!st.empty()&&hh[st.back()]>hh[i]){
int H=hh[st.back()];st.pop_back();
int Wd=st.empty()?i:i-st.back()-1;best=max(best,H*Wd);}
st.push_back(i);}return best;};
vector<int>he(w,0);int mr=0;
for(int r=0;r<h;r++){for(int c=0;c<w;c++)he[c]=g[r][c]?he[c]+1:0;
mr=max(mr,hist(he));}
cout<<ms*ms<<"\n"<<mr<<"\n";}
