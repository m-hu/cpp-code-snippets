#include <iostream>
#include <vector>
using namespace std;
// Ben-Or randomized asynchronous binary consensus (lockstep simulation).
// Per round: stage 1 proposes v on strict majority (>n/2) of correct votes
// else abstains; stage 2 decides v if >=f+1 propose it unopposed, adopts v
// if proposed but short of quorum, else each correct flips a coin (LCG).
typedef unsigned long long u64;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,f,Rmax; if(!(cin>>n>>f>>Rmax)) return 0;
    vector<int> x(n);
    for(int i=0;i<n;i++) cin>>x[i];
    int k;cin>>k;
    vector<int> faulty(n,0);
    for(int j=0;j<k;j++){int t;cin>>t;faulty[t]=1;}
    u64 lcg=777;
    auto flip=[&](){ lcg=lcg*6364136223846793005ULL+1442695040888963407ULL; return (int)((lcg>>33)%2); };
    int nc=0; for(int v:faulty) if(!v) nc++;
    int decision=-1, rounds=0;
    long long flips=0;
    for(int r=1;r<=Rmax;r++){
        rounds=r;
        int o=0,z=0;
        for(int i=0;i<n;i++) if(!faulty[i]){ if(x[i]==1) o++; else z++; }
        int prop=-1;
        if(o>n/2) prop=1; else if(z>n/2) prop=0;
        if(prop>=0){
            if(nc>=f+1){ decision=prop; break; }
            for(int i=0;i<n;i++) if(!faulty[i]) x[i]=prop;
        } else {
            for(int i=0;i<n;i++) if(!faulty[i]){ x[i]=flip(); flips++; }
        }
    }
    cout<<"DECISION: ";
    if(decision>=0) cout<<decision<<"\n"; else cout<<"UNDECIDED\n";
    cout<<"ROUNDS: "<<rounds<<"\n";
    cout<<"COINFLIPS: "<<flips<<"\n";
    return 0;
}
