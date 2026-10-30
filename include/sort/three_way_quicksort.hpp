#include <bits/stdc++.h>
namespace oi {
// Dutch National Flag 3-way partition
static void sort3(std::vector<int>& a, int lo, int hi){
    if(lo>=hi) return;
    int pivot=a[lo + (hi-lo)/2];
    int lt=lo, i=lo, gt=hi;
    while(i<=gt){
        if(a[i]<pivot) std::swap(a[lt++],a[i++]);
        else if(a[i]>pivot) std::swap(a[i],a[gt--]);
        else ++i;
    }
    sort3(a,lo,lt-1);
    sort3(a,gt+1,hi);
}
inline std::vector<int> three_way_quicksort(std::vector<int> &a){
    if(!a.empty()) sort3(a,0,(int)a.size()-1);
    return a;
}
}
