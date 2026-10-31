#include <iostream>
#include <vector>
using namespace std;
const long long MOD=1000000007LL;
long long mod_norm(long long x){ long long r=x%MOD; return r<0?r+MOD:r; }
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n; if(!(cin>>n)||n<0) return 0;
    vector<long long> c(n+1);
    for(int i=0;i<=n;i++){ long long v;cin>>v; c[i]=mod_norm(v); }
    // coeffs c[0]..c[n] where p(x)=c[0]+c[1]*x+...+c[n]*x^n (low to high)
    int q; if(!(cin>>q)) return 0;
    for(int qi=0; qi<q; qi++){
        long long x;cin>>x; x=mod_norm(x);
        long long res=c[n];
        for(int i=n-1;i>=0;i--) res=(res*x%MOD + c[i])%MOD;
        if(qi) cout<<" "; cout<<res;
    }
    cout<<"\n";
    return 0;
}
