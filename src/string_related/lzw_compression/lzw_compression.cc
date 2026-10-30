#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    string s; if(!(cin>>s)) return 0;
    map<string,int> d;
    for(int i=0;i<256;i++) d[string(1,char(i))]=i;
    int nxt=256;
    string w;
    vector<int> codes;
    for(char c: s){
        string wc=w+c;
        auto it=d.find(wc);
        if(it!=d.end()) w=wc;
        else { codes.push_back(d[w]); d[wc]=nxt++; w=string(1,c); }
    }
    if(!w.empty()) codes.push_back(d[w]);
    for(size_t i=0;i<codes.size();i++){ if(i) cout<<" "; cout<<codes[i]; }
    if(!codes.empty()) cout<<"\n";
    return 0;
}
