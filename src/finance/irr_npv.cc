#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
// Capital budgeting: NPV at the hurdle rate, IRR by bisection on
// [-0.9999, 10] (NONE without a sign change) and WACC = w_e r_e +
// w_d r_d (1 - tax).
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double rate; int m;
    if(!(cin>>rate>>m)) return 0;
    vector<double> cf(m);
    for(int i=0;i<m;i++) cin>>cf[i];
    auto npv=[&](double r){double s=0;for(int t=0;t<m;t++)s+=cf[t]*pow(1+r,-t);return s;};
    double N=npv(rate);
    double lo=-0.9999,hi=10.0,flo=npv(lo),fhi=npv(hi);
    bool has=(flo==0||fhi==0||(flo<0)!=(fhi<0));
    double irr=0;
    if(has){
        if(flo==0) irr=lo;
        else if(fhi==0) irr=hi;
        else{
            for(int it=0;it<200;it++){
                double mid=(lo+hi)/2,fm=npv(mid);
                if(fm==0){lo=hi=mid;break;}
                if((fm<0)!=(flo<0)){hi=mid;fhi=fm;}else{lo=mid;flo=fm;}
            }
            irr=(lo+hi)/2;
        }
    }
    double tax,we,re,wd,rd;
    cin>>tax>>we>>re>>wd>>rd;
    double wacc=we*re+wd*rd*(1-tax);
    cout<<fixed<<setprecision(6);
    cout<<"NPV: "<<N<<"\n";
    cout<<"IRR: ";
    if(has) cout<<irr<<"\n"; else cout<<"NONE\n";
    cout<<"WACC: "<<wacc<<"\n";
    return 0;
}
