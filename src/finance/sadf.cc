#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
// Supremum Augmented Dickey-Fuller explosive-bubble test (lag 0): for each
// expanding window [0..e], DF regression dy_t = a + b*y_{t-1}; SADF is the
// supremum of b's t-statistic (0.0 when the window is degenerate).
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int M; double r0;
    if(!(cin>>M>>r0)) return 0;
    vector<double> y(M);
    for(int i=0;i<M;i++) cin>>y[i];
    int emin=(int)(r0*M)-1;
    if(emin<3) emin=3;
    double sadf=-1e100; int arg=emin;
    for(int e=emin;e<M;e++){
        int nobs=e; // t = 1..e
        double my=0; for(int t=1;t<=e;t++) my+=y[t-1]; my/=nobs;
        double md=0; for(int t=1;t<=e;t++) md+=y[t]-y[t-1]; md/=nobs;
        double sxx=0,sxy=0;
        for(int t=1;t<=e;t++){sxx+=(y[t-1]-my)*(y[t-1]-my);sxy+=(y[t-1]-my)*((y[t]-y[t-1])-md);}
        double tst=0;
        if(sxx>0&&nobs>2){
            double b=sxy/sxx, a=md-b*my, sse=0;
            for(int t=1;t<=e;t++){double r=(y[t]-y[t-1])-a-b*y[t-1];sse+=r*r;}
            double s2=sse/(nobs-2);
            if(s2>0) tst=b/sqrt(s2/sxx);
        }
        if(tst>sadf){sadf=tst;arg=e;}
    }
    cout<<fixed<<setprecision(6)<<"SADF: "<<sadf<<"\n";
    cout<<"ARGMAX: "<<arg<<"\n";
    return 0;
}
