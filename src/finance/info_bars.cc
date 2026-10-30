#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
// Information-driven bars (AFML ch.2): tick bars (every N trades), volume
// bars (every V shares), dollar bars (every D dollars), tick-imbalance
// bars (|cum tick sign| >= T) and volume-run bars (|cum signed vol| >= R).
// Counts complete bars; lastclose = last complete bar close (else first px).
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N; double V,D,T,R;
    if(!(cin>>N>>V>>D>>T>>R)) return 0;
    int M;cin>>M;
    vector<double> px(M), vol(M);
    for(int i=0;i<M;i++) cin>>px[i]>>vol[i];
    // tick
    int nt=M/N; double tickc=(nt>0?px[nt*N-1]:px[0]);
    // volume
    int nv=0; double acc=0, volc=px[0];
    for(int i=0;i<M;i++){ acc+=vol[i]; if(acc>=V-1e-12){ nv++; acc=0; volc=px[i]; } }
    // dollar
    int nd_=0; acc=0; double dollc=px[0];
    for(int i=0;i<M;i++){ acc+=px[i]*vol[i]; if(acc>=D-1e-12){ nd_++; acc=0; dollc=px[i]; } }
    // tick imbalance (tick rule with previous-tick fill)
    int ntib=0; double cum=0, tibc=px[0]; int prev=1;
    for(int i=1;i<M;i++){
        int b=(px[i]>px[i-1]?1:(px[i]<px[i-1]?-1:prev));
        prev=b; cum+=b;
        if(fabs(cum)>=T-1e-12){ ntib++; cum=0; tibc=px[i]; }
    }
    // volume run (signed volume)
    int nvr=0; double cumv=0, vrc=px[0]; prev=1;
    for(int i=1;i<M;i++){
        int b=(px[i]>px[i-1]?1:(px[i]<px[i-1]?-1:prev));
        prev=b; cumv+=b*vol[i];
        if(fabs(cumv)>=R-1e-12){ nvr++; cumv=0; vrc=px[i]; }
    }
    cout<<fixed<<setprecision(2);
    cout<<"TICK: "<<nt<<" "<<tickc<<"\n";
    cout<<"VOLUME: "<<nv<<" "<<volc<<"\n";
    cout<<"DOLLAR: "<<nd_<<" "<<dollc<<"\n";
    cout<<"TIB: "<<ntib<<" "<<tibc<<"\n";
    cout<<"VRUN: "<<nvr<<" "<<vrc<<"\n";
    return 0;
}
