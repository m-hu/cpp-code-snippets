#include <iostream>
#include <vector>
using namespace std;
// Triple-barrier labeling & meta-labeling (AFML ch.3): for each event t0,
// scan t0+1..t0+H for first touch of +up (label +1) or -dn (label -1),
// else 0 at the vertical barrier; meta label = 1 iff side == label != 0.
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int M,H; double up,dn;
    if(!(cin>>M>>H>>up>>dn)) return 0;
    vector<double> px(M);
    for(int i=0;i<M;i++) cin>>px[i];
    int E;cin>>E;
    vector<int> ev(E), side(E);
    for(int j=0;j<E;j++) cin>>ev[j]>>side[j];
    vector<int> lab(E,0), meta(E,0);
    for(int j=0;j<E;j++){
        int t0=ev[j], L=0;
        for(int t=t0+1;t<M&&t<=t0+H;t++){
            double r=px[t]-px[t0];
            if(r>=up-1e-12){L=1;break;}
            if(r<=-dn+1e-12){L=-1;break;}
        }
        lab[j]=L;
        meta[j]=(L!=0&&side[j]==L?1:0);
    }
    cout<<"LABELS:";
    for(int x:lab) cout<<" "<<x;
    cout<<"\nMETA:";
    for(int x:meta) cout<<" "<<x;
    cout<<"\n";
    return 0;
}
