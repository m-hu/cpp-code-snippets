#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;
double norm_cdf(double x){ return 0.5*(1.0+erf(x/sqrt(2.0))); }
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if(!(cin>>n)) return 0;
    vector<double> rets(n);
    for(int i=0;i<n;i++) cin>>rets[i];
    double rf;
    cin>>rf;
    // annualized Sharpe = mean(excess) / std(excess) * sqrt(252)
    double mu=0;
    for(double x:rets) mu+=x;
    mu/=n;
    double excess_mu=mu-rf;
    double var=0;
    for(double x:rets) var+=(x-mu)*(x-mu);
    var/=(n-1);
    double sd=sqrt(var);
    double sr = (sd==0?0:excess_mu/sd*sqrt(252.0));
    // PSR: P[SR* > SR_benchmark] using normal approx
    // PSR = Phi( (SR - SR_b) * sqrt(T-1) / sqrt(1 - skew*SR + kurtosis/4*(SR^2-1)) )
    // Simplified: use standard error of SR ~ sqrt((1 + 0.5*SR^2)/T)
    double T=n;
    // compute skewness and kurtosis of returns
    double m2=0,m3=0,m4=0;
    for(double x:rets){ double d=x-mu; m2+=d*d; m3+=d*d*d; m4+=d*d*d*d; }
    m2/=n; m3/=n; m4/=n;
    double skew = (m2==0?0:m3/pow(m2,1.5));
    double kurt = (m2==0?0:m4/(m2*m2));
    double sr_benchmark=0;
    // read optional benchmark
    if(cin>>sr_benchmark){}
    else sr_benchmark=0;
    double numer = (sr - sr_benchmark)*sqrt(T-1);
    double denom2 = 1.0 - skew*sr + (kurt-1.0)/4.0*sr*sr;
    if(denom2<0) denom2=1.0;
    double denom=sqrt(denom2);
    double psr = norm_cdf(numer/denom);
    cout<<fixed<<setprecision(4)<<sr<<"\n";
    cout<<fixed<<setprecision(4)<<psr<<"\n";
    return 0;
}
