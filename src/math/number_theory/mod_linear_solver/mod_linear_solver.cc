#include <iostream>
#include <vector>
using namespace std;
long long egcd(long long a,long long b,long long &x,long long &y){
    if(b==0){ x=1; y=0; return a; }
    long long x1,y1; long long g=egcd(b,a%b,x1,y1); x=y1; y=x1-(a/b)*y1; return g;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    long long a,b,n; if(!(cin>>a>>b>>n)) return 0;
    if(n<=0){ cout<<"NONE\n"; return 0; }
    if(n==1){ cout<<"0\n"; return 0; }
    a=((a%n)+n)%n; b=((b%n)+n)%n;
    long long x,y; long long g=egcd(a,n,x,y);
    if(b%g!=0){ cout<<"NONE\n"; return 0; }
    long long n2=n/g;
    long long x0=(x*(b/g)%n+n)%n;
    // all solutions: x0 + k*n2 for k=0..g-1
    vector<long long> sols;
    for(long long k=0;k<g;k++) sols.push_back((x0+k*n2)%n);
    sort(sols.begin(),sols.end());
    cout<<g<<"\n";
    for(int i=0;i<(int)sols.size();i++){ if(i) cout<<" "; cout<<sols[i]; } cout<<"\n";
    return 0;
}
