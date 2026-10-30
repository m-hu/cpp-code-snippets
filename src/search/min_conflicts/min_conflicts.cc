
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int conflicts_at(const vector<int>& b, int row, int col){
    int n=b.size(), c=0;
    for(int i=0;i<n;i++){
        if(i==row) continue;
        if(b[i]==col) c++;
        else if(abs(b[i]-col)==abs(i-row)) c++;
    }
    return c;
}
int total_pairs(const vector<int>& b){
    int n=b.size(),c=0;
    for(int i=0;i<n;i++) for(int j=i+1;j<n;j++){
        if(b[i]==b[j]) c++;
        else if(abs(b[i]-b[j])==abs(i-j)) c++;
    }
    return c;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int N,MS; cin>>N>>MS;
        vector<int> b(N);
        for(int i=0;i<N;i++) cin>>b[i];
        for(int step=0; step<MS; step++){
            int vr=-1, vc=-1;
            for(int i=0;i<N;i++){
                int c=conflicts_at(b,i,b[i]);
                if(c>0 && c>vc){ vc=c; vr=i; }
            }
            if(vr<0) break;
            int bc=b[vr], bv=conflicts_at(b,vr,bc);
            for(int c=0;c<N;c++){
                int v=conflicts_at(b,vr,c);
                if(v<bv){ bv=v; bc=c; }
            }
            b[vr]=bc;
        }
        for(int i=0;i<N;i++){ if(i)cout<<' '; cout<<b[i]; }
        cout<<"\n"<<total_pairs(b)<<"\n";
    }
    return 0;
}
