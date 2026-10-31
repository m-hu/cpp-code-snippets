// parallel-merge-sort: fork-join P-Merge-Sort & P-Merge (CLRS 26.3)
// (Introduction to Algorithms, 4th Ed., Cormen et al., MIT Press, 2022,
// Ch. 12 / Ch. 27 — Multithreaded merge sort with O(n log n) work and
// O(log^2 n) span via parallel merge using binary search for the
// crossover point. For this single-threaded reference implementation
// the parallelism is simulated sequentially: P-Merge finds the median
// split via binary search and recurses on the two halves, matching
// the work of the parallel version. Pure C++ with vectors.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void p_merge(vector<long long>& A, int p1, int r1, int p2, int r2, vector<long long>& B, int p3) {
    int n1 = r1 - p1 + 1;
    int n2 = r2 - p2 + 1;
    if (n1 < n2) {
        // Swap to ensure A[p1..r1] is larger
        p_merge(A, p2, r2, p1, r1, B, p3);
        return;
    }
    if (n1 == 0) return;
    if (n2 == 0) {
        for (int i = 0; i < n1; i++) B[p3 + i] = A[p1 + i];
        return;
    }
    // For sequential simulation, merge via standard merge when small
    // Otherwise use binary search split (parallel merge logic)
    if (n1 + n2 <= 64) {
        int i = p1, j = p2, k = p3;
        while (i <= r1 && j <= r2) {
            if (A[i] <= A[j]) B[k++] = A[i++];
            else B[k++] = A[j++];
        }
        while (i <= r1) B[k++] = A[i++];
        while (j <= r2) B[k++] = A[j++];
        return;
    }
    int q1 = (p1 + r1) / 2;
    // Binary search for q2 = lower_bound of A[q1] in A[p2..r2]
    int lo = p2, hi = r2, q2 = r2 + 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (A[mid] < A[q1]) lo = mid + 1;
        else { q2 = mid; hi = mid - 1; }
    }
    int q3 = p3 + (q1 - p1) + (q2 - p2);
    B[q3] = A[q1];
    // Simulated parallel: two recursive merges (sequential here)
    vector<long long> B_lo(q3 - p3), B_hi((p3 + n1 + n2) - (q3 + 1));
    // Left part
    p_merge(A, p1, q1 - 1, p2, q2 - 1, B, p3);
    // Right part
    p_merge(A, q1 + 1, r1, q2, r2, B, q3 + 1);
}

void p_merge_sort(vector<long long>& A, int p, int r, vector<long long>& B, int s) {
    int n = r - p + 1;
    if (n <= 64) {
        sort(A.begin() + p, A.begin() + r + 1);
        for (int i = p; i <= r; i++) B[s + i - p] = A[i];
        // Copy back sorted into A for parent merges
        for (int i = p; i <= r; i++) A[i] = B[s + i - p];
        return;
    }
    int q = (p + r) / 2;
    int q_prime = s + (q - p + 1);
    // Simulated spawn: sort two halves
    p_merge_sort(A, p, q, B, s);
    p_merge_sort(A, q + 1, r, B, q_prime);
    // Now A[p..q] and A[q+1..r] are sorted, merge via P-Merge
    p_merge(A, p, q, q + 1, r, B, s);
    for (int i = p; i <= r; i++) A[i] = B[s + i - p];
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    if(n==0){ cout<<"[]\n"; return 0; }
    vector<long long> a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    vector<long long> aux(n);
    p_merge_sort(a, 0, n-1, aux, 0);
    cout<<"[";
    for(int i=0;i<n;i++){ if(i) cout<<","; cout<<a[i]; }
    cout<<"]\n";
    return 0;
}
