
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
using namespace std;
typedef long long ll;
ll G;
ll gcdll(ll a,ll b){ if(a<0)a=-a; if(b<0)b=-b; while(b){ll t=a%b;a=b;b=t;} return a==0?1:a; }
struct Frac{ ll p,q; };
Frac norm(ll p,ll q){ if(q<0){p=-p;q=-q;} ll g=gcdll(p,q); return {p/g,q/g}; }
int cmpf(Frac a,Frac b){ __int128 l=(__int128)a.p*b.q, r=(__int128)b.p*a.q; if(l<r)return -1; if(l>r)return 1; return 0; }
vector<int> leaves; string types;
Frac solve(int idx,int level){
    if(level==(int)types.size()) return norm(leaves[idx],1);
    Frac a=solve(idx*2,level+1), b=solve(idx*2+1,level+1);
    char t=types[level];
    if(t=='X') return cmpf(a,b)>=0?a:b;
    if(t=='N') return cmpf(a,b)<=0?a:b;
    return norm(a.p*b.q+b.p*a.q, 2*a.q*b.q);
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int D; cin>>D;
        cin>>types;
        int n=1<<D;
        leaves.assign(n,0);
        for(int i=0;i<n;i++)cin>>leaves[i];
        Frac r=solve(0,0);
        cout<<"EXPECTI "<<r.p<<"/"<<r.q<<"\n";
    }
    return 0;
}
