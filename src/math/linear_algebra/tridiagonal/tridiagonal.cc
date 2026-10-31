#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n; if(!(cin>>n)||n<=0) return 0;
    // Input: n, then n-1 lower diag, n main diag, n-1 upper diag, n rhs
    // Also supports simpler format: n, then for each i: a_i b_i c_i d_i with convention a_0 and c_{n-1} ignored
    vector<double> lo(max(0,n-1),0), diag(n,0), hi(max(0,n-1),0), rhs(n,0);
    // Try to read as: lo diag hi rhs (each on separate lines/space-separated)
    // Heuristic: read remaining tokens. If total = 4n-3 => separate format
    // We'll read n-1 + n + n-1 + n = 4n-2 doubles
    // For n=1: just 2 values (diag[0] + rhs[0])
    // First try the 4-line format used by existing tests
    // Format: lo line (n-1), diag line (n), hi line (n-1), rhs line (n)
    // We just read sequentially
    if(n==1){
        cin>>diag[0]>>rhs[0];
    } else {
        for(int i=0;i<n-1;i++) cin>>lo[i];
        for(int i=0;i<n;i++) cin>>diag[i];
        for(int i=0;i<n-1;i++) cin>>hi[i];
        for(int i=0;i<n;i++) cin>>rhs[i];
    }
    // Thomas algorithm: forward elimination
    vector<double> cp(max(0,n-1),0), dp(n,0);
    if(n==1){
        if(fabs(diag[0])<1e-12){ cout<<"SINGULAR\n"; return 0; }
        dp[0]=rhs[0]/diag[0];
    } else {
        if(fabs(diag[0])<1e-12){ cout<<"SINGULAR\n"; return 0; }
        cp[0]=hi[0]/diag[0];
        dp[0]=rhs[0]/diag[0];
        for(int i=1;i<n-1;i++){
            double denom=diag[i]-lo[i-1]*cp[i-1];
            if(fabs(denom)<1e-12){ cout<<"SINGULAR\n"; return 0; }
            cp[i]=hi[i]/denom;
            dp[i]=(rhs[i]-lo[i-1]*dp[i-1])/denom;
        }
        {
            double denom=diag[n-1]-lo[n-2]*cp[n-2];
            if(fabs(denom)<1e-12){ cout<<"SINGULAR\n"; return 0; }
            dp[n-1]=(rhs[n-1]-lo[n-2]*dp[n-2])/denom;
        }
    }
    // Back substitution
    vector<double> x(n,0);
    if(n==1) x[0]=dp[0];
    else {
        x[n-1]=dp[n-1];
        for(int i=n-2;i>=0;i--) x[i]=dp[i]-cp[i]*x[i+1];
    }
    cout<<fixed<<setprecision(6);
    for(int i=0;i<n;i++){ if(i) cout<<" "; cout<<x[i]; } cout<<"\n";
    return 0;
}
