
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int S,A; cin>>S>>A;
        struct Tr{int s2; double p; double r;};
        vector<vector<vector<Tr>>> tr(S,vector<vector<Tr>>(A));
        for(int s=0;s<S;s++)for(int a=0;a<A;a++){
            int nt;cin>>nt;
            for(int i=0;i<nt;i++){int s2;double n,d,r;cin>>s2>>n>>d>>r;tr[s][a].push_back({s2,n/d,r});}
        }
        double gn,gd;cin>>gn>>gd; double g=gn/gd;
        int K;cin>>K;
        vector<double> U(S,0.0),U2(S,0.0);
        for(int k=0;k<K;k++){
            for(int s=0;s<S;s++){
                double best=-1e300;
                for(int a=0;a<A;a++){
                    double v=0;
                    for(auto &t:tr[s][a])v+=t.p*(t.r+g*U[t.s2]);
                    if(v>best)best=v;
                }
                U2[s]=best;
            }
            U=U2;
        }
        vector<int> pol(S,0);
        for(int s=0;s<S;s++){
            double best=-1e300;
            for(int a=0;a<A;a++){
                double v=0;
                for(auto &t:tr[s][a])v+=t.p*(t.r+g*U[t.s2]);
                if(v>best){best=v;pol[s]=a;}
            }
        }
        cout<<"VI\n";
        for(int s=0;s<S;s++){if(s)cout<<' ';char b[32];snprintf(b,sizeof b,"%.6f",U[s]);cout<<b;}
        cout<<"\n";
        for(int s=0;s<S;s++){if(s)cout<<' ';cout<<pol[s];}
        cout<<"\n";
    }
    return 0;
}
