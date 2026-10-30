#include <iostream>
#include <vector>
using namespace std;
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    long long n; if(!(cin>>n)) return 0;
    if(n<2){ cout<<"0\n\n"; return 0; }
    vector<bool> is_prime(n+1,true);
    is_prime[0]=is_prime[1]=false;
    for(long long i=2;i*i<=n;i++) if(is_prime[i]) for(long long j=i*i;j<=n;j+=i) is_prime[j]=false;
    int cnt=0; for(long long i=2;i<=n;i++) if(is_prime[i]) cnt++;
    cout<<cnt<<"\n";
    bool first=true;
    for(long long i=2;i<=n;i++) if(is_prime[i]){ if(!first) cout<<" "; cout<<i; first=false; }
    cout<<"\n";
    return 0;
}
