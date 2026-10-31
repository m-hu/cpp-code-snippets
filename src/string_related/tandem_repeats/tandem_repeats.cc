#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string s; if(!(cin>>s)) return 0;
    int n=s.size();
    vector<pair<int,int>> reps;
    for(int i=0;i<n;i++){
        for(int len=1; i+2*len<=n; len++){
            bool ok=true;
            for(int k=0;k<len;k++) if(s[i+k]!=s[i+len+k]){ok=false;break;}
            if(ok) reps.emplace_back(i,len);
        }
    }
    // Sort by pos then len (already in order due to loop order)
    cout << reps.size() << "\n";
    for(auto &p: reps) cout << p.first << " " << p.second << "\n";
    return 0;
}
