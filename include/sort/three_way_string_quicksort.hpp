#include <bits/stdc++.h>
namespace oi {
static void sort3str(std::vector<std::string>& a, int lo, int hi, int d){
    if(hi<=lo) return;
    int lt=lo, gt=hi;
    int v = (d < (int)a[lo].size()) ? (unsigned char)a[lo][d] : -1;
    int i=lo+1;
    while(i<=gt){
        int t = (d < (int)a[i].size()) ? (unsigned char)a[i][d] : -1;
        if(t < v) std::swap(a[lt++],a[i++]);
        else if(t > v) std::swap(a[i],a[gt--]);
        else i++;
    }
    sort3str(a,lo,lt-1,d);
    if(v>=0) sort3str(a,lt,gt,d+1);
    sort3str(a,gt+1,hi,d);
}
inline std::vector<std::string> three_way_string_quicksort(std::vector<std::string> &a){
    if(!a.empty()) sort3str(a,0,(int)a.size()-1,0);
    return a;
}
}
