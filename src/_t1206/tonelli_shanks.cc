#include <iostream>
using namespace std;
using int64=long long;
int64 modpow(int64 b,int64 e,int64 m){
    int64 r=1%m; b%=m; while(e){ if(e&1) r=(__int128)r*b%m; b=(__int128)b*b%m; e>>=1; } return r;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int64 a,p; if(!(cin>>a>>p)) return 0;
    a=((a%p)+p)%p;
    if(a==0){ cout<<"0\n"; return 0; }
    if(p==2){ cout<<a<<"\n"; return 0; }
    // check legendre
    if(modpow(a,(p-1)/2,p)!=1){ cout<<"NONE\n"; return 0; }
    // Tonelli-Shanks
    int64 q=p-1; int s=0;
    while((q&1)==0){ q>>=1; s++; }
    if(s==1){ int64 r=modpow(a,(p+1)/4,p); cout<<min(r,p-r)<<"\n"; return 0; }
    int64 z=2; while(modpow(z,(p-1)/2,p)!=p-1) z++;
    int64 c=modpow(z,q,p);
    int64 r=modpow(a,(q+1)/2,p);
    int64 t=modpow(a,q,p);
    int m=s;
    while(t!=1){
        int64 t2=t; int i=1;
        for(;i<m;i++){ t2=(__int128)t2*t2%p; if(t2==1) break; }
        int64 b=modpow(c,1LL<<(m-i-1),p);
        r=(__int128)r*b%p;
        c=(__int128)b*b%p;
        t=(__int128)t*c%p;
        m=i;
    }
    cout<<min(r,p-r)<<"\n";
    return 0;
}
