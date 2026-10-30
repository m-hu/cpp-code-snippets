#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <complex>
#include <string>
using namespace std;
// Jones & Mueller-Stokes polarization calculus: cascade of polarizers,
// waveplates and rotators; system Jones J, Mueller M = A(J x J*)A^-1,
// output Jones and Stokes vectors.
typedef complex<double> C;
struct M2{ C a[2][2]; };
static M2 mmul(const M2&A,const M2&B){M2 R;for(int i=0;i<2;i++)for(int j=0;j<2;j++){R.a[i][j]=0;for(int k=0;k<2;k++)R.a[i][j]+=A.a[i][k]*B.a[k][j];}return R;}
struct M4{ C a[4][4]; };
static M4 m4mul(const M4&A,const M4&B){M4 R;for(int i=0;i<4;i++)for(int j=0;j<4;j++){R.a[i][j]=0;for(int k=0;k<4;k++)R.a[i][j]+=A.a[i][k]*B.a[k][j];}return R;}
static double sn(double x){return fabs(x)<5e-7?0.0:x;}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    const double PI=acos(-1.0);
    int E; if(!(cin>>E)) return 0;
    M2 J; J.a[0][0]=1;J.a[0][1]=0;J.a[1][0]=0;J.a[1][1]=1;
    for(int e=0;e<E;e++){
        string kind; cin>>kind; M2 T;
        if(kind=="P"){double th;cin>>th;double t=th*PI/180.0,c=cos(t),s=sin(t);
            T.a[0][0]=c*c;T.a[0][1]=c*s;T.a[1][0]=c*s;T.a[1][1]=s*s;}
        else if(kind=="W"){double dl,th;cin>>dl>>th;double d=dl*PI/180.0,t=th*PI/180.0,c=cos(t),s=sin(t);
            M2 R,RI,D;R.a[0][0]=c;R.a[0][1]=s;R.a[1][0]=-s;R.a[1][1]=c;
            RI.a[0][0]=c;RI.a[0][1]=-s;RI.a[1][0]=s;RI.a[1][1]=c;
            D.a[0][0]=polar(1.0,d/2);D.a[0][1]=0;D.a[1][0]=0;D.a[1][1]=polar(1.0,-d/2);
            T=mmul(RI,mmul(D,R));}
        else{double ph;cin>>ph;double t=ph*PI/180.0,c=cos(t),s=sin(t);
            T.a[0][0]=c;T.a[0][1]=-s;T.a[1][0]=s;T.a[1][1]=c;}
        J=mmul(T,J);
    }
    double exr,exi,eyr,eyi; cin>>exr>>exi>>eyr>>eyi;
    double S[4]; for(int i=0;i<4;i++)cin>>S[i];
    C ox=J.a[0][0]*C(exr,exi)+J.a[0][1]*C(eyr,eyi);
    C oy=J.a[1][0]*C(exr,exi)+J.a[1][1]*C(eyr,eyi);
    M4 K; // J (x) conj(J)
    for(int i=0;i<2;i++)for(int j=0;j<2;j++)for(int k=0;k<2;k++)for(int l=0;l<2;l++)
        K.a[i*2+k][j*2+l]=J.a[i][j]*conj(J.a[k][l]);
    M4 A,AI;
    double ad[4][4]={{1,0,0,1},{1,0,0,-1},{0,1,1,0},{0,0,0,0}};
    for(int i=0;i<4;i++)for(int j=0;j<4;j++)A.a[i][j]=ad[i][j];
    A.a[3][1]=C(0,1);A.a[3][2]=C(0,-1);
    for(int i=0;i<4;i++)for(int j=0;j<4;j++)AI.a[i][j]=0;
    AI.a[0][0]=0.5;AI.a[0][1]=0.5;AI.a[1][2]=0.5;AI.a[1][3]=C(0,-0.5);
    AI.a[2][2]=0.5;AI.a[2][3]=C(0,0.5);AI.a[3][0]=0.5;AI.a[3][1]=-0.5;
    M4 M=m4mul(A,m4mul(K,AI));
    double O[4]={0,0,0,0};
    for(int i=0;i<4;i++)for(int j=0;j<4;j++)O[i]+=M.a[i][j].real()*S[j];
    cout.setf(ios::fixed);cout<<setprecision(6);
    cout<<"JONES:";double jv[8]={J.a[0][0].real(),J.a[0][0].imag(),J.a[0][1].real(),J.a[0][1].imag(),J.a[1][0].real(),J.a[1][0].imag(),J.a[1][1].real(),J.a[1][1].imag()};
    for(int i=0;i<8;i++)cout<<" "<<sn(jv[i]+0.0);
    cout<<"\nMUELLER:";for(int i=0;i<4;i++)for(int j=0;j<4;j++)cout<<" "<<sn(M.a[i][j].real()+0.0);
    cout<<"\nOUT_J: "<<sn(ox.real()+0.0)<<" "<<sn(ox.imag()+0.0)<<" "<<sn(oy.real()+0.0)<<" "<<sn(oy.imag()+0.0);
    cout<<"\nOUT_S:";for(int i=0;i<4;i++)cout<<" "<<sn(O[i]+0.0);
    cout<<"\n";
    return 0;
}
