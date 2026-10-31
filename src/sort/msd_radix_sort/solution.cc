#include <bits/stdc++.h>
#include "sort/msd_radix_sort.hpp"
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    string dummy; getline(cin,dummy);
    vector<string> a(n);
    for(int i=0;i<n;++i) getline(cin,a[i]);
    oi::msd_radix_sort(a);
    cout<<"[";
    for(int i=0;i<n;++i){ if(i) cout<<","; cout<<a[i]; }
    cout<<"]";
    return 0;
}
