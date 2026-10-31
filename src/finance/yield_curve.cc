#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
// Zero-coupon yield curve bootstrapping (semiannual par curve at consecutive
// half-years) & forward rate extraction: df_j from par bond j, zeros as
// 2*(df^-1/j - 1), annualized 6M forwards 2*(df_{j-1}/df_j - 1).
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    vector<double> y(n);
    for(int i=0;i<n;i++) cin>>y[i];
    vector<double> df(n,0);
    for(int j=0;j<n;j++){
        double cp=y[j]*50.0, acc=0;
        for(int k=0;k<j;k++) acc+=cp*df[k];
        df[j]=(100.0-acc)/(100.0+cp);
    }
    cout<<fixed<<setprecision(6)<<"ZEROS:";
    for(int j=0;j<n;j++) cout<<" "<<2*(pow(df[j],-1.0/(j+1))-1);
    cout<<"\nFORWARDS:";
    for(int j=1;j<n;j++) cout<<" "<<2*(df[j-1]/df[j]-1);
    cout<<"\n";
    return 0;
}
