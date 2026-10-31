#include <bits/stdc++.h>
#include "sort/bottom_up_mergesort.hpp"
using namespace std;
int main(){
    int n; if(!(cin>>n)) return 0;
    vector<int> a(n);
    for(int i=0;i<n;++i) cin>>a[i];
    oi::bottom_up_mergesort(a);
    cout<<"[";
    for(int i=0;i<n;++i){ if(i) cout<<","; cout<<a[i]; }
    cout<<"]";
    return 0;
}
