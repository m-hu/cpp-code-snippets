#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    string s; if(!(cin>>s)) return 0;
    string t=s+"$";
    int n=t.size();
    vector<int> sa(n);
    iota(sa.begin(),sa.end(),0);
    sort(sa.begin(),sa.end(),[&](int a,int b){ return t.substr(a)<t.substr(b); });
    string bwt(n,' ');
    for(int i=0;i<n;i++) bwt[i]=t[(sa[i]-1+n)%n];
    cout<<bwt<<"\n";
    return 0;
}
