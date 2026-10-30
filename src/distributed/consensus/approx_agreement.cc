#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,f,R;
    if(!(cin>>n>>f>>R)) return 0;
    vector<double> vals(n);
    for(int i=0;i<n;i++) cin>>vals[i];
    for(int r=0;r<R;r++){
        vector<double> nvals(n);
        for(int i=0;i<n;i++){
            vector<double> recvd=vals;
            sort(recvd.begin(),recvd.end());
            int lo=f,hi=n-f;
            if(hi<=lo){ nvals[i]=vals[i]; continue; }
            double s=0;
            for(int k=lo;k<hi;k++) s+=recvd[k];
            nvals[i]=s/(hi-lo);
        }
        vals=nvals;
    }
    cout<<fixed<<setprecision(6);
    for(int i=0;i<n;i++) cout<<"P"<<i<<": "<<vals[i]<<"\n";
    return 0;
}
