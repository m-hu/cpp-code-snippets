#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; if(!(cin>>n)||n<=0) return 0;
    vector<vector<double>> a(n,vector<double>(n));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin>>a[i][j];
    vector<vector<double>> L(n,vector<double>(n,0.0));
    for(int i=0;i<n;i++){
        for(int j=0;j<=i;j++){
            double s=a[i][j];
            for(int k=0;k<j;k++) s-=L[i][k]*L[j][k];
            if(i==j){
                if(s<=1e-9){ cout<<"NOT_POSITIVE_DEFINITE\n"; return 0; }
                L[i][j]=sqrt(s);
            } else {
                L[i][j]=s/L[j][j];
            }
        }
    }
    cout<<fixed<<setprecision(6);
    for(int i=0;i<n;i++){ for(int j=0;j<n;j++){ if(j) cout<<" "; cout<<L[i][j]; } cout<<"\n"; }
    return 0;
}
