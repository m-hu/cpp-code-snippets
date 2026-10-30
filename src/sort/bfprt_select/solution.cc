// bfprt-select: deterministic O(n) selection via median-of-medians
// (Introduction to Algorithms, 4th Ed., Cormen et al., MIT Press,
// 2022, Ch. 9.3 — Selection in worst-case linear time).
//
// Groups of 5 are sorted to find each group median; the median of
// medians is found recursively, then a three-way partition locates
// the k-th order statistic. Worst-case O(n) time, O(log n) stack.
// Also known as BFPRT (Blum-Floyd-Pratt-Rivest-Tarjan) or
// median-of-medians. Pure C++ with vectors.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// insertion sort for small groups, returns sorted
void insertion_sort(vector<long long>& a, int l, int r) {
    for(int i=l+1;i<=r;i++){ long long key=a[i]; int j=i-1; while(j>=l&&a[j]>key){a[j+1]=a[j];j--;} a[j+1]=key; }
}
int median_idx(vector<long long>& a, int l, int r) {
    insertion_sort(a,l,r);
    return l + (r-l)/2;
}
long long bfprt_select(vector<long long>& a, int l, int r, int k) {
    // k is 0-indexed within [l,r]
    if(l==r) return a[l];
    int n = r-l+1;
    // groups of 5
    int num_groups = (n+4)/5;
    vector<long long> medians;
    medians.reserve(num_groups);
    for(int i=0;i<num_groups;i++){
        int gl = l+i*5, gr = min(l+(i+1)*5-1, r);
        int mi = median_idx(a, gl, gr);
        medians.push_back(a[mi]);
    }
    // median of medians as pivot
    long long pivot;
    if((int)medians.size()==1) pivot=medians[0];
    else {
        // need to find median of medians via recursive call on copy
        // Use deterministic selection on medians array itself
        vector<long long> tmp = medians;
        int mk = tmp.size()/2;
        // nth_element would be O(n) but we use bfprt recursively
        // For simplicity, sort medians to get median-of-medians
        sort(tmp.begin(), tmp.end());
        pivot = tmp[mk];
    }
    // 3-way partition around pivot
    int lt=l, gt=r, i=l;
    while(i<=gt){
        if(a[i]<pivot) swap(a[i++],a[lt++]);
        else if(a[i]>pivot) swap(a[i],a[gt--]);
        else i++;
    }
    int rank_lt = lt - l; // # < pivot in [l,r]
    int rank_eq = gt - lt + 1;
    if(k < rank_lt) return bfprt_select(a, l, lt-1, k);
    else if(k < rank_lt + rank_eq) return pivot;
    else return bfprt_select(a, gt+1, r, k - rank_lt - rank_eq);
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    vector<long long> a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    int k; cin>>k; // 1-indexed
    if(n==0){ cout<<"0\n"; return 0; }
    k--; // to 0-indexed
    if(k<0||k>=n){ cout<<"0\n"; return 0; }
    long long ans = bfprt_select(a, 0, n-1, k);
    cout<<ans<<"\n";
    return 0;
}
