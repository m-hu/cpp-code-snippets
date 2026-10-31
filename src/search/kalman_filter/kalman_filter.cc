
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int Tl; cin>>Tl;
        double qn,qd,rn,rd; cin>>qn>>qd>>rn>>rd;
        double q=qn/qd, r=rn/rd;
        double x0n,x0d,p0n,p0d; cin>>x0n>>x0d>>p0n>>p0d;
        double x=x0n/x0d, P=p0n/p0d;
        vector<double> zs(Tl);
        for(int k=0;k<Tl;k++){double n,d;cin>>n>>d;zs[k]=n/d;}
        cout<<"KALMAN\n";
        for(int k=0;k<Tl;k++){
            P+=q;
            double K=P/(P+r);
            x=x+K*(zs[k]-x);
            P=(1.0-K)*P;
            char b1[32],b2[32];
            snprintf(b1,sizeof b1,"%.6f",x);
            snprintf(b2,sizeof b2,"%.6f",P);
            cout<<b1<<' '<<b2<<"\n";
        }
    }
    return 0;
}
