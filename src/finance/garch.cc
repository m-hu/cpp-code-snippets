#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
// EWMA (RiskMetrics) & GARCH(1,1) volatility filtering; GARCH parameters by
// variance-targeted grid MLE (alpha 0.01..0.30, beta 0.60..0.95, first max).
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int M; double lam;
    if(!(cin>>M>>lam)) return 0;
    vector<double> r(M);
    for(int i=0;i<M;i++) cin>>r[i];
    double mu=0; for(double x:r) mu+=x; mu/=M;
    double var=0; for(double x:r) var+=(x-mu)*(x-mu); var/=(M-1);
    double v=var;
    for(int t=0;t<M;t++) v=lam*v+(1-lam)*r[t]*r[t];
    double ewma=v;
    double bom=0,ba=0,bb=0,bll=-1e300,bgf=var;
    for(int ai=1;ai<=30;ai++){
        double a=ai*0.01;
        for(int bi=60;bi<=95;bi++){
            double b=bi*0.01;
            if(a+b>=1) continue;
            double om=var*(1-a-b), vv=var, ll=0;
            for(int t=0;t<M;t++){ ll+=-0.5*(log(vv)+r[t]*r[t]/vv); vv=om+a*r[t]*r[t]+b*vv; }
            if(ll>bll){bll=ll;bom=om;ba=a;bb=b;bgf=vv;}
        }
    }
    cout<<fixed<<setprecision(6);
    cout<<"EWMA: "<<ewma<<"\n";
    cout<<"GARCH: "<<bom<<" "<<ba<<" "<<bb<<" "<<bll<<"\n";
    cout<<"GFILTER: "<<bgf<<"\n";
    return 0;
}
