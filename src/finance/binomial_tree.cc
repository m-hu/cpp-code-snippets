#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double S,K,T,r,sig;
    int N;
    string type,style;
    if(!(cin>>S>>K>>T>>r>>sig>>N>>type>>style)) return 0;
    double dt=T/N;
    double u=exp(sig*sqrt(dt));
    double d=1.0/u;
    double disc=exp(-r*dt);
    double p=(exp(r*dt)-d)/(u-d);
    // clamp p to [0,1]
    p=max(0.0,min(1.0,p));
    vector<double> vals(N+1);
    for(int j=0;j<=N;j++){
        double ST=S*pow(u,j)*pow(d,N-j);
        if(type=="call") vals[j]=max(ST-K,0.0);
        else vals[j]=max(K-ST,0.0);
    }
    for(int step=N-1;step>=0;step--){
        for(int j=0;j<=step;j++){
            double hold=disc*(p*vals[j+1]+(1-p)*vals[j]);
            if(style=="american"){
                double ST=S*pow(u,j)*pow(d,step-j);
                double intrinsic=(type=="call"?max(ST-K,0.0):max(K-ST,0.0));
                vals[j]=max(hold,intrinsic);
            } else {
                vals[j]=hold;
            }
        }
    }
    cout<<fixed<<setprecision(4)<<vals[0]<<"\n";
    return 0;
}
