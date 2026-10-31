#include <iostream>
#include <vector>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    vector<long long> id(n);
    for(int i=0;i<n;i++) cin>>id[i];
    long long mn=id[0];
    for(long long x:id) mn=min(mn,x);
    long long ts_rounds = mn*n + n;
    long long vs_rounds = (long long)n*(mn+1);
    long long vs_msgs = n;
    for(long long x:id){ if(x==mn) continue; long long h = vs_rounds/(x+1); if(h>n) h=n; vs_msgs += h; }
    cout<<"TIME-SLICE ROUNDS: "<<ts_rounds<<" MESSAGES: "<<n<<"\n";
    cout<<"VARIABLE-SPEED ROUNDS: "<<vs_rounds<<" MESSAGES: "<<vs_msgs<<"\n";
    cout<<"LEADER: "<<mn<<"\n";
    return 0;
}
