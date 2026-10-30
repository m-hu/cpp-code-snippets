#include <iostream>
#include <vector>
using namespace std;
// Peterson's async unidirectional ring election (Lynch 15.1.3):
// active nodes carry alias `cur`; per phase each learns the two nearest
// active counter-clockwise aliases (uid2, uid3); sole survivor declares.
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    vector<long long> id(n);
    for(int i=0;i<n;i++) cin>>id[i];
    vector<long long> cur=id;
    vector<int> active(n,1);
    long long leader=-1, alias=-1;
    int phases=0, cap=4*n+10;
    while(phases<cap){
        vector<int> a;
        for(int i=0;i<n;i++) if(active[i]) a.push_back(i);
        int k=a.size();
        if(k==0) break;
        phases++;
        if(k==1){ leader=id[a[0]]; alias=cur[a[0]]; break; }
        vector<long long> ncur=cur;
        vector<int> nact=active;
        bool done=false;
        for(int j=0;j<k;j++){
            int q=a[j];
            long long uid2=cur[a[(j-1+k)%k]];
            long long uid3=cur[a[(j-2+k)%k]];
            if(uid2==cur[q]){ leader=id[q]; alias=cur[q]; done=true; break; }
            else if(uid2>cur[q] && uid2>uid3){ ncur[q]=uid2; }
            else { nact[q]=0; }
        }
        cur=ncur; active=nact;
        if(done) break;
    }
    cout<<"LEADER: "<<leader<<"\n";
    cout<<"ALIAS: "<<alias<<"\n";
    cout<<"PHASES: "<<phases<<"\n";
    cout<<"MESSAGES: "<<2LL*n*phases<<"\n";
    return 0;
}
