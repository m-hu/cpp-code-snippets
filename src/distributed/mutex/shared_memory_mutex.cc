#include <iostream>
#include <vector>
#include <string>
using namespace std;
// Shared-memory mutual exclusion: peterson2 (2-process), filter (n-process),
// bakery (Lamport), dijkstra (K-state, b/c/k), burns (priority backoff).
// Round-robin step simulation: each scheduled step executes one protocol
// line; regions R(0)/T(1)/C(2)/E(3). Reports entries + max concurrency.
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string algo; int n; long long T;
    if(!(cin>>algo>>n>>T)) return 0;
    vector<int> region(n,0), pc(n,0), aux(n,0);
    vector<long long> entries(n,0);
    vector<int> flag(n,0), level(n,0), choosing(n,0), b(n,1), c(n,1);
    vector<long long> number(n,0);
    vector<int> victim(n,0);
    int turn=0, k=0;
    auto step=[&](int i){
        int j=(i+1)%n;
        if(region[i]==0){ region[i]=1; pc[i]=0; aux[i]=0; return; }
        if(region[i]==2){ region[i]=3; pc[i]=0; return; }
        if(region[i]==3){
            if(algo=="peterson2"){ flag[i]=0; region[i]=0; }
            else if(algo=="filter"){ level[i]=0; region[i]=0; }
            else if(algo=="bakery"){ number[i]=0; region[i]=0; }
            else if(algo=="dijkstra"){ if(pc[i]==0){c[i]=1;pc[i]=1;} else {b[i]=1;region[i]=0;} }
            else if(algo=="burns"){ flag[i]=0; region[i]=0; }
            return;
        }
        // trying region
        if(algo=="peterson2"){
            if(pc[i]==0){ flag[i]=1; pc[i]=1; }
            else if(pc[i]==1){ turn=j; pc[i]=2; }
            else { if(flag[j]==1&&turn==j){} else {region[i]=2;entries[i]++;} }
        } else if(algo=="filter"){
            int L=pc[i]/3, sub=pc[i]%3;
            if(sub==0){ level[i]=L+1; pc[i]++; }
            else if(sub==1){ victim[L+1]=i; pc[i]++; }
            else{
                bool blocked=false;
                for(int t=0;t<n;t++) if(t!=i&&level[t]>=L+1) blocked=true;
                if(blocked&&victim[L+1]==i){}
                else if(L+1==n-1){region[i]=2;entries[i]++;}
                else pc[i]++;
            }
        } else if(algo=="bakery"){
            if(pc[i]==0){ choosing[i]=1; pc[i]=1; }
            else if(pc[i]==1){ long long mx=0; for(long long x:number) mx=max(mx,x); number[i]=mx+1; pc[i]=2; }
            else if(pc[i]==2){ choosing[i]=0; pc[i]=3; aux[i]=0; }
            else{
                int t=aux[i];
                if(t==i){ aux[i]++; }
                else if(t>=n){ region[i]=2; entries[i]++; }
                else if(choosing[t]==1){}
                else if(number[t]!=0&&(number[t]<number[i]||(number[t]==number[i]&&t<i))){}
                else aux[i]++;
            }
        } else if(algo=="dijkstra"){
            if(pc[i]==0){ b[i]=0; pc[i]=1; }
            else if(pc[i]==1){ pc[i]=(k!=i?2:4); }
            else if(pc[i]==2){ c[i]=1; pc[i]=3; }
            else if(pc[i]==3){ if(b[k]==1) k=i; pc[i]=1; }
            else if(pc[i]==4){ c[i]=0; pc[i]=5; }
            else{
                bool fail=false;
                for(int t=0;t<n;t++) if(t!=i&&c[t]==0) fail=true;
                if(fail) pc[i]=1; else {region[i]=2;entries[i]++;}
            }
        } else if(algo=="burns"){
            if(pc[i]==0){ flag[i]=0; pc[i]=1; }
            else if(pc[i]==1){ flag[i]=1; pc[i]=2; aux[i]=0; }
            else if(pc[i]==2){
                int t=aux[i];
                if(t>=i){ aux[i]=i+1; pc[i]=3; }
                else if(flag[t]==1){ pc[i]=4; }
                else aux[i]++;
            } else if(pc[i]==4){ flag[i]=0; pc[i]=5; }
            else if(pc[i]==5){ if(flag[aux[i]]==1){} else {pc[i]=1;aux[i]=0;} }
            else{
                int t=aux[i];
                if(t>=n){ region[i]=2; entries[i]++; }
                else if(flag[t]==1){}
                else aux[i]++;
            }
        }
    };
    long long maxconc=0;
    for(long long s=0;s<T;s++){
        int i=(int)(s%n);
        step(i);
        long long cc=0;
        for(int x:region) if(x==2) cc++;
        maxconc=max(maxconc,cc);
    }
    for(int i=0;i<n;i++) cout<<"P"<<i<<": entries="<<entries[i]<<"\n";
    cout<<"MAXCONCURRENT: "<<maxconc<<"\n";
    cout<<"STEPS: "<<T<<"\n";
    return 0;
}
