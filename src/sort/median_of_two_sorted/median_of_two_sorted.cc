#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

double findMedian(vector<long long>& A, vector<long long>& B) {
    // Ensure A is smaller
    if(A.size() > B.size()) return findMedian(B, A);
    int m=A.size(), n=B.size();
    if(m==0 && n==0) return 0;
    if(m==0) { sort(B.begin(),B.end()); int mid=n/2; if(n%2==1) return B[mid]; return (B[mid-1]+B[mid])/2.0; }
    // Both sorted already by input contract
    int lo=0, hi=m;
    int total = m+n;
    while(lo <= hi){
        int cutA = (lo+hi)/2;
        int cutB = (total+1)/2 - cutA;
        long long maxLeftA = (cutA==0) ? LLONG_MIN : A[cutA-1];
        long long minRightA = (cutA==m) ? LLONG_MAX : A[cutA];
        long long maxLeftB = (cutB==0) ? LLONG_MIN : B[cutB-1];
        long long minRightB = (cutB==n) ? LLONG_MAX : B[cutB];
        if(maxLeftA <= minRightB && maxLeftB <= minRightA){
            if(total%2==1) return max(maxLeftA, maxLeftB);
            return (max(maxLeftA,maxLeftB) + min(minRightA,minRightB))/2.0;
        } else if(maxLeftA > minRightB) hi = cutA-1;
        else lo = cutA+1;
    }
    return 0;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int m,n;
    if(!(cin>>m>>n)) return 0;
    vector<long long> A(m), B(n);
    for(int i=0;i<m;i++) cin>>A[i];
    for(int i=0;i<n;i++) cin>>B[i];
    // Sort inputs (test may provide unsorted)
    sort(A.begin(),A.end()); sort(B.begin(),B.end());
    double ans = findMedian(A,B);
    // Output: if integer median, print as int; else .5
    long long iv = (long long)ans;
    if(ans == iv) cout<<iv<<"\n";
    else cout<<ans<<"\n";
    return 0;
}
