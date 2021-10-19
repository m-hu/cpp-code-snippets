//https://www.hackerrank.com/contests/launchpad-1-winter-challenge/challenges/binary-search-advanced
#include <bits/stdc++.h>
#define rep(i, l, r) for ((i) = (l); (i) < (r); (i)++)
#define all(x) (x).begin(), (x).end()
using namespace std;

int upper_bound(int A[],int N,int K){
    int low , high , mid;
    mid = 0;
    low = 0 ;
    high = N-1 ;
    while(low <= high){
        mid = ( low + high ) / 2 ; // finding middle element 
        if(A[mid] > K && ( mid == 0 || A[mid-1] <= K )) // checking conditions for upperbound
            return mid ;
        else if(A[mid] > K) // answer should be in left part 
            high = mid - 1 ;
        else                // answer should in right part if it exists
            low = mid + 1 ;
    }
    return mid ; // this will execute when there is no element in the given array which > K
}

int lower_bound(int A[],int N,int K){
    int low , high , mid;
    mid = 0;
    low = 0 ;
    high = N-1 ;
    while(low <= high){
        mid = ( low + high ) / 2 ; // finding middle element 
        if(A[mid] >= K && ( mid == 0 || A[mid-1] < K )) // checking conditions for lowerbound
            return mid ;
        else if(A[mid] >= K) // answer should be in left part 
            high = mid - 1 ;
        else                // answer should in right part if it exists
            low = mid + 1 ;
    }
    return mid ; // this will execute when there is no element in the given array which >= K
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int * a = new int[n];
    for (int i=0; i < n; ++i){
        cin >> a[i];
    }
    int key;
    cin >> key;
    int lower_index = lower_bound(a, n, key);
    int upper_index = upper_bound(a, n, key);
    if (a[lower_index] != key){
        cout << -1 << " "<< -1<< " " << 0 << endl;
    }else{
        cout << lower_index << " " << upper_index -1<< " " << upper_index - lower_index << endl;
    }
    delete [] a;
    return 0;
}
