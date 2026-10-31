#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
// Markowitz mean-variance (min-variance & tangency via Lagrange systems,
// efficient frontier at 3 targets) + Black-Litterman posterior blending
// for one view. Small Gaussian solver with first-max partial pivoting.
static vector<double> solve(vector<vector<double>> A,vector<double> b){
    int n=A.size();
    for(int k=0;k<n;k++){
        int piv=k; double best=fabs(A[k][k]);
        for(int i=k+1;i<n;i++) if(fabs(A[i][k])>best){best=fabs(A[i][k]);piv=i;}
        swap(A[k],A[piv]); swap(b[k],b[piv]);
        for(int i=k+1;i<n;i++){
            double f=A[i][k]/A[k][k];
            for(int j=k;j<n;j++) A[i][j]-=f*A[k][j];
            b[i]-=f*b[k];
        }
    }
    vector<double> x(n,0);
    for(int k=n-1;k>=0;k--){
        double s=b[k];
        for(int j=k+1;j<n;j++) s-=A[k][j]*x[j];
        x[k]=s/A[k][k];
    }
    return x;
}
static vector<vector<double>> inverse(vector<vector<double>> A){
    int n=A.size();
    vector<vector<double>> I(n,vector<double>(n,0));
    for(int i=0;i<n;i++) I[i][i]=1;
    for(int k=0;k<n;k++){
        int piv=k; double best=fabs(A[k][k]);
        for(int i=k+1;i<n;i++) if(fabs(A[i][k])>best){best=fabs(A[i][k]);piv=i;}
        swap(A[k],A[piv]); swap(I[k],I[piv]);
        double d=A[k][k];
        for(int j=0;j<n;j++){A[k][j]/=d;I[k][j]/=d;}
        for(int i=0;i<n;i++){
            if(i==k) continue;
            double f=A[i][k];
            for(int j=0;j<n;j++){A[i][j]-=f*A[k][j];I[i][j]-=f*I[k][j];}
        }
    }
    return I;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    vector<double> mu(n);
    for(int i=0;i<n;i++) cin>>mu[i];
    vector<vector<double>> S(n,vector<double>(n));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin>>S[i][j];
    double rf;cin>>rf;
    vector<double> tg(3); for(int i=0;i<3;i++) cin>>tg[i];
    double tau;cin>>tau;
    vector<double> P(n); for(int i=0;i<n;i++) cin>>P[i];
    double Q,om;cin>>Q>>om;
    // min variance
    vector<vector<double>> A(n+1,vector<double>(n+1,0));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) A[i][j]=S[i][j];
    for(int i=0;i<n;i++){A[i][n]=1;A[n][i]=1;}
    vector<double> b(n+1,0); b[n]=1;
    vector<double> sol=solve(A,b);
    // tangency
    vector<double> ex(n); for(int i=0;i<n;i++) ex[i]=mu[i]-rf;
    vector<double> tw=solve(S,ex);
    double ts=0; for(double x:tw) ts+=x;
    for(double &x:tw) x/=ts;
    // frontier
    vector<double> fvar(3,0);
    for(int f=0;f<3;f++){
        vector<vector<double>> F(n+2,vector<double>(n+2,0));
        for(int i=0;i<n;i++) for(int j=0;j<n;j++) F[i][j]=S[i][j];
        for(int i=0;i<n;i++){F[i][n]=mu[i];F[n][i]=mu[i];F[i][n+1]=1;F[n+1][i]=1;}
        vector<double> fb(n+2,0); fb[n]=tg[f]; fb[n+1]=1;
        vector<double> w=solve(F,fb);
        double v=0;
        for(int i=0;i<n;i++) for(int j=0;j<n;j++) v+=w[i]*S[i][j]*w[j];
        fvar[f]=v;
    }
    // Black-Litterman, one view
    vector<vector<double>> tS(n,vector<double>(n));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) tS[i][j]=S[i][j]*tau;
    vector<vector<double>> iTS=inverse(tS);
    vector<vector<double>> M(n,vector<double>(n));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) M[i][j]=iTS[i][j]+P[i]*P[j]/om;
    vector<double> rhs(n,0);
    for(int i=0;i<n;i++){
        double s=0; for(int j=0;j<n;j++) s+=iTS[i][j]*mu[j];
        rhs[i]=s+P[i]*Q/om;
    }
    vector<vector<double>> iM=inverse(M);
    vector<double> bl(n,0);
    for(int i=0;i<n;i++){double s=0;for(int j=0;j<n;j++)s+=iM[i][j]*rhs[j];bl[i]=s;}
    cout<<fixed<<setprecision(6);
    cout<<"MINVAR:"; for(int i=0;i<n;i++) cout<<" "<<sol[i]; cout<<"\n";
    cout<<"TANGENCY:"; for(double x:tw) cout<<" "<<x; cout<<"\n";
    cout<<"FRONTIER:";
    for(int f=0;f<3;f++) cout<<" "<<tg[f]<<","<<fvar[f];
    cout<<"\nBL:"; for(double x:bl) cout<<" "<<x; cout<<"\n";
    return 0;
}
