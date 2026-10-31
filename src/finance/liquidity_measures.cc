#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;
// Market microstructure liquidity (5 measures): Roll's spread (2*sqrt(-cov)
// of close changes, else 0), Corwin-Schultz high-low spread (floored at 0),
// Kyle's lambda (OLS slope of returns on signed volume), Amihud illiquidity
// (mean |r|/dollar-volume) and VPIN over min(50,B) volume buckets.
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int B; if(!(cin>>B)) return 0;
    vector<double> O(B),H(B),L(B),C(B),V(B);
    for(int i=0;i<B;i++) cin>>O[i]>>H[i]>>L[i]>>C[i]>>V[i];
    // Roll
    double roll=0;
    if(B>=3){
        double m1=0,m2=0; int n=B-2;
        for(int t=1;t<B-1;t++){m1+=C[t]-C[t-1];m2+=C[t+1]-C[t];}
        m1/=n;m2/=n;
        double cv=0;
        for(int t=1;t<B-1;t++) cv+=((C[t]-C[t-1])-m1)*((C[t+1]-C[t])-m2);
        cv/=n;
        if(cv<0) roll=2*sqrt(-cv);
    }
    // Corwin-Schultz
    double cs=0;
    if(B>=2){
        double s=0; int cnt=0;
        for(int t=0;t<B-1;t++){
            double b0=log(H[t]/L[t]),b1=log(H[t+1]/L[t+1]);
            double beta=b0*b0+b1*b1;
            double g=log(max(H[t],H[t+1])/min(L[t],L[t+1]));
            double gamma=g*g;
            double alpha=(sqrt(2*beta)-sqrt(beta))/(3-2*sqrt(2.0))-sqrt(gamma/(3-2*sqrt(2.0)));
            double st=2*(exp(alpha)-1)/(1+exp(alpha));
            if(st<0) st=0;
            s+=st;cnt++;
        }
        cs=s/cnt;
    }
    // signs (tick rule)
    vector<int> sg(B,1);
    for(int t=1;t<B;t++) sg[t]=(C[t]>C[t-1]?1:(C[t]<C[t-1]?-1:sg[t-1]));
    // Kyle lambda
    double kyle=0;
    if(B>=2){
        double mx=0,mr=0; int n=B-1;
        for(int t=1;t<B;t++){mx+=sg[t]*V[t];mr+=C[t]/C[t-1]-1;}
        mx/=n;mr/=n;
        double cv=0,vv=0;
        for(int t=1;t<B;t++){cv+=(sg[t]*V[t]-mx)*((C[t]/C[t-1]-1)-mr);vv+=(sg[t]*V[t]-mx)*(sg[t]*V[t]-mx);}
        if(vv>0) kyle=cv/vv;
    }
    // Amihud
    double am=0; int an=0;
    for(int t=1;t<B;t++){
        double dv=C[t]*V[t];
        if(dv>0){am+=fabs(C[t]/C[t-1]-1)/dv;an++;}
    }
    double amihud=(an>0?am/an:0);
    // VPIN
    double tot=0; for(double x:V) tot+=x;
    int nb=min(50,B); if(nb<1) nb=1;
    double vb=tot/nb, vpin=0;
    double fill=0, buy=0, sell=0;
    for(int t=0;t<B;t++){
        double rem=V[t];
        while(rem>1e-12){
            double take=min(rem,vb-fill);
            if(sg[t]>0) buy+=take; else sell+=take;
            fill+=take; rem-=take;
            if(fill>=vb-1e-12){vpin+=fabs(buy-sell);fill=0;buy=0;sell=0;}
        }
    }
    if(fill>1e-12) vpin+=fabs(buy-sell);
    vpin=(tot>0?vpin/tot:0);
    cout<<fixed<<setprecision(6);
    cout<<"ROLL: "<<roll<<"\n";
    cout<<"CS: "<<cs<<"\n";
    cout<<"KYLE: "<<kyle<<"\n";
    cout<<"AMIHUD: "<<amihud<<"\n";
    cout<<"VPIN: "<<vpin<<"\n";
    return 0;
}
