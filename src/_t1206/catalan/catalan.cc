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
int n,m; if(!(cin>>n>>m)) return 0;
auto cat=[&](int k){vector<long long>C(k+1,0);C[0]=1;
for(int i=1;i<=k;i++){__int128 s=0;for(int j=0;j<i;j++)s+=(__int128)C[j]*C[i-1-j];C[i]=(long long)s;}
return C[k];};
cout<<cat(n)<<"\n"<<(m>=2?cat(m-2):0)<<"\n";}
