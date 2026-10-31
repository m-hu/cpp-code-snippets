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
int n,M; if(!(cin>>n>>M)) return 0;
vector<string>w(n); for(int i=0;i<n;i++) cin>>w[i];
vector<int>len(n); for(int i=0;i<n;i++) len[i]=w[i].size();
const long long INF=1e18;
vector<long long>cost(n+1,INF); cost[n]=0;
for(int i=n-1;i>=0;i--){long long ll=0;
for(int j=i;j<n;j++){ll+=len[j]+(j>i?1:0); if(ll>M) break;
long long c=(j==n-1?0:(long long)pow((double)(M-ll),3));
cost[i]=min(cost[i],c+cost[j+1]);}}
cout<<cost[0]<<"\n";}
