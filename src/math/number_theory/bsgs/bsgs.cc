#include <iostream>
#include <unordered_map>
#include <cmath>
using namespace std;
using int64=long long;
int64 modpow(int64 b,int64 e,int64 m){
    int64 r=1%m; b%=m; while(e){ if(e&1) r=(__int128)r*b%m; b=(__int128)b*b%m; e>>=1; } return r;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int64 g,h,p; if(!(cin>>g>>h>>p)) return 0;
    g=((g%p)+p)%p; h=((h%p)+p)%p;
    if(h==1){ cout<<"0\n"; return 0; }
    int64 m=(int64)ceil(sqrt((double)p));
    unordered_map<int64,int64> table;
    int64 cur=1;
    for(int64 j=0;j<m;j++){
        if(!table.count(cur)) table[cur]=j;
        cur=(__int128)cur*g%p;
    }
    int64 factor=modpow(g,p-1-m,p); // g^{-m}
    // Actually compute g^{-m} = g^{p-1-m} if p prime, else use inverse via extended gcd
    // Use generic inverse: modpow only works for prime. Compute inverse via egcd.
    // Recompute factor as inverse of g^m
    {
        // compute g^m mod p, then inverse via egcd
        int64 gm=modpow(g,m,p);
        // egcd to find inverse of gm mod p
        auto egcd=[&](auto&& self,int64 a,int64 b,int64 &x,int64 &y)->int64{
            if(b==0){ x=1;y=0; return a; }
            int64 x1,y1; int64 gg=self(self,b,a%b,x1,y1); x=y1; y=x1-(a/b)*y1; return gg;
        };
        int64 ix,iy; int64 gg=egcd(egcd,gm,p,ix,iy);
        if(gg==1) factor=((ix%p)+p)%p;
    }
    int64 gamma=h;
    for(int64 i=0;i<m;i++){
        auto it=table.find(gamma);
        if(it!=table.end()){
            int64 ans=i*m+it->second;
            if(modpow(g,ans,p)==h){ cout<<ans<<"\n"; return 0; }
        }
        gamma=(__int128)gamma*factor%p;
    }
    cout<<"NONE\n";
    return 0;
}
