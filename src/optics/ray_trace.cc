#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
// Exact 3D ray tracing through centered spherical surfaces (R=0 plano):
// sphere intersection, vector Snell refraction, optical path length.
static double sn(double x){return fabs(x)<5e-7?0.0:x;}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int S; if(!(cin>>S)) return 0;
    vector<double> zv(S),RR(S),na(S);
    for(int j=0;j<S;j++)cin>>zv[j]>>RR[j]>>na[j];
    int M; cin>>M;
    cout.setf(ios::fixed);cout<<setprecision(6);
    for(int m=0;m<M;m++){
        double ox,oy,oz,dx,dy,dz;cin>>ox>>oy>>oz>>dx>>dy>>dz;
        double dl=sqrt(dx*dx+dy*dy+dz*dz);dx/=dl;dy/=dl;dz/=dl;
        double n1=1.0,opl=0; bool ok=true;
        vector<double> hx(S),hy(S);
        for(int j=0;j<S;j++){
            double t=-1;
            if(RR[j]==0){ if(dz!=0) t=(zv[j]-oz)/dz; }
            else{
                double cx=0,cy=0,cz=zv[j]+RR[j];
                double ocx=ox-cx,ocy=oy-cy,ocz=oz-cz;
                double b=dx*ocx+dy*ocy+dz*ocz;
                double c=ocx*ocx+ocy*ocy+ocz*ocz-RR[j]*RR[j];
                double disc=b*b-c;
                if(disc>=0){double sq=sqrt(disc),t1=-b-sq,t2=-b+sq;
                    if(t1>1e-9)t=t1;else if(t2>1e-9)t=t2;}
            }
            if(t<1e-9){ok=false;break;}
            opl+=n1*t;
            double px=ox+dx*t,py=oy+dy*t,pz=oz+dz*t;
            hx[j]=px;hy[j]=py;
            double nx,ny,nz;
            if(RR[j]==0){nx=0;ny=0;nz=1;}
            else{double ar=fabs(RR[j]);nx=px/ar;ny=py/ar;nz=(pz-(zv[j]+RR[j]))/ar;
                double nl=sqrt(nx*nx+ny*ny+nz*nz);nx/=nl;ny/=nl;nz/=nl;}
            if(dx*nx+dy*ny+dz*nz>0){nx=-nx;ny=-ny;nz=-nz;}
            double eta=n1/na[j];
            double c1=-(dx*nx+dy*ny+dz*nz);
            double s2t=eta*eta*(1-c1*c1);
            if(s2t>1){ok=false;break;}
            double c2=sqrt(max(0.0,1-s2t));
            double k=eta*c1-c2;
            dx=eta*dx+k*nx;dy=eta*dy+k*ny;dz=eta*dz+k*nz;
            ox=px+dx*1e-9;oy=py+dy*1e-9;oz=pz+dz*1e-9;
            n1=na[j];
        }
        if(!ok){cout<<"RAY "<<m<<" MISS\n";continue;}
        cout<<"RAY "<<m<<" HIT:";for(int j=0;j<S;j++)cout<<" "<<sn(hx[j]+0.0)<<" "<<sn(hy[j]+0.0);
        cout<<"\nRAY "<<m<<" DIR: "<<sn(dx+0.0)<<" "<<sn(dy+0.0)<<" "<<sn(dz+0.0);
        cout<<"\nRAY "<<m<<" OPL: "<<sn(opl+0.0)<<"\n";
    }
    return 0;
}
