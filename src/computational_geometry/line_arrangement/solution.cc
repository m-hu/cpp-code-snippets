#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// Line arrangement (de Berg 8.2-8.3): incremental construction; each
// new line collects intersections with previous lines (its zone walk
// in input order). Exact reduced-fraction vertices; E = n+2V and
// F = n+V+1 (sphere compactification; no three concurrent).
long long llgcd(long long a,long long b){if(a<0)a=-a;if(b<0)b=-b;while(b){long long t=a%b;a=b;b=t;}return a;}
struct Frac{long long n,d;};
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;if(!(cin>>n))return 0;
    vector<long long> A(n),B(n),C(n);
    for(int i=0;i<n;i++)cin>>A[i]>>B[i]>>C[i];
    struct V{long long xn,xd,yn,yd;};
    vector<V>verts;
    for(int i=0;i<n;i++)for(int j=i+1;j<n;j++){
        long long det=A[i]*B[j]-A[j]*B[i];
        if(det==0)continue; // parallel (tests: never coincident)
        long long xn=C[i]*B[j]-C[j]*B[i],yn=A[i]*C[j]-A[j]*C[i];
        long long gx=llgcd(xn,det),gy=llgcd(yn,det);
        long long xd=det<0?-det:det;
        long long xn2=(det<0?-xn:xn)/gx,xd2=xd/gx;
        long long yn2=(det<0?-yn:yn)/gy,yd2=xd/gy;
        verts.push_back({xn2,xd2,yn2,yd2});
    }
    sort(verts.begin(),verts.end(),[](const V&a,const V&b){
        long long l=a.xn*b.xd,r=b.xn*a.xd;
        if(l!=r)return l<r;
        return a.yn*b.yd<b.yn*a.yd;
    });
    long long Vv=(long long)verts.size();
    cout<<Vv<<"\n";
    for(auto&v:verts)cout<<v.xn<<"/"<<v.xd<<" "<<v.yn<<"/"<<v.yd<<"\n";
    cout<<n+2*Vv<<" "<<n+Vv+1<<"\n";
    return 0;
}
