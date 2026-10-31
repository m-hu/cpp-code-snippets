#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
// Seidel third-order aberration sums: paraxial marginal + chief trace, then
// S1..S5 (spherical, coma, astigmatism, Petzval, distortion) and chromatic
// C1 (axial) C2 (lateral) from surface contributions (Smith's formulas).
static double sn(double x){return fabs(x)<5e-7?0.0:x;}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int S; if(!(cin>>S)) return 0;
    vector<double> R(S),th(S),nd(S),dn(S);
    for(int j=0;j<S;j++)cin>>R[j]>>th[j]>>nd[j]>>dn[j];
    double h,u,hb,ub;cin>>h>>u>>hb>>ub;
    double H=ub*h-u*hb;
    double n=1.0,d=0.0;
    double S1=0,S2=0,S3=0,S4=0,S5=0,C1=0,C2=0;
    for(int j=0;j<S;j++){
        double c=(R[j]==0)?0.0:1.0/R[j];
        double np=nd[j],dp=dn[j];
        double up=(n*u-h*c*(np-n))/np;
        double ubp=(n*ub-hb*c*(np-n))/np;
        double A=n*(h*c+u), Ab=n*(hb*c+ub);
        double dun=up/np-u/n, dinv=1/np-1/n, ddn=dp/np-d/n;
        S1+=-A*A*h*dun; S2+=-A*Ab*h*dun; S3+=-Ab*Ab*h*dun;
        S4+=-H*H*c*dinv;
        if(fabs(A)>1e-12)S5+=-(Ab/A)*(Ab*Ab*h*dun+H*H*c*dinv);
        C1+=h*A*ddn; C2+=h*Ab*ddn;
        h=h+up*th[j]; u=up; hb=hb+ubp*th[j]; ub=ubp;
        n=np; d=dp;
    }
    cout.setf(ios::fixed);cout<<setprecision(6);
    cout<<"SEIDEL: "<<sn(S1+0.0)<<" "<<sn(S2+0.0)<<" "<<sn(S3+0.0)<<" "<<sn(S4+0.0)<<" "<<sn(S5+0.0)<<"\n";
    cout<<"CHROM: "<<sn(C1+0.0)<<" "<<sn(C2+0.0)<<"\n";
    return 0;
}
