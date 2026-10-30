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
#include <list>
#include <deque>
#include <numeric>
#include <functional>
using namespace std;

int main(){ios::sync_with_stdio(false);cin.tie(nullptr);
int n,m; if(!(cin>>n>>m)) return 0;
vector<int>lst(n);for(int i=0;i<n;i++)lst[i]=i;
long long tot=0;
for(int k=0;k<m;k++){int x;cin>>x;
int i=0;while(lst[i]!=x)i++;
tot+=i+1;lst.erase(lst.begin()+i);lst.insert(lst.begin(),x);}
cout<<tot<<"\n";}
