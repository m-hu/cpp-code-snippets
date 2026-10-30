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
    int n=s.size(); int i=0;
    bool first=true;
    while(i<n){
        char c=s[i]; int cnt=1;
        while(i+cnt<n && s[i+cnt]==c) cnt++;
        if(!first) cout<<" "; first=false;
        cout<<c<<cnt;
        i+=cnt;
    }
    cout<<"\n";
    return 0;
}
