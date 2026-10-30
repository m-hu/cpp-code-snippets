#include <bits/stdc++.h>
#include "sort/three_way_string_quicksort.hpp"
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    string dummy; getline(cin,dummy);
    vector<string> a(n);
    for(int i=0;i<n;++i) getline(cin,a[i]);
    oi::three_way_string_quicksort(a);
    cout<<"[";
    for(int i=0;i<n;++i){ if(i) cout<<","; cout<<a[i]; }
    cout<<"]";
    return 0;
}
