#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;
// Feature importance (AFML ch.8): MDI via max single-split variance
// reduction per feature (exhaustive midpoints, value/index order); MDA via
// R^2 drop under deterministic cyclic shift of the column for model Xw;
// SFI via single-feature OLS (with intercept) R^2.
static double r2score(const vector<double>& y,const vector<double>& p){
    int n=y.size(); double mu=0; for(double v:y) mu+=v; mu/=n;
    double sse=0,sst=0;
    for(int i=0;i<n;i++){sse+=(y[i]-p[i])*(y[i]-p[i]);sst+=(y[i]-mu)*(y[i]-mu);}
    if(sst==0) return (sse==0?1.0:0.0);
    return 1-sse/sst;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,p; if(!(cin>>n>>p)) return 0;
    vector<vector<double>> X(n,vector<double>(p));
    for(int i=0;i<n;i++) for(int j=0;j<p;j++) cin>>X[i][j];
    vector<double> y(n);
    for(int i=0;i<n;i++) cin>>y[i];
    vector<double> w(p);
    for(int j=0;j<p;j++) cin>>w[j];
    double mu=0; for(double v:y) mu+=v; mu/=n;
    double tot=0; for(double v:y) tot+=(v-mu)*(v-mu);
    vector<double> mdi(p,0),mda(p,0),sfi(p,0);
    // MDI
    for(int j=0;j<p;j++){
        vector<int> idx(n); for(int i=0;i<n;i++) idx[i]=i;
        sort(idx.begin(),idx.end(),[&](int a,int b){return X[a][j]<X[b][j]||(X[a][j]==X[b][j]&&a<b);});
        double best=0;
        for(int s=1;s<n;s++){
            if(X[idx[s]][j]==X[idx[s-1]][j]) continue;
            int nl=s,nr=n-s;
            double ml=0,mr=0;
            for(int t=0;t<s;t++) ml+=y[idx[t]];
            for(int t=s;t<n;t++) mr+=y[idx[t]];
            ml/=nl;mr/=nr;
            double sl=0,sr=0;
            for(int t=0;t<s;t++) sl+=(y[idx[t]]-ml)*(y[idx[t]]-ml);
            for(int t=s;t<n;t++) sr+=(y[idx[t]]-mr)*(y[idx[t]]-mr);
            best=max(best,tot-sl-sr);
        }
        mdi[j]=best;
    }
    // MDA
    vector<double> base(n,0);
    for(int i=0;i<n;i++){double s=0;for(int j=0;j<p;j++)s+=X[i][j]*w[j];base[i]=s;}
    double r2b=r2score(y,base);
    for(int j=0;j<p;j++){
        vector<double> pr(n,0);
        for(int i=0;i<n;i++){double s=0;for(int k=0;k<p;k++){double v=(k==j?X[(i+1)%n][k]:X[i][k]);s+=v*w[k];}pr[i]=s;}
        mda[j]=r2b-r2score(y,pr);
    }
    // SFI
    for(int j=0;j<p;j++){
        double mx=0; for(int i=0;i<n;i++) mx+=X[i][j]; mx/=n;
        double cov=0,vv=0;
        for(int i=0;i<n;i++){cov+=(X[i][j]-mx)*(y[i]-mu);vv+=(X[i][j]-mx)*(X[i][j]-mx);}
        double slope=(vv==0?0:cov/vv), icept=mu-slope*mx;
        vector<double> pr(n);
        for(int i=0;i<n;i++) pr[i]=icept+slope*X[i][j];
        sfi[j]=r2score(y,pr);
    }
    cout<<fixed<<setprecision(6);
    cout<<"MDI:"; for(double v:mdi) cout<<" "<<v; cout<<"\n";
    cout<<"MDA:"; for(double v:mda) cout<<" "<<v; cout<<"\n";
    cout<<"SFI:"; for(double v:sfi) cout<<" "<<v; cout<<"\n";
    return 0;
}
