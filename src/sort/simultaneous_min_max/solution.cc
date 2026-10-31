// simultaneous-min-max: pairwise tournament for min and max in
// 3*floor(n/2) comparisons (Introduction to Algorithms, 4th Ed.,
// Cormen et al., MIT Press, 2022, Ch. 9.1 — Simultaneous minimum
// and maximum).
//
// On even n the first pair seeds min and max; on odd n the first
// element seeds both. Each subsequent pair contributes one comparison
// to order the pair plus one each toward the running min and max,
// totaling 3*floor(n/2). Worst-case optimal for comparison-based
// min/max. Pure C++ with vectors; used here as the canonical
// optimal-comparisons variant.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

pair<long long,long long> simultaneous_min_max(vector<long long>& a) {
    int n = a.size();
    if (n == 0) return {0, 0};
    if (n == 1) return {a[0], a[0]};
    long long mn, mx;
    // Pairwise tournament for 3*floor(n/2) comparisons
    if (n % 2 == 0) {
        if (a[0] < a[1]) { mn = a[0]; mx = a[1]; }
        else { mn = a[1]; mx = a[0]; }
        for (int i = 2; i + 1 < n; i += 2) {
            long long sm, lg;
            if (a[i] < a[i+1]) { sm = a[i]; lg = a[i+1]; }
            else { sm = a[i+1]; lg = a[i]; }
            if (sm < mn) mn = sm;
            if (lg > mx) mx = lg;
        }
    } else {
        mn = mx = a[0];
        for (int i = 1; i + 1 < n; i += 2) {
            long long sm, lg;
            if (a[i] < a[i+1]) { sm = a[i]; lg = a[i+1]; }
            else { sm = a[i+1]; lg = a[i]; }
            if (sm < mn) mn = sm;
            if (lg > mx) mx = lg;
        }
    }
    return {mn, mx};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    vector<long long> a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    if(n==0){ cout<<"0 0\n"; return 0; }
    auto [mn, mx] = simultaneous_min_max(a);
    cout<<mn<<" "<<mx<<"\n";
    return 0;
}
