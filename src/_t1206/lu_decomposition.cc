#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const long long MOD = 1000000007LL;
long long mod_norm(long long x){ long long r=x%MOD; return r<0?r+MOD:r; }
long long mod_pow(long long b,long long e){ long long r=1; b=mod_norm(b); while(e>0){ if(e&1) r=r*b%MOD; b=b*b%MOD; e>>=1; } return r; }
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; if(!(cin>>n)||n<=0) return 0;
    vector<vector<long long>> a(n,vector<long long>(n));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++){ long long v; cin>>v; a[i][j]=mod_norm(v); }
    vector<long long> b(n); for(int i=0;i<n;i++){ long long v; cin>>v; b[i]=mod_norm(v); }
    vector<int> pi(n); for(int i=0;i<n;i++) pi[i]=i;
    int swaps=0;
    for(int k=0;k<n;k++){
        long long p=0; int kp=k;
        for(int i=k;i<n;i++) if(a[i][k]>p){p=a[i][k]; kp=i;}
        if(p==0){ cout<<"SINGULAR\n"; return 0; }
        if(kp!=k){ swaps++; swap(pi[k],pi[kp]); swap(a[k],a[kp]); }
        long long inv=mod_pow(a[k][k],MOD-2);
        for(int i=k+1;i<n;i++){ a[i][k]=a[i][k]*inv%MOD; for(int j=k+1;j<n;j++) a[i][j]=mod_norm(a[i][j]-a[i][k]*a[k][j]%MOD); }
    }
    long long det=1; for(int k=0;k<n;k++) det=det*a[k][k]%MOD;
    if((swaps&1)&&det) det=MOD-det;
    // solve Ly=Pb
    vector<long long> y(n,0);
    for(int i=0;i<n;i++){ long long s=b[pi[i]]; for(int j=0;j<i;j++) s=mod_norm(s-a[i][j]*y[j]%MOD); y[i]=s; }
    vector<long long> x(n,0);
    for(int i=n-1;i>=0;i--){ long long s=y[i]; for(int j=i+1;j<n;j++) s=mod_norm(s-a[i][j]*x[j]%MOD); x[i]=s*mod_pow(a[i][i],MOD-2)%MOD; }
    // inverse
    vector<vector<long long>> inv(n,vector<long long>(n,0));
    for(int c=0;c<n;c++){
        vector<long long> e(n,0); e[c]=1;
        vector<long long> yy(n,0);
        for(int i=0;i<n;i++){ long long s=e[pi[i]]; for(int j=0;j<i;j++) s=mod_norm(s-a[i][j]*yy[j]%MOD); yy[i]=s; }
        vector<long long> col(n,0);
        for(int i=n-1;i>=0;i--){ long long s=yy[i]; for(int j=i+1;j<n;j++) s=mod_norm(s-a[i][j]*col[j]%MOD); col[i]=s*mod_pow(a[i][i],MOD-2)%MOD; }
        for(int r=0;r<n;r++) inv[r][c]=col[r];
    }
    cout<<det<<"\n";
    for(int i=0;i<n;i++){ if(i) cout<<" "; cout<<x[i]; } cout<<"\n";
    for(int r=0;r<n;r++){ for(int c=0;c<n;c++){ if(c) cout<<" "; cout<<inv[r][c]; } cout<<"\n"; }
    return 0;
}
