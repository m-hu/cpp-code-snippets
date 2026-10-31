#include <iostream>
#include <vector>
using namespace std;
const long long MOD=1000000007LL;
long long mod_norm(long long x){ long long r=x%MOD; return r<0?r+MOD:r; }
// Karatsuba polynomial multiplication over Z_mod
vector<long long> karatsuba(const vector<long long>& a, const vector<long long>& b){
    int n=(int)a.size(), m=(int)b.size();
    if(n==0||m==0) return {};
    if(min(n,m)<=32){
        vector<long long> c(n+m-1,0);
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) c[i+j]=(c[i+j]+a[i]*b[j])%MOD;
        return c;
    }
    int k=max(n,m)/2;
    vector<long long> a0(a.begin(),a.begin()+min(k,n)), a1;
    if((int)a.size()>k) a1.assign(a.begin()+k,a.end());
    vector<long long> b0(b.begin(),b.begin()+min(k,m)), b1;
    if((int)b.size()>k) b1.assign(b.begin()+k,b.end());
    // z0=a0*b0, z2=a1*b1, z1=(a0+a1)*(b0+b1)-z0-z2
    auto z0=karatsuba(a0,b0);
    auto z2=karatsuba(a1,b1);
    vector<long long> as(k), bs(k);
    // build a0+a1 and b0+b1 (pad to max)
    int asz=max((int)a0.size(),(int)a1.size()), bsz=max((int)b0.size(),(int)b1.size());
    vector<long long> asum(asz,0), bsum(bsz,0);
    for(int i=0;i<(int)a0.size();i++) asum[i]=(asum[i]+a0[i])%MOD;
    for(int i=0;i<(int)a1.size();i++) asum[i]=(asum[i]+a1[i])%MOD;
    for(int i=0;i<(int)b0.size();i++) bsum[i]=(bsum[i]+b0[i])%MOD;
    for(int i=0;i<(int)b1.size();i++) bsum[i]=(bsum[i]+b1[i])%MOD;
    auto z1=karatsuba(asum,bsum);
    // z1 = z1 - z0 - z2
    if((int)z1.size()<max((int)z0.size(),(int)z2.size())) z1.resize(max((int)z0.size(),(int)z2.size()),0);
    for(int i=0;i<(int)z0.size();i++) z1[i]=mod_norm(z1[i]-z0[i]);
    for(int i=0;i<(int)z2.size();i++) z1[i]=mod_norm(z1[i]-z2[i]);
    vector<long long> res(n+m-1,0);
    for(int i=0;i<(int)z0.size();i++) res[i]=(res[i]+z0[i])%MOD;
    for(int i=0;i<(int)z1.size();i++) res[i+k]=(res[i+k]+z1[i])%MOD;
    for(int i=0;i<(int)z2.size();i++) res[i+2*k]=(res[i+2*k]+z2[i])%MOD;
    return res;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int da,db; if(!(cin>>da>>db)) return 0;
    vector<long long> a(da+1), b(db+1);
    for(int i=0;i<=da;i++){ long long v;cin>>v;a[i]=mod_norm(v); }
    for(int i=0;i<=db;i++){ long long v;cin>>v;b[i]=mod_norm(v); }
    auto c=karatsuba(a,b);
    int dc=da+db;
    cout<<dc<<"\n";
    for(int i=0;i<=dc;i++){ if(i) cout<<" "; cout<<c[i]; } cout<<"\n";
    return 0;
}
