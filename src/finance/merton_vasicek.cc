#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
// Merton structural credit model (equity-implied assets, distance to
// default, PD via Newton/fixed-point) & Vasicek one-factor Gaussian copula
// CDO tranche expected loss via 10-point Gauss-Hermite quadrature.
// Self-contained erf (AS 7.1.26) & Acklam inverse-normal in all languages.
static double erf7(double x){
    const double a1=0.254829592,a2=-0.284496736,a3=1.421413741,a4=-1.453152027,a5=1.061405429,p=0.3275911;
    int s=(x<0?-1:1);
    double ax=fabs(x),t=1/(1+p*ax);
    double poly=(((((a5*t+a4)*t+a3)*t+a2)*t+a1));
    return s*(1-poly*t*exp(-ax*ax));
}
static double ncdf(double x){ return 0.5*(1+erf7(x/sqrt(2.0))); }
static double phiinv(double p){
    const double a1=-3.969683028665376e+01,a2=2.209460984245205e+02,a3=-2.759285104469687e+02;
    const double a4=1.383577518672690e+02,a5=-3.066479806614716e+01,a6=2.506628277459239e+00;
    const double b1=-5.447609879822406e+01,b2=1.615858368580409e+02,b3=-1.556989798598866e+02;
    const double b4=6.680131188771972e+01,b5=-1.328068155288572e+01;
    const double c1=-7.784894002430293e-03,c2=-3.223964580411365e-01,c3=-2.400758277161838e+00;
    const double c4=-2.549732539343734e+00,c5=4.374664141464968e+00,c6=2.938163982698783e+00;
    const double d1=7.784695709041462e-03,d2=3.224671290700398e-01,d3=2.445134137142996e+00,d4=3.754408661907416e+00;
    double x,q,r;
    if(p<0.02425){ q=sqrt(-2*log(p)); x=(((((c1*q+c2)*q+c3)*q+c4)*q+c5)*q+c6)/((((d1*q+d2)*q+d3)*q+d4)*q+1); }
    else if(p<=0.97575){ q=p-0.5;r=q*q; x=(((((a1*r+a2)*r+a3)*r+a4)*r+a5)*r+a6)*q/(((((b1*r+b2)*r+b3)*r+b4)*r+b5)*r+1); }
    else { q=sqrt(-2*log(1-p)); x=-(((((c1*q+c2)*q+c3)*q+c4)*q+c5)*q+c6)/((((d1*q+d2)*q+d3)*q+d4)*q+1); }
    return x;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double E,sE,D,rr,T;
    if(!(cin>>E>>sE>>D>>rr>>T)) return 0;
    double sA=sE*E/(E+D);
    double A=E+D*exp(-rr*T);
    for(int it=0;it<100;it++){
        for(int nt=0;nt<50;nt++){
            double d1=(log(A/D)+(rr+0.5*sA*sA)*T)/(sA*sqrt(T));
            double d2=d1-sA*sqrt(T);
            double C=A*ncdf(d1)-D*exp(-rr*T)*ncdf(d2);
            double delta=ncdf(d1);
            A=A-(C-E)/delta;
        }
        double d1=(log(A/D)+(rr+0.5*sA*sA)*T)/(sA*sqrt(T));
        sA=sE*E/(ncdf(d1)*A);
    }
    double DD=(log(A/D)+(rr-0.5*sA*sA)*T)/(sA*sqrt(T));
    double PD=ncdf(-DD);
    double p,rho,att,det;
    cin>>p>>rho>>att>>det;
    const double gx[5]={0.3429013272237046,1.036610829789514,1.756683649299882,2.53273167423279,3.436159118837738};
    const double gw[5]={0.6108626337353258,0.2401386110823147,0.03387439445548106,0.001343645746781232,7.64043285523262e-06};
    double pinv=phiinv(p), sqr=sqrt(rho), sq1=sqrt(1-rho), acc=0;
    for(int i=0;i<5;i++){
        for(int s=-1;s<=1;s+=2){
            double z=s*sqrt(2.0)*gx[i];
            double P=ncdf((pinv-sqr*z)/sq1);
            double L=(P-att)/(det-att);
            if(L<0)L=0; if(L>1)L=1;
            acc+=gw[i]*L;
        }
    }
    double el=acc/sqrt(M_PI);
    cout<<fixed<<setprecision(6);
    cout<<"MERTON: "<<A<<" "<<sA<<" "<<DD<<" "<<PD<<"\n";
    cout<<"VASICEK: "<<el<<"\n";
    return 0;
}
