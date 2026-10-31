
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int N,IT; cin>>N>>IT;
        vector<double> x(N);
        for(int i=0;i<N;i++){double n,d;cin>>n>>d;x[i]=n/d;}
        double mn=x[0],mx=x[0],mean=0;
        for(double v:x){mn=min(mn,v);mx=max(mx,v);mean+=v;}
        mean/=N;
        double va=0;
        for(double v:x)va+=(v-mean)*(v-mean);
        va/=N; if(va<1e-6)va=1e-6;
        double w0=0.5,w1=0.5,mu0=mn,mu1=mx,v0=va,v1=va;
        vector<double> g0(N),g1(N);
        for(int it=0;it<IT;it++){
            for(int i=0;i<N;i++){
                double p0=w0*exp(-0.5*(x[i]-mu0)*(x[i]-mu0)/v0)/sqrt(v0);
                double p1=w1*exp(-0.5*(x[i]-mu1)*(x[i]-mu1)/v1)/sqrt(v1);
                double s=p0+p1;
                if(s==0){g0[i]=g1[i]=0.5;}
                else{g0[i]=p0/s;g1[i]=p1/s;}
            }
            double n0=0,n1=0;
            for(int i=0;i<N;i++){n0+=g0[i];n1+=g1[i];}
            w0=n0/N;w1=n1/N;
            mu0=0;mu1=0;
            for(int i=0;i<N;i++){mu0+=g0[i]*x[i];mu1+=g1[i]*x[i];}
            mu0/=n0;mu1/=n1;
            v0=0;v1=0;
            for(int i=0;i<N;i++){v0+=g0[i]*(x[i]-mu0)*(x[i]-mu0);v1+=g1[i]*(x[i]-mu1)*(x[i]-mu1);}
            v0/=n0;v1/=n1;
            if(v0<1e-6)v0=1e-6;
            if(v1<1e-6)v1=1e-6;
        }
        // order by mean
        if(mu1<mu0){swap(w0,w1);swap(mu0,mu1);swap(v0,v1);for(int i=0;i<N;i++)swap(g0[i],g1[i]);}
        cout<<"EM\n";
        char b[6][32];
        snprintf(b[0],32,"%.6f",w0);snprintf(b[1],32,"%.6f",mu0);snprintf(b[2],32,"%.6f",v0);
        snprintf(b[3],32,"%.6f",w1);snprintf(b[4],32,"%.6f",mu1);snprintf(b[5],32,"%.6f",v1);
        cout<<b[0]<<' '<<b[1]<<' '<<b[2]<<' '<<b[3]<<' '<<b[4]<<' '<<b[5]<<"\n";
        for(int i=0;i<N;i++){if(i)cout<<' ';cout<<(g1[i]>g0[i]?1:0);}
        cout<<"\n";
    }
    return 0;
}
