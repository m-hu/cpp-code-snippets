#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
// Hierarchical Risk Parity (AFML ch.16): single-linkage clustering on
// correlation distance (first-min lex order), quasi-diagonal leaf order,
// recursive bisection with inverse-variance cluster weights.
static double cvar(const vector<vector<double>>& S,const vector<int>& items,const vector<double>& iv){
    double wsum=0; for(int i:items) wsum+=iv[i];
    double v=0;
    for(int i:items) for(int j:items) v+=(iv[i]/wsum)*(iv[j]/wsum)*S[i][j];
    return v;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    vector<vector<double>> S(n,vector<double>(n));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin>>S[i][j];
    vector<double> sd(n);
    for(int i=0;i<n;i++) sd[i]=sqrt(S[i][i]);
    vector<vector<double>> D(n,vector<double>(n,0));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++){
        double rho=S[i][j]/(sd[i]*sd[j]);
        rho=max(-1.0,min(1.0,rho));
        D[i][j]=sqrt(max(0.0,0.5*(1-rho)));
    }
    // single linkage; clusters indexed 0..2n-2 (leaves 0..n-1)
    vector<vector<int>> members(2*n-1);
    for(int i=0;i<n;i++) members[i].push_back(i);
    vector<int> alive(2*n-1,0);
    for(int i=0;i<n;i++) alive[i]=1;
    vector<vector<double>> CD(2*n-1,vector<double>(2*n-1,1e100));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) CD[i][j]=D[i][j];
    vector<int> L(2*n-1,-1),R(2*n-1,-1);
    int next=n;
    for(int m=0;m<n-1;m++){
        double best=1e100; int bi=-1,bj=-1;
        for(int i=0;i<next;i++) if(alive[i])
            for(int j=i+1;j<next;j++) if(alive[j])
                if(CD[i][j]<best){best=CD[i][j];bi=i;bj=j;}
        alive[bi]=0;alive[bj]=0;alive[next]=1;
        L[next]=bi;R[next]=bj;
        members[next]=members[bi];
        for(int x:members[bj]) members[next].push_back(x);
        for(int i=0;i<next;i++) if(alive[i]){
            double dd=min(CD[bi][i],CD[bj][i]);
            CD[next][i]=CD[i][next]=dd;
        }
        next++;
    }
    vector<int> order;
    vector<int> tmp;
    tmp.push_back(2*n-2);
    while(!tmp.empty()){
        int u=tmp.back();tmp.pop_back();
        if(u<n) order.push_back(u);
        else{tmp.push_back(R[u]);tmp.push_back(L[u]);}
    }
    vector<double> iv(n);
    for(int i=0;i<n;i++) iv[i]=1.0/S[i][i];
    vector<double> w(n,1.0);
    vector<vector<int>> work={order};
    while(!work.empty()){
        vector<int> cur=work.back();work.pop_back();
        if(cur.size()<2) continue;
        size_t mid=cur.size()/2;
        vector<int> Lc(cur.begin(),cur.begin()+mid),Rc(cur.begin()+mid,cur.end());
        double vl=cvar(S,Lc,iv),vr=cvar(S,Rc,iv);
        double a=1-vl/(vl+vr);
        for(int i:Lc) w[i]*=a;
        for(int i:Rc) w[i]*=(1-a);
        work.push_back(Lc);work.push_back(Rc);
    }
    double ws=0; for(double x:w) ws+=x;
    for(double &x:w) x/=ws;
    cout<<"ORDER:";
    for(int x:order) cout<<" "<<x;
    cout<<"\nWEIGHTS:";
    cout<<fixed<<setprecision(6);
    for(double x:w) cout<<" "<<x;
    cout<<"\n";
    return 0;
}
