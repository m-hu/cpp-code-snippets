#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
// Landau-Vishkin k-difference matching: diagonal DP with LCE jumps.
// L[d][e] = furthest pattern row on diagonal e=j-i with d errors.
// Output: count + 0-based text end positions with edit distance <= k.
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    string P,T; int k;
    if(!(cin>>P>>T>>k)) return 0;
    int m=(int)P.size(), n=(int)T.size();
    auto lce=[&](int i,int j){int c=0;while(i<m&&j<n&&P[i]==T[j]){i++;j++;c++;}return c;};
    const int NEG=-1000000000;
    int OFF=m+2, SZ=m+n+5;
    vector<int> prev(SZ,NEG), cur(SZ,NEG);
    vector<char> matched(n,0);
    for(int d=0;d<=k;d++){
        fill(cur.begin(),cur.end(),NEG);
        for(int e=-m;e<=n;e++){
            int r=NEG;
            if(d==0){
                if(e<0||e>n) continue;
                r=0;
            }else{
                int a=prev[e+OFF]+1, b=prev[e-1+OFF], c=prev[e+1+OFF]+1;
                r=max(a,max(b,c));
                if(r<=NEG/2) continue;
            }
            int L=r+lce(r,r+e);
            cur[e+OFF]=L;
            if(L>=m){int end=m+e-1; if(end>=0&&end<n) matched[end]=1;}
        }
        prev.swap(cur);
    }
    vector<int> ans;
    for(int j=0;j<n;j++) if(matched[j]) ans.push_back(j);
    cout<<ans.size()<<"\n";
    if(!ans.empty()){
        for(size_t i=0;i<ans.size();i++){if(i)cout<<" ";cout<<ans[i];}
        cout<<"\n";
    }
    return 0;
}
