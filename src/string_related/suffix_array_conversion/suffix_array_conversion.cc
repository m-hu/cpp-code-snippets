#include <bits/stdc++.h>
using namespace std;

vector<int> build_sa(const string &s) {
    int n = (int)s.size();
    vector<int> sa(n), rnk(n), tmp(n);
    for (int i = 0; i < n; i++) { sa[i]=i; rnk[i]=(unsigned char)s[i]; }
    for (int k = 1; k < n; k <<= 1) {
        auto cmp = [&](int a, int b){
            if(rnk[a]!=rnk[b]) return rnk[a]<rnk[b];
            int ra=a+k<n?rnk[a+k]:-1, rb=b+k<n?rnk[b+k]:-1;
            return ra<rb;
        };
        sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]]=0;
        for(int i=1;i<n;i++) tmp[sa[i]]=tmp[sa[i-1]]+(cmp(sa[i-1],sa[i])?1:0);
        rnk=tmp;
    }
    return sa;
}
vector<int> build_lcp(const string &s, const vector<int>& sa){
    int n=s.size(); vector<int> rnk(n), lcp(n,0);
    for(int i=0;i<n;i++) rnk[sa[i]]=i;
    for(int i=0,h=0;i<n;i++){
        if(rnk[i]==0) continue;
        int j=sa[rnk[i]-1];
        while(i+h<n && j+h<n && s[i+h]==s[j+h]) h++;
        lcp[rnk[i]]=h;
        if(h) h--;
    }
    return lcp;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string s; if(!(cin>>s)) return 0;
    int n=s.size(); if(n==0){ cout<<"\n\n"; return 0; }
    auto sa=build_sa(s); auto lcp=build_lcp(s,sa);
    for(int i=0;i<n;i++){ if(i) cout<<' '; cout<<sa[i]; } cout<<"\n";
    for(int i=0;i<n;i++){ if(i) cout<<' '; cout<<lcp[i]; } cout<<"\n";
    return 0;
}
