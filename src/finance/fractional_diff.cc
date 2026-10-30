#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
// Fixed-width window fractional differentiation (AFML ch.5): weights
// w_0 = 1, w_k = -w_{k-1} (d-k+1)/k; y_t = sum_k w_k x_{t-k} over window L.
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double d; int L,M;
    if(!(cin>>d>>L>>M)) return 0;
    vector<double> x(M);
    for(int i=0;i<M;i++) cin>>x[i];
    vector<double> w(L,0); w[0]=1;
    for(int k=1;k<L;k++) w[k]=-w[k-1]*(d-k+1)/k;
    cout<<fixed<<setprecision(6)<<"W:";
    for(double v:w) cout<<" "<<v;
    cout<<"\nY:";
    for(int t=L-1;t<M;t++){double s=0;for(int k=0;k<L;k++) s+=w[k]*x[t-k];cout<<" "<<s;}
    cout<<"\n";
    return 0;
}
