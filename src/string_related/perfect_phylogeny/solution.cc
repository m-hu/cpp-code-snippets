#include <iostream>
#include <string>
#include <vector>
using namespace std;
// Directed perfect phylogeny (Gusfield 17.1, root all-0): the binary
// matrix admits one iff the 1-sets of columns form a laminar family
// (each pair nested or disjoint). Violation: rows showing 11, 10, 01.
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,m;if(!(cin>>n>>m))return 0;
    vector<string>rows(n);for(int i=0;i<n;i++)cin>>rows[i];
    for(int j=0;j<m;j++)for(int k=j+1;k<m;k++){
        bool h11=false,h10=false,h01=false;
        for(int i=0;i<n;i++){
            int a=rows[i][j]-'0',b=rows[i][k]-'0';
            if(a==1&&b==1)h11=true;else if(a==1)h10=true;else if(b==1)h01=true;
        }
        if(h11&&h10&&h01){cout<<"NO\n";return 0;}
    }
    cout<<"YES\n";
    return 0;
}
