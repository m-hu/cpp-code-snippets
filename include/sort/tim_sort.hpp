#include <bits/stdc++.h>
namespace oi {
static void insertion_sort_run(std::vector<int>& a, size_t lo, size_t hi){
    for(size_t i=lo+1;i<hi;++i){
        int cur=a[i]; long long j=(long long)i-1;
        while(j>=(long long)lo && a[j]>cur){ a[j+1]=a[j]; --j; }
        a[j+1]=cur;
    }
}
static void merge_runs(std::vector<int>& a, size_t lo, size_t mid, size_t hi, std::vector<int>& buf){
    size_t i=lo,j=mid,k=lo;
    while(i<mid && j<hi){
        if(a[i]<=a[j]) buf[k++]=a[i++];
        else buf[k++]=a[j++];
    }
    while(i<mid) buf[k++]=a[i++];
    while(j<hi) buf[k++]=a[j++];
    for(size_t t=lo;t<hi;++t) a[t]=buf[t];
}
inline std::vector<int> tim_sort(std::vector<int> &a){
    size_t n=a.size();
    if(n<2) return a;
    const size_t MIN_RUN=32;
    std::vector<int> buf(n);
    // insertion sort each run
    for(size_t lo=0; lo<n; lo+=MIN_RUN){
        size_t hi=std::min(lo+MIN_RUN,n);
        insertion_sort_run(a,lo,hi);
    }
    // merge runs doubling
    for(size_t sz=MIN_RUN; sz<n; sz*=2){
        for(size_t lo=0; lo+sz<n; lo+=2*sz){
            size_t mi=lo+sz;
            size_t hi=std::min(lo+2*sz,n);
            if(a[mi-1]<=a[mi]) continue; // already sorted
            merge_runs(a,lo,mi,hi,buf);
        }
    }
    return a;
}
}
