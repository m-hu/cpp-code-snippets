
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int N,F,R; cin>>N>>F>>R;
        vector<vector<int>> X(N,vector<int>(F));
        vector<int> Y(N);
        for(int i=0;i<N;i++){for(int f=0;f<F;f++)cin>>X[i][f];cin>>Y[i];}
        vector<double> w(N,1.0/N);
        struct Stump{int f,t,pol; double alpha;};
        vector<Stump> ens;
        for(int rd=0;rd<R;rd++){
            int bf=0,bt=0,bpol=0; double be=1e300;
            for(int f=0;f<F;f++){
                vector<int> vals;
                for(int i=0;i<N;i++)vals.push_back(X[i][f]);
                sort(vals.begin(),vals.end());
                vals.erase(unique(vals.begin(),vals.end()),vals.end());
                for(int t:vals)for(int pol=0;pol<2;pol++){
                    double e=0;
                    for(int i=0;i<N;i++){
                        int h=((X[i][f]>=t)==(pol==1))?1:0;
                        if(h!=Y[i])e+=w[i];
                    }
                    if(e<be-1e-12){be=e;bf=f;bt=t;bpol=pol;}
                }
            }
            if(be>=0.5)break;
            double alpha=(be<=0)?10.0:0.5*log((1.0-be)/be);
            double tot=0;
            for(int i=0;i<N;i++){
                int h=((X[i][bf]>=bt)==(bpol==1))?1:-1;
                int y=Y[i]==1?1:-1;
                w[i]*=exp(-alpha*y*h);
                tot+=w[i];
            }
            for(int i=0;i<N;i++)w[i]/=tot;
            ens.push_back({bf,bt,bpol,alpha});
            if(be<=0)break;
        }
        vector<int> P(N);
        int err=0;
        for(int i=0;i<N;i++){
            double s=0;
            for(auto &st:ens){
                int h=((X[i][st.f]>=st.t)==(st.pol==1))?1:-1;
                s+=st.alpha*h;
            }
            P[i]=(s>=0?1:0);
            if(P[i]!=Y[i])err++;
        }
        cout<<"ADA "<<ens.size()<<' '<<err<<"\n";
        for(int i=0;i<N;i++){if(i)cout<<' ';cout<<P[i];}
        cout<<"\n";
    }
    return 0;
}
