#include <iostream>
#include <vector>
using namespace std;
// Lehmann-Rabin RightLeftDP: per round, thinking philosophers get hungry
// (p=0.6, fixed-seed LCG); hungry ones draw left/right-first and grab the
// first fork if free; holders take the second if free (else release first
// and retry next round); eating holds both forks one full round.
// Deadlock-free (no hold-and-wait across rounds). Reports eats/waits.
typedef unsigned long long u64;
static u64 lcg_state;
static u64 lcg_next(){ lcg_state = lcg_state*6364136223846793005ULL + 1442695040888963407ULL; return lcg_state; }
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; long long R;
    if(!(cin>>n>>R)) return 0;
    lcg_state = 12345;
    vector<int> fork(n,0); // 0 free else holder+1
    vector<int> hungry(n,0), held(n,-1), eatst(n,0);
    vector<long long> eats(n,0), waits(n,0);
    for(long long r=0;r<R;r++){
        for(int i=0;i<n;i++)
            if(!hungry[i]&&!eatst[i]&&(lcg_next()>>16)%100<60){ hungry[i]=1; held[i]=-1; }
        for(int i=0;i<n;i++){
            if(!hungry[i]||held[i]!=-1) continue;
            int f1=(((lcg_next()>>33)%2==0)?i:(i+1)%n);
            if(fork[f1]==0){ fork[f1]=i+1; held[i]=f1; }
        }
        for(int i=0;i<n;i++){
            if(!hungry[i]||held[i]==-1||eatst[i]) continue;
            int lf=i, rt=(i+1)%n;
            int f2=(held[i]==lf?rt:lf);
            if(fork[f2]==0){ fork[f2]=i+1; eatst[i]=1; }
            else { fork[held[i]]=0; held[i]=-1; }
        }
        for(int i=0;i<n;i++){
            if(eatst[i]==2){ fork[i]=0; fork[(i+1)%n]=0; eatst[i]=0; hungry[i]=0; eats[i]++; }
            else if(eatst[i]==1){ eatst[i]=2; }
            else if(hungry[i]){ waits[i]++; }
        }
    }
    long long tot=0; for(long long x:eats) tot+=x;
    int stuck=0; for(int x:fork) if(x!=0) stuck++;
    for(int i=0;i<n;i++) cout<<"P"<<i<<": eats="<<eats[i]<<" waits="<<waits[i]<<"\n";
    cout<<"TOTALEATS: "<<tot<<"\n";
    cout<<"STUCK: "<<stuck<<"\n";
    return 0;
}
