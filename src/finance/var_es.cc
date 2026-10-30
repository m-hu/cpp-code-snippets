#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;
// Value-at-Risk (parametric delta-normal, historical simulation, Monte
// Carlo with LCG+Box-Muller) & Expected Shortfall + Kupiec POF and
// Christoffersen independence backtests. Acklam inverse-normal CDF.
static double phiinv(double p){
    const double a1=-3.969683028665376e+01,a2=2.209460984245205e+02,a3=-2.759285104469687e+02;
    const double a4=1.383577518672690e+02,a5=-3.066479806614716e+01,a6=2.506628277459239e+00;
    const double b1=-5.447609879822406e+01,b2=1.615858368580409e+02,b3=-1.556989798598866e+02;
    const double b4=6.680131188771972e+01,b5=-1.328068155288572e+01;
    const double c1=-7.784894002430293e-03,c2=-3.223964580411365e-01,c3=-2.400758277161838e+00;
    const double c4=-2.549732539343734e+00,c5=4.374664141464968e+00,c6=2.938163982698783e+00;
    const double d1=7.784695709041462e-03,d2=3.224671290700398e-01,d3=2.445134137142996e+00,d4=3.754408661907416e+00;
    double x,q,r;
    if(p<0.02425){
        q=sqrt(-2*log(p));
        x=(((((c1*q+c2)*q+c3)*q+c4)*q+c5)*q+c6)/((((d1*q+d2)*q+d3)*q+d4)*q+1);
    } else if(p<=0.97575){
        q=p-0.5;r=q*q;
        x=(((((a1*r+a2)*r+a3)*r+a4)*r+a5)*r+a6)*q/(((((b1*r+b2)*r+b3)*r+b4)*r+b5)*r+1);
    } else {
        q=sqrt(-2*log(1-p));
        x=-(((((c1*q+c2)*q+c3)*q+c4)*q+c5)*q+c6)/((((d1*q+d2)*q+d3)*q+d4)*q+1);
    }
    return x;
}
static double tlog(double a,double b){ return (b==0?0:b*log(a)); }
typedef unsigned long long u64;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int M,MCN; double alpha;
    if(!(cin>>M>>alpha>>MCN)) return 0;
    vector<double> r(M);
    for(int i=0;i<M;i++) cin>>r[i];
    double mu=0; for(double x:r) mu+=x; mu/=M;
    double vv=0; for(double x:r) vv+=(x-mu)*(x-mu); vv/=(M-1);
    double sd=sqrt(vv);
    double z=phiinv(alpha);
    double pvar=-(mu+sd*z);
    double pes=sd*exp(-z*z/2)/sqrt(2*M_PI)/alpha-mu;
    vector<double> s=r; sort(s.begin(),s.end());
    int idx=max(0,(int)ceil(alpha*M)-1);
    double hvar=-s[idx], hes=0;
    for(int i=0;i<=idx;i++) hes+=s[i];
    hes=-hes/(idx+1);
    u64 lcg=42;
    auto uni=[&](){lcg=lcg*6364136223846793005ULL+1442695040888963407ULL;return (double)((lcg>>11)+1)/9007199254740992.0;};
    vector<double> sim; sim.reserve(MCN);
    while((int)sim.size()<MCN){
        double u1=uni(),u2=uni();
        double rad=sqrt(-2*log(u1));
        sim.push_back(mu+sd*rad*cos(2*M_PI*u2));
        if((int)sim.size()<MCN) sim.push_back(mu+sd*rad*sin(2*M_PI*u2));
    }
    sort(sim.begin(),sim.end());
    int j=max(0,(int)ceil(alpha*MCN)-1);
    double mvar=-sim[j], mes=0;
    for(int i=0;i<=j;i++) mes+=sim[i];
    mes=-mes/(j+1);
    vector<int> hit(M,0);
    for(int i=0;i<M;i++) hit[i]=(r[i]<-hvar?1:0);
    int x=0; for(int v:hit) x+=v;
    double kup=-2*(tlog(1-alpha,M-x)+tlog(alpha,x))+2*(tlog(1-(double)x/M,M-x)+tlog((double)x/M,x));
    int n00=0,n01=0,n10=0,n11=0;
    for(int i=1;i<M;i++){
        if(hit[i-1]==0&&hit[i]==0)n00++;
        else if(hit[i-1]==0&&hit[i]==1)n01++;
        else if(hit[i-1]==1&&hit[i]==0)n10++;
        else n11++;
    }
    double pi0=(n00+n01)>0?(double)n01/(n00+n01):0;
    double pi1=(n10+n11)>0?(double)n11/(n10+n11):0;
    double pi=(double)(n01+n11)/(M-1);
    double chr=-2*(tlog(1-pi,n00+n10)+tlog(pi,n01+n11))
        +2*(tlog(1-pi0,n00)+tlog(pi0,n01)+tlog(1-pi1,n10)+tlog(pi1,n11));
    cout<<fixed<<setprecision(6);
    cout<<"PVAR: "<<pvar<<" PES: "<<pes<<"\n";
    cout<<"HVAR: "<<hvar<<" HES: "<<hes<<"\n";
    cout<<"MVAR: "<<mvar<<" MES: "<<mes<<"\n";
    cout<<"KUPIEC: "<<kup<<"\n";
    cout<<"CHRIST: "<<chr<<"\n";
    return 0;
}
