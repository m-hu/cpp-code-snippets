#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <complex>
using namespace std;
// Thin-film multilayer characteristic matrix method: for s & p polarizations
// computes amplitude reflection/transmission and R/T of a layer stack.
typedef complex<double> C;
static double sn(double x){return fabs(x)<5e-7?0.0:x;}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    const double PI=acos(-1.0);
    int L; double lambda,theta0,n0,ns;
    if(!(cin>>L>>lambda>>theta0>>n0>>ns)) return 0;
    vector<double> nn(L),dd(L);
    for(int j=0;j<L;j++)cin>>nn[j]>>dd[j];
    double s0=n0*sin(theta0*PI/180.0);
    for(int pol=0;pol<2;pol++){
        C M11=1,M12=0,M21=0,M22=1;
        for(int j=0;j<L;j++){
            double st=s0/nn[j]; if(st>1)st=1; if(st<-1)st=-1;
            double ct=sqrt(max(0.0,1-st*st));
            double eta=(pol==0)?nn[j]*ct:nn[j]/ct;
            double delta=2*PI*nn[j]*dd[j]*ct/lambda;
            C c=cos(delta),s=sin(delta),iu(0,1);
            C N11=c, N12=iu*s/eta, N21=iu*eta*s, N22=c;
            C O11=M11*N11+M12*N21, O12=M11*N12+M12*N22;
            C O21=M21*N11+M22*N21, O22=M21*N12+M22*N22;
            M11=O11;M12=O12;M21=O21;M22=O22;
        }
        double st0=sin(theta0*PI/180.0), ct0=cos(theta0*PI/180.0);
        double sts=s0/ns; if(sts>1)sts=1; if(sts<-1)sts=-1;
        double cts=sqrt(max(0.0,1-sts*sts));
        double e0=(pol==0)?n0*ct0:n0/ct0, es=(pol==0)?ns*cts:ns/cts;
        C den=e0*M11+e0*es*M12+M21+es*M22;
        C r=(e0*M11+e0*es*M12-M21-es*M22)/den;
        C t=2.0*e0/den;
        double R=norm(r), T=(es/e0)*norm(t);
        cout.setf(ios::fixed);cout<<setprecision(6);
        cout<<(pol==0?"S: ":"P: ")<<"r "<<sn(r.real()+0.0)<<" "<<sn(r.imag()+0.0)
            <<" R "<<sn(R+0.0)<<" T "<<sn(T+0.0)<<"\n";
    }
    return 0;
}
