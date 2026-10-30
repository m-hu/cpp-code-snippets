#include <iostream>
using namespace std;
long long modpow(long long b,long long e,long long m){
    if(m==1) return 0;
    long long r=1%m; b=((b%m)+m)%m;
    while(e>0){ if(e&1) r=(__int128)r*b%m; b=(__int128)b*b%m; e>>=1; }
    return r;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    long long a,b,m;
    // support multiple queries: first number T then T lines, or single triple
    long long vals[100000]; int cnt=0; long long v;
    while(cin>>v) vals[cnt++]=v;
    if(cnt==0) return 0;
    if(cnt==3){ cout<<modpow(vals[0],vals[1],vals[2])<<"\n"; return 0; }
    int t=(int)vals[0];
    if(t>0 && cnt==3*t+1){
        for(int i=0;i<t;i++) cout<<modpow(vals[1+3*i],vals[1+3*i+1],vals[1+3*i+2])<<"\n";
    } else {
        // try single
        cout<<modpow(vals[0],vals[1],vals[2])<<"\n";
    }
    return 0;
}
