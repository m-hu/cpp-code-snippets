#include <iostream>
using namespace std;
long long bgcd(long long a,long long b){
    if(a==0) return b>=0?b:-b;
    if(b==0) return a>=0?a:-a;
    if(a<0) a=-a; if(b<0) b=-b;
    int shift=0;
    while(((a|b)&1)==0){ a>>=1; b>>=1; shift++; }
    while((a&1)==0) a>>=1;
    do{
        while((b&1)==0) b>>=1;
        if(a>b) swap(a,b);
        b=b-a;
    }while(b!=0);
    return a<<shift;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    long long a,b; 
    // support multiple lines: first line is T, then each line a b
    // or single pair. Detect: if odd number of remaining tokens handling
    // Read all
    long long vals[100000]; int cnt=0;
    long long v; while(cin>>v) vals[cnt++]=v;
    if(cnt==0) return 0;
    if(cnt==2){ cout<<bgcd(vals[0],vals[1])<<"\n"; return 0; }
    // first is T
    int t=(int)vals[0];
    if(t>0 && cnt==2*t+1){
        for(int i=0;i<t;i++) cout<<bgcd(vals[1+2*i],vals[1+2*i+1])<<"\n";
    } else {
        // treat as pairs
        for(int i=0;i+1<cnt;i+=2) cout<<bgcd(vals[i],vals[i+1])<<"\n";
    }
    return 0;
}
