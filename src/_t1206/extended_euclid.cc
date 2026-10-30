#include <iostream>
using namespace std;
long long extgcd(long long a,long long b,long long &x,long long &y){
    if(b==0){ x=(a>=0?1:-1); y=0; return a>=0?a:-a; }
    long long x1,y1; long long g=extgcd(b,a%b,x1,y1); x=y1; y=x1-(a/b)*y1; return g;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    long long a,b; if(!(cin>>a>>b)) return 0;
    // handle negative: normalize sign
    long long aa=a>=0?a:-a, bb=b>=0?b:-b;
    long long x,y; long long g=extgcd(aa,bb,x,y);
    if(a<0) x=-x; if(b<0) y=-y;
    // special case both zero
    if(a==0&&b==0){ cout<<"0 0 0\n"; return 0; }
    cout<<g<<" "<<x<<" "<<y<<"\n";
    return 0;
}
