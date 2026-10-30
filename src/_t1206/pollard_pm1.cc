#include <iostream>
using namespace std;
long long llgcd(long long a,long long b){ if(a<0)a=-a; if(b<0)b=-b; while(b){ long long t=a%b; a=b; b=t; } return a; }
long long modpow_ll(long long b,long long e,long long m){
    long long r=1%m; b%=m; while(e){ if(e&1) r=(__int128)r*b%m; b=(__int128)b*b%m; e>>=1; } return r;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    long long n,B; if(!(cin>>n>>B)) return 0;
    if(n<=1){ cout<<"NONE\n"; return 0; }
    // Pollard p-1: a=2, for k=2..B: a = a^k mod n, then g=gcd(a-1,n)
    long long a=2;
    for(long long k=2;k<=B;k++){
        a=modpow_ll(a,k,n);
        long long g=llgcd(a>0?a-1+n: n-1,n);
        if(g>1 && g<n){ cout<<g<<"\n"; return 0; }
    }
    {
        long long g=llgcd((a-1+n)%n,n);
        if(g>1 && g<n){ cout<<g<<"\n"; return 0; }
    }
    cout<<"NONE\n";
    return 0;
}
