#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
// Symmetric CUSUM filter (AFML ch.2): S+ = max(0, S+ + y), S- = min(0, S- + y)
// with y_t = p_t - mean; event when S+ > h or S- < -h, then reset both.
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double h; int M;
    if(!(cin>>h>>M)) return 0;
    vector<double> px(M);
    for(int i=0;i<M;i++) cin>>px[i];
    double mu=0; for(double x:px) mu+=x; mu/=M;
    double sp=0, sn=0;
    vector<int> ev;
    for(int i=0;i<M;i++){
        double y=px[i]-mu;
        sp+=y; if(sp<0) sp=0;
        sn+=y; if(sn>0) sn=0;
        if(sp>h||sn<-h){ ev.push_back(i); sp=0; sn=0; }
    }
    cout<<"EVENTS:";
    for(int e:ev) cout<<" "<<e;
    cout<<"\nCOUNT: "<<ev.size()<<"\n";
    return 0;
}
