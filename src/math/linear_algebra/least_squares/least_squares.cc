#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int m,n;
    if(!(cin>>m>>n)||m<=0||n<=0) return 0;
    vector<vector<double>> A(m,vector<double>(n));
    for(int i=0;i<m;i++) for(int j=0;j<n;j++) cin>>A[i][j];
    vector<double> b(m); for(int i=0;i<m;i++) cin>>b[i];
    // Normal equations: AtA x = Atb
    vector<vector<double>> AtA(n,vector<double>(n,0));
    vector<double> Atb(n,0);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            double s=0; for(int k=0;k<m;k++) s+=A[k][i]*A[k][j];
            AtA[i][j]=s;
        }
        double s=0; for(int k=0;k<m;k++) s+=A[k][i]*b[k];
        Atb[i]=s;
    }
    // Gauss elimination with partial pivot
    vector<vector<double>> aug(n,vector<double>(n+1));
    for(int i=0;i<n;i++){ for(int j=0;j<n;j++) aug[i][j]=AtA[i][j]; aug[i][n]=Atb[i]; }
    for(int col=0;col<n;col++){
        int pivot=col; double best=fabs(aug[col][col]);
        for(int row=col+1;row<n;row++) if(fabs(aug[row][col])>best){best=fabs(aug[row][col]);pivot=row;}
        if(best<1e-12){ cout<<"SINGULAR\n"; return 0; }
        if(pivot!=col) swap(aug[pivot],aug[col]);
        for(int row=col+1;row<n;row++){
            double f=aug[row][col]/aug[col][col];
            for(int j=col;j<=n;j++) aug[row][j]-=f*aug[col][j];
        }
    }
    vector<double> x(n,0);
    for(int i=n-1;i>=0;i--){ double s=aug[i][n]; for(int j=i+1;j<n;j++) s-=aug[i][j]*x[j]; x[i]=s/aug[i][i]; }
    cout<<fixed<<setprecision(6);
    for(int i=0;i<n;i++){ if(i) cout<<" "; cout<<x[i]; } cout<<"\n";
    return 0;
}
