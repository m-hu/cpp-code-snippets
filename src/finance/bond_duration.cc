#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
// Bond analytics: price, Macaulay/modified duration, convexity (annualized,
// semiannual compounding), key-rate durations (+/-1bp per key tenor) and
// Redington immunization check vs a single liability payment.
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double ytm; int m;
    if(!(cin>>ytm>>m)) return 0;
    vector<int> kp(m); vector<double> cf(m);
    for(int i=0;i<m;i++) cin>>kp[i]>>cf[i];
    double yp=ytm/2;
    auto df=[&](int k){return pow(1+yp,-k);};
    double P=0; for(int i=0;i<m;i++) P+=cf[i]*df(kp[i]);
    double dper=0; for(int i=0;i<m;i++) dper+=kp[i]*cf[i]*df(kp[i]); dper/=P;
    double cper=0; for(int i=0;i<m;i++) cper+=kp[i]*(kp[i]+1)*cf[i]*df(kp[i]); cper/=P*(1+yp)*(1+yp);
    double mac=dper/2, mod=mac/(1+yp), conv=cper/4;
    int nk;cin>>nk;
    vector<int> keys(nk); for(int i=0;i<nk;i++) cin>>keys[i];
    vector<double> krd(nk,0);
    for(int j=0;j<nk;j++){
        double pu=0,pd=0;
        for(int i=0;i<m;i++){
            double r=(kp[i]==keys[j]?yp+0.0001:yp);
            pu+=cf[i]*pow(1+r,-kp[i]);
            r=(kp[i]==keys[j]?yp-0.0001:yp);
            pd+=cf[i]*pow(1+r,-kp[i]);
        }
        krd[j]=-(pu-pd)/(2*P*0.0001)/2;
    }
    int kl; double al;cin>>kl>>al;
    double pl=al*pow(1+yp,-kl);
    double dl=(double)kl, cl=kl*(kl+1)/((1+yp)*(1+yp));
    bool imm=(fabs(P-pl)/pl<1e-6&&fabs(dper-dl)<1e-4&&cper>cl+1e-9);
    cout<<fixed<<setprecision(6);
    cout<<"PRICE: "<<P<<"\n";
    cout<<"MAC: "<<mac<<"\n";
    cout<<"MOD: "<<mod<<"\n";
    cout<<"CONV: "<<conv<<"\n";
    cout<<"KRD:";
    for(double x:krd) cout<<" "<<x;
    cout<<"\nIMMUNIZED: "<<(imm?"YES":"NO")<<"\n";
    return 0;
}
