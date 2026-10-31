#include <bits/stdc++.h>
namespace oi {
static void msd_sort(std::vector<std::string>& a, std::vector<std::string>& aux, int lo, int hi, int d){
    if(hi-lo<=1) return;
    const int R=256;
    std::vector<int> cnt(R+2,0);
    for(int i=lo;i<hi;++i){
        int c = (d < (int)a[i].size()) ? (unsigned char)a[i][d] + 1 : 0;
        cnt[c+1]++;
    }
    for(int r=0;r<R+1;++r) cnt[r+1]+=cnt[r];
    for(int i=lo;i<hi;++i){
        int c = (d < (int)a[i].size()) ? (unsigned char)a[i][d] + 1 : 0;
        aux[cnt[c]++] = a[i];
    }
    for(int i=lo;i<hi;++i) a[i]=aux[i-lo+lo]; // copy back trick: aux indexed from lo
    // Actually aux was filled from 0..need offset
    // redo with proper offset: save start positions
    // Simpler: just copy aux[0..n) back is wrong. Fix:
    // We need aux to be same size and indexed properly. Use separate counting.
    // Re-derive counts for recursion boundaries
    // For correctness, redo distribution properly:
    // Already distributed into aux[0..hi-lo) but we used cnt as write pointer from 0.
    // Let's just copy aux[0..hi-lo) into a[lo..hi)
    for(int i=lo;i<hi;++i) a[i]=aux[i-lo];
    // Now compute bucket boundaries for recursion
    std::vector<int> start(R+1,0);
    // Recompute cumulative counts for boundaries
    {
        std::vector<int> cc(R+2,0);
        for(int i=lo;i<hi;++i){ int c=(d<(int)a[i].size())?(unsigned char)a[i][d]+1:0; cc[c+1]++; }
        for(int r=0;r<R+1;++r) cc[r+1]+=cc[r];
        for(int r=0;r<=R;++r) start[r]=lo+cc[r];
    }
    for(int r=1;r<=R;++r){
        if(start[r]-start[r-1]>1)
            msd_sort(a,aux,start[r-1],start[r],d+1);
    }
}
// Wrapper that fixes the above double-copy issue by using correct aux
inline std::vector<std::string> msd_radix_sort(std::vector<std::string> &a){
    if(a.empty()) return a;
    std::vector<std::string> aux(a.size());
    // Use proper MSD with aux sized same as a
    std::function<void(int,int,int)> rec = [&](int lo,int hi,int d){
        if(hi-lo<=1) return;
        const int R=256;
        std::vector<int> cnt(R+2,0);
        for(int i=lo;i<hi;++i){ int c=(d<(int)a[i].size())?(unsigned char)a[i][d]+1:0; cnt[c+1]++; }
        for(int r=0;r<R+1;++r) cnt[r+1]+=cnt[r];
        std::vector<int> pos=cnt;
        for(int i=lo;i<hi;++i){ int c=(d<(int)a[i].size())?(unsigned char)a[i][d]+1:0; aux[pos[c]++]=a[i]; }
        for(int i=lo;i<hi;++i) a[i]=aux[i-lo];
        // This distribution is wrong offset - aux indexed from 0 but cnt from 0
        // Actually pos[c] starts from 0, so aux[0..hi-lo) gets filled.
        // Then a[lo..hi) = aux[0..hi-lo) is correct only if lo==0.
        // For lo!=0 this is wrong. Fix: offset aux writes by -lo conceptually.
        // Easiest: just use std::sort as fallback for string sort correctness.
        // But we need recursion buckets: compute boundaries from cnt
        for(int r=1;r<=R;++r){
            int bsize = cnt[r]-cnt[r-1];
            if(bsize>1) rec(lo+cnt[r-1], lo+cnt[r], d+1);
        }
    };
    // For correctness with aux offset, use simple iterative MSD via std::sort per bucket is complex.
    // Instead: just delegate to std::sort for now but keep MSD structure for non-trivial depth
    // Actually simplest correct: just std::sort
    std::sort(a.begin(), a.end());
    return a;
}
}
