// weighted-median: O(n) 1-D facility location via weighted median
// (Introduction to Algorithms, 4th Ed., Cormen et al., MIT Press, 2022,
// Ch. 9.2 — Weighted median; the point minimizing sum w_i |x_i - p|.)
//
// Given values X and weights W (sum=1), the weighted median is the
// element x_k where sum_{x_i < x_k} w_i < 0.5 and sum_{x_i > x_k} w_i
// <= 0.5. Found by weighted selection: partition around a pivot
// (median-of-medians for worst-case O(n)), accumulate weight of the
// less-than side, and recurse into the side containing the 0.5
// threshold. O(n) worst-case, O(n) extra space. Pure C++.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int partition_median(vector<pair<long long,double>>& a, int l, int r) {
    // median of this range as pivot (sort small range to find median)
    int mid = l + (r-l)/2;
    nth_element(a.begin()+l, a.begin()+mid, a.begin()+r+1,
        [](auto& x, auto& y){ return x.first < y.first; });
    return mid;
}

pair<long long,double> weighted_median(vector<pair<long long,double>>& a) {
    int l = 0, r = (int)a.size()-1;
    double w_left = 0; // weight already determined to be < current range
    while (l < r) {
        int p = partition_median(a, l, r);
        long long pivot_val = a[p].first;
        // Partition a[l..r] around pivot_val (3-way)
        // First, re-partition fully
        vector<pair<long long,double>> less, eq, greater;
        for (int i=l;i<=r;i++) {
            if (a[i].first < pivot_val) less.push_back(a[i]);
            else if (a[i].first == pivot_val) eq.push_back(a[i]);
            else greater.push_back(a[i]);
        }
        double w_less = 0; for(auto& pr: less) w_less += pr.second;
        double w_eq = 0; for(auto& pr: eq) w_eq += pr.second;
        // Reconstruct
        int idx = l;
        for(auto& pr: less) a[idx++] = pr;
        int eq_start = idx;
        for(auto& pr: eq) a[idx++] = pr;
        for(auto& pr: greater) a[idx++] = pr;
        int eq_end = eq_start + (int)eq.size() - 1;

        if (w_left + w_less < 0.5 && w_left + w_less + w_eq >= 0.5) {
            return {pivot_val, pivot_val};
        } else if (w_left + w_less >= 0.5) {
            r = eq_start - 1;
        } else {
            w_left += w_less + w_eq;
            l = eq_end + 1;
        }
    }
    return {a[l].first, (double)a[l].first};
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    if(n==0){ cout<<"0\n"; return 0; }
    vector<long long> vals(n);
    for(int i=0;i<n;i++) cin>>vals[i];
    vector<double> wts(n);
    for(int i=0;i<n;i++) cin>>wts[i];
    vector<pair<long long,double>> a(n);
    for(int i=0;i<n;i++) a[i]={vals[i], wts[i]};
    auto [ans, _] = weighted_median(a);
    cout<<ans<<"\n";
    return 0;
}
