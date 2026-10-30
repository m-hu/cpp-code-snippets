#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
// Sample uniqueness & sequential bootstrap (AFML ch.4): label i over bars
// [t0,t1] has uniqueness u_i = mean over t of 1/c_t (c_t = concurrency);
// sequential bootstrap draws K labels with prob proportional to u (LCG),
// then debits overlapping labels' uniqueness (clamped at 0).
typedef unsigned long long u64;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int L,K; if(!(cin>>L>>K)) return 0;
    vector<int> t0(L),t1(L);
    int Tmax=0;
    for(int i=0;i<L;i++){cin>>t0[i]>>t1[i];Tmax=max(Tmax,t1[i]);}
    vector<int> c(Tmax+1,0);
    for(int i=0;i<L;i++) for(int t=t0[i];t<=t1[i];t++) c[t]++;
    vector<double> u(L,0);
    for(int i=0;i<L;i++){double s=0;for(int t=t0[i];t<=t1[i];t++) s+=1.0/c[t];u[i]=s/(t1[i]-t0[i]+1);}
    cout<<fixed<<setprecision(6)<<"UNIQ:";
    for(double x:u) cout<<" "<<x;
    cout<<"\n";
    u64 lcg=999;
    vector<int> draws;
    vector<double> uu=u;
    for(int d=0;d<K;d++){
        double tot=0; for(double x:uu) tot+=x;
        int pick=0;
        if(tot<=0){ lcg=lcg*6364136223846793005ULL+1442695040888963407ULL; pick=(int)(((lcg>>11)+1)% (u64)L); }
        else{
            lcg=lcg*6364136223846793005ULL+1442695040888963407ULL;
            double r=((double)((lcg>>11)+1)/9007199254740992.0)*tot;
            double acc=0; pick=L-1;
            for(int i=0;i<L;i++){acc+=uu[i]; if(acc>r){pick=i;break;}}
        }
        draws.push_back(pick);
        for(int t=t0[pick];t<=t1[pick];t++)
            for(int j=0;j<L;j++)
                if(t0[j]<=t&&t<=t1[j]){ uu[j]-=(1.0/c[t])/(t1[j]-t0[j]+1); if(uu[j]<0) uu[j]=0; }
    }
    cout<<"BOOT:";
    for(int x:draws) cout<<" "<<x;
    cout<<"\n";
    return 0;
}
