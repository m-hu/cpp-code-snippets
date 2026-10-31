#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
// Deflated Sharpe Ratio (DSR) & Probabilistic Sharpe Ratio (PSR),
// Bailey-Lopez de Prado: PSR(SR*) = Phi((SR-SR*)sqrt(T-1)/
// sqrt(1-g3*SR+(g4-1)/4*SR^2)); DSR = PSR(SR0) with SR0 from K trials.
// Phi via Abramowitz-Stegun erf, PhiInv via Acklam (bit-stable).
static double aerf(double x){
    int s=x<0?-1:1; x=fabs(x);
    double t=1.0/(1.0+0.3275911*x);
    double y=1.0-((((1.061405429*t-1.453152027)*t+1.421413741)*t-0.284496736)*t+0.254829592)*t*exp(-x*x);
    return s*y;
}
static double Phi(double x){ return 0.5*(1.0+aerf(x/sqrt(2.0))); }
static double PhiInv(double p){
    const double a1=-3.969683028665376e+01,a2=2.209460984245205e+02,a3=-2.759285104469687e+02;
    const double a4=1.383577518672690e+02,a5=-3.066479806614716e+01,a6=2.506628277459239e+00;
    const double b1=-5.447609879822406e+01,b2=1.615858368580409e+02,b3=-1.556989798598866e+02;
    const double b4=6.680131188771972e+01,b5=-1.328068155288572e+01;
    const double c1=-7.784894002430293e-03,c2=-3.223964580411365e-01,c3=-2.400758277161838e+00;
    const double c4=-2.549732539343734e+00,c5=4.374664141464968e+00,c6=2.938163982698783e+00;
    const double d1=7.784695709041462e-03,d2=3.224671290700398e-01,d3=2.445134137142996e+00,d4=3.754408661907416e+00;
    if(p<0.02425){double q=sqrt(-2.0*log(p));return (((((c1*q+c2)*q+c3)*q+c4)*q+c5)*q+c6)/((((d1*q+d2)*q+d3)*q+d4)*q+1.0);}
    if(p>0.97575){double q=sqrt(-2.0*log(1.0-p));return -(((((c1*q+c2)*q+c3)*q+c4)*q+c5)*q+c6)/((((d1*q+d2)*q+d3)*q+d4)*q+1.0);}
    double q=p-0.5,r=q*q;
    return (((((a1*r+a2)*r+a3)*r+a4)*r+a5)*r+a6)*q/(((((b1*r+b2)*r+b3)*r+b4)*r+b5)*r+1.0);
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N,K; double bench;
    if(!(cin>>N>>K>>bench)) return 0;
    vector<double> r(N); for(int i=0;i<N;i++)cin>>r[i];
    vector<double> tr(K); for(int i=0;i<K;i++)cin>>tr[i];
    double m=0; for(double x:r)m+=x; m/=N;
    double v=0,m2=0,m3=0,m4=0;
    for(double x:r){double d=x-m;v+=d*d;m2+=d*d;m3+=d*d*d;m4+=d*d*d*d;}
    v/=(N-1); m2/=N; m3/=N; m4/=N;
    double sd=sqrt(v);
    double SR=m/sd*sqrt(252.0);
    double g3=m3/pow(m2,1.5), g4=m4/(m2*m2);
    double den=1.0-g3*SR+(g4-1.0)/4.0*SR*SR; if(den<=0)den=1e-12;
    double sc=sqrt((double)(N-1))/sqrt(den);
    double PSR=Phi((SR-bench)*sc);
    double tm=0; for(double x:tr)tm+=x; tm/=K;
    double V=0; if(K>1){for(double x:tr)V+=(x-tm)*(x-tm); V/=(K-1);}
    double SR0=0;
    if(K>=2){
        const double g=0.5772156649015329, e=2.718281828459045;
        double a1=PhiInv(1.0-1.0/K), a2=PhiInv(1.0-1.0/(K*e));
        SR0=sqrt(V)*((1.0-g)*a1+g*a2);
    }
    double DSR=Phi((SR-SR0)*sc);
    cout.setf(ios::fixed); cout<<setprecision(6);
    cout<<"SR: "<<SR+0.0<<"\n";
    cout<<"SKEW: "<<g3+0.0<<" KURT: "<<g4+0.0<<"\n";
    cout<<"PSR: "<<PSR+0.0<<"\n";
    cout<<"DSR: "<<DSR+0.0<<" SR0: "<<SR0+0.0<<"\n";
    return 0;
}
