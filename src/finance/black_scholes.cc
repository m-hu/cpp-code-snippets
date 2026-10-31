#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
using namespace std;
double norm_cdf(double x){ return 0.5*(1.0+erf(x/sqrt(2.0))); }
double norm_pdf(double x){ return exp(-0.5*x*x)/sqrt(2.0*M_PI); }
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double S,K,T,r,sig;
    string type;
    if(!(cin>>S>>K>>T>>r>>sig>>type)) return 0;
    double d1=(log(S/K)+(r+0.5*sig*sig)*T)/(sig*sqrt(T));
    double d2=d1-sig*sqrt(T);
    double price,delta,gamma,vega,theta,rho;
    if(type=="call"){
        price=S*norm_cdf(d1)-K*exp(-r*T)*norm_cdf(d2);
        delta=norm_cdf(d1);
        rho=K*T*exp(-r*T)*norm_cdf(d2);
    } else {
        price=K*exp(-r*T)*norm_cdf(-d2)-S*norm_cdf(-d1);
        delta=norm_cdf(d1)-1.0;
        rho=-K*T*exp(-r*T)*norm_cdf(-d2);
    }
    gamma=norm_pdf(d1)/(S*sig*sqrt(T));
    vega=S*norm_pdf(d1)*sqrt(T);
    double term1 = -(S*norm_pdf(d1)*sig)/(2.0*sqrt(T));
    if(type=="call"){
        term1 -= r*K*exp(-r*T)*norm_cdf(d2);
    } else {
        term1 += r*K*exp(-r*T)*norm_cdf(-d2);
    }
    theta=term1;
    cout<<fixed<<setprecision(4)<<price<<"\n";
    cout<<fixed<<setprecision(4)<<delta<<"\n";
    cout<<fixed<<setprecision(4)<<gamma<<"\n";
    cout<<fixed<<setprecision(4)<<vega<<"\n";
    cout<<fixed<<setprecision(4)<<theta<<"\n";
    cout<<fixed<<setprecision(4)<<rho<<"\n";
    return 0;
}
