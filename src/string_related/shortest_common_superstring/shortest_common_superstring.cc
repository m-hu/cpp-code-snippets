#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;
int overlap(const string& a,const string& b){
    for(int k=min(a.size(),b.size());k>=1;k--) if(a.substr(a.size()-k)==b.substr(0,k)) return k;
    return 0;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    vector<string> strs(n);
    for(int i=0;i<n;i++) cin>>strs[i];
    // Remove strings that are substrings of others
    // Greedy: repeatedly merge max overlap pair
    while(strs.size()>1){
        int best_i=-1,best_j=-1,best_ov=-1;
        string best_merged;
        for(size_t i=0;i<strs.size();i++) for(size_t j=0;j<strs.size();j++){
            if(i==j) continue;
            int ov=overlap(strs[i],strs[j]);
            if(ov>best_ov){best_ov=ov;best_i=(int)i;best_j=(int)j;best_merged=strs[i]+strs[j].substr(ov);}
        }
        vector<string> next;
        for(size_t k=0;k<strs.size();k++) if((int)k!=best_i&&(int)k!=best_j) next.push_back(strs[k]);
        next.push_back(best_merged);
        strs=next;
    }
    cout<<strs[0]<<"\n";
    return 0;
}
