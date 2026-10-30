#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const long long MOD=1000000007LL;
long long mod_norm(long long x){ long long r=x%MOD; return r<0?r+MOD:r; }
long long mod_pow(long long b,long long e){ long long r=1;b=mod_norm(b);while(e>0){if(e&1)r=r*b%MOD;b=b*b%MOD;e>>=1;}return r;}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;if(!(cin>>n)||n<=0) return 0;
    vector<vector<long long>> a(n,vector<long long>(n));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++){ long long v;cin>>v;a[i][j]=mod_norm(v);}
    // Gauss-Jordan with partial pivot (mod prime)
    vector<vector<long long>> aug(n,vector<long long>(2*n,0));
    for(int i=0;i<n;i++){ for(int j=0;j<n;j++) aug[i][j]=a[i][j]; aug[i][n+i]=1; }
    for(int col=0;col<n;col++){
        int pivot=-1;
        for(int row=col;row<n;row++) if(aug[row][col]!=0){pivot=row;break;}
        if(pivot==-1){ cout<<"SINGULAR\n"; return 0; }
        if(pivot!=col) swap(aug[pivot],aug[col]);
        long long inv=mod_pow(aug[col][col],MOD-2);
        for(int j=0;j<2*n;j++) aug[col][j]=aug[col][j]*inv%MOD;
        for(int row=0;row<n;row++) if(row!=col&&aug[row][col]!=0){
            long long f=aug[row][col];
            for(int j=0;j<2*n;j++) aug[row][j]=mod_norm(aug[row][j]-f*aug[col][j]%MOD);
        }
    }
    for(int i=0;i<n;i++){ for(int j=0;j<n;j++){ if(j) cout<<" "; cout<<aug[i][n+j]; } cout<<"\n"; }
    return 0;
}
