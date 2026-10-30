#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;
// Bet sizing from predicted probabilities & dynamic active averaging
// (AFML ch.10, essence): signed size s = 2p - 1; active position is the
// decay-weighted average pos = d*pos + (1-d)*s clamped to [-1, 1].
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; double d;
    if(!(cin>>n>>d)) return 0;
    vector<double> pr(n);
    for(int i=0;i<n;i++) cin>>pr[i];
    cout<<fixed<<setprecision(6)<<"SIZES:";
    vector<double> s(n);
    for(int i=0;i<n;i++){s[i]=2*pr[i]-1;cout<<" "<<s[i];}
    cout<<"\nACTIVE:";
    double pos=0;
    for(int i=0;i<n;i++){pos=d*pos+(1-d)*s[i];pos=max(-1.0,min(1.0,pos));cout<<" "<<pos;}
    cout<<"\n";
    return 0;
}
