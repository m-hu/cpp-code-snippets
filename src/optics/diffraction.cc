#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
// Fraunhofer & Fresnel scalar diffraction via radix-2 FFT: aperture samples
// (Fresnel premultiplied by the chirp exp(i pi x^2/lambda z)) are Fourier
// transformed; output peak-normalized intensities.
static double sn(double x){return fabs(x)<5e-7?0.0:x;}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    const double PI=acos(-1.0);
    int N,mode; if(!(cin>>N>>mode)) return 0;
    vector<double> A(N); for(int j=0;j<N;j++)cin>>A[j];
    double lam=1,z=1,dx=1;
    if(mode==1)cin>>lam>>z>>dx;
    vector<double> re(N),im(N);
    for(int j=0;j<N;j++){
        if(mode==0){re[j]=A[j];im[j]=0;}
        else{double x=(j-N/2.0)*dx;double ph=PI*x*x/(lam*z);
            re[j]=A[j]*cos(ph);im[j]=A[j]*sin(ph);}
    }
    for(int i=1,kk=0;i<N;i++){int b=N>>1;for(;kk&b;b>>=1)kk&=~b;kk|=b;
        if(i<kk){swap(re[i],re[kk]);swap(im[i],im[kk]);}}
    for(int m=2;m<=N;m*=2){
        double ang=-2*PI/m;double wr=cos(ang),wi=sin(ang);
        for(int k=0;k<N;k+=m){
            double cr=1,ci=0;
            for(int j=0;j<m/2;j++){
                double tr=cr*re[k+j+m/2]-ci*im[k+j+m/2];
                double ti=cr*im[k+j+m/2]+ci*re[k+j+m/2];
                re[k+j+m/2]=re[k+j]-tr;im[k+j+m/2]=im[k+j]-ti;
                re[k+j]+=tr;im[k+j]+=ti;
                double nr=cr*wr-ci*wi;ci=cr*wi+ci*wr;cr=nr;
            }
        }
    }
    vector<double> I(N);double mx=0;
    for(int k=0;k<N;k++){I[k]=re[k]*re[k]+im[k]*im[k];if(I[k]>mx)mx=I[k];}
    cout.setf(ios::fixed);cout<<setprecision(6);
    cout<<"I:";for(int k=0;k<N;k++)cout<<" "<<sn(I[k]/mx+0.0);
    cout<<"\n";
    return 0;
}
