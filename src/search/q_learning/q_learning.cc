
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdint>
using namespace std;
struct LCG{ uint64_t s; LCG(uint64_t x):s(x){}
    uint64_t next(){ s=s*6364136223846793005ULL+1442695040888963407ULL; return s; }
    int nextInt(int n){ return (int)(next()%(uint64_t)n); }
    double nextDouble(){ return (double)(next()>>11)*1.1102230246251565E-16; } };
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
        double gn,gd,an,ad,en,ed;
        cin>>gn>>gd>>an>>ad>>en>>ed;
        double g=gn/gd,al=an/ad,eps=en/ed;
        int E,L; long long seed; cin>>E>>L>>seed;
        auto egreedy=[&](LCG& rng, const vector<vector<double>>& Q, int s)->int{
            double u=rng.nextDouble();
            if(u<eps) return rng.nextInt(A);
            int ba=0; double bv=Q[s][0];
            for(int a=1;a<A;a++) if(Q[s][a]>bv){bv=Q[s][a];ba=a;}
            return ba;
        };
        auto step=[&](LCG& rng, int s, int a, int& ns, double& rw){
            double u=rng.nextDouble(),c=0;
            ns=tr[s][a].back().s2; rw=tr[s][a].back().r;
            for(auto &t:tr[s][a]){c+=t.p; if(u<c){ns=t.s2;rw=t.r;break;}}
        };
        // Q-learning
        {
            LCG rng((uint64_t)seed);
            vector<vector<double>> Q(S,vector<double>(A,0.0));
            for(int e=0;e<E;e++){
                int s=0;
                for(int l=0;l<L;l++){
                    int a=egreedy(rng,Q,s);
                    int ns; double rw; step(rng,s,a,ns,rw);
                    double mx=Q[ns][0];
                    for(int b=1;b<A;b++)mx=max(mx,Q[ns][b]);
                    Q[s][a]+=al*(rw+g*mx-Q[s][a]);
                    s=ns;
                }
            }
            cout<<"QLEARN\n";
            for(int s=0;s<S;s++){
                for(int a=0;a<A;a++){if(a)cout<<' ';char b[32];snprintf(b,sizeof b,"%.6f",Q[s][a]);cout<<b;}
                cout<<"\n";
            }
            cout<<"QP";
            for(int s=0;s<S;s++){int ba=0;for(int a=1;a<A;a++)if(Q[s][a]>Q[s][ba])ba=a;cout<<' '<<ba;}
            cout<<"\n";
        }
        // SARSA
        {
            LCG rng((uint64_t)seed);
            vector<vector<double>> Q(S,vector<double>(A,0.0));
            for(int e=0;e<E;e++){
                int s=0, a=egreedy(rng,Q,0);
                for(int l=0;l<L;l++){
                    int ns; double rw; step(rng,s,a,ns,rw);
                    int na=egreedy(rng,Q,ns);
                    Q[s][a]+=al*(rw+g*Q[ns][na]-Q[s][a]);
                    s=ns;a=na;
                }
            }
            cout<<"SARSA\n";
            for(int s=0;s<S;s++){
                for(int a=0;a<A;a++){if(a)cout<<' ';char b[32];snprintf(b,sizeof b,"%.6f",Q[s][a]);cout<<b;}
                cout<<"\n";
            }
            cout<<"SP";
            for(int s=0;s<S;s++){int ba=0;for(int a=1;a<A;a++)if(Q[s][a]>Q[s][ba])ba=a;cout<<' '<<ba;}
            cout<<"\n";
        }
    }
    return 0;
}
