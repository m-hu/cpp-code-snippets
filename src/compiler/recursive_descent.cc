
#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;
string s; size_t p; bool err;
void skip(){}
ll parseE();
ll parseF(){
    if(err||p>=s.size()){err=true;return 0;}
    if(s[p]=='('){p++;ll v=parseE();if(err||p>=s.size()||s[p]!=')'){err=true;return 0;}p++;return v;}
    if(s[p]=='-'){p++;return -parseF();}
    if(s[p]<'0'||s[p]>'9'){err=true;return 0;}
    ll v=0;
    while(p<s.size()&&s[p]>='0'&&s[p]<='9'){v=v*10+(s[p]-'0');p++;}
    return v;
}
ll parseT(){
    ll v=parseF();
    while(!err&&p<s.size()&&(s[p]=='*'||s[p]=='/')){
        char op=s[p];p++;
        ll r=parseF();
        if(err)return 0;
        if(op=='*')v=v*r;
        else{if(r==0){err=true;return 0;}v=v/r;}
    }
    return v;
}
ll parseE(){
    ll v=parseT();
    while(!err&&p<s.size()&&(s[p]=='+'||s[p]=='-')){
        char op=s[p];p++;
        ll r=parseT();
        if(err)return 0;
        if(op=='+')v=v+r;else v=v-r;
    }
    return v;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        cin>>s;p=0;err=false;
        ll v=parseE();
        if(err||p!=s.size())cout<<"RD ERROR\n";
        else cout<<"RD "<<v<<"\n";
    }
    return 0;
}
