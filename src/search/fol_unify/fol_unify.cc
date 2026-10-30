
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>
using namespace std;
struct Term{ string sym; vector<Term> args; bool isvar; };
Term parse_term(const string& s, size_t& p){
    size_t q=p;
    while(q<s.size()&&(isalnum(s[q])!=0)) q++;
    string sym=s.substr(p,q-p); p=q;
    if(p<s.size()&&s[p]=='('){
        p++;
        Term t; t.sym=sym; t.isvar=false;
        while(true){
            t.args.push_back(parse_term(s,p));
            if(s[p]==','){p++;continue;}
            p++; break;
        }
        return t;
    }
    Term t; t.sym=sym; t.isvar=(islower(sym[0])!=0);
    return t;
}
string show(const Term& t){
    if(t.args.empty()) return t.sym;
    string r=t.sym+"(";
    for(size_t i=0;i<t.args.size();i++){ if(i)r+=","; r+=show(t.args[i]); }
    return r+")";
}
Term subst(const Term& t, map<string,Term>& th){
    if(t.isvar){
        auto it=th.find(t.sym);
        if(it==th.end()) return t;
        Term r=subst(it->second,th);
        th[t.sym]=r;
        return r;
    }
    Term r=t; r.args.clear();
    for(auto &a:t.args) r.args.push_back(subst(a,th));
    return r;
}
bool occurs(const string& v, const Term& t, map<string,Term>& th){
    Term s=subst(t,th);
    if(s.isvar) return s.sym==v;
    for(auto &a:s.args) if(occurs(v,a,th)) return true;
    return false;
}
bool unify(Term a, Term b, map<string,Term>& th){
    a=subst(a,th); b=subst(b,th);
    if(a.isvar&&b.isvar&&a.sym==b.sym) return true;
    if(a.isvar){
        if(occurs(a.sym,b,th)) return false;
        th[a.sym]=b; return true;
    }
    if(b.isvar){
        if(occurs(b.sym,a,th)) return false;
        th[b.sym]=a; return true;
    }
    if(a.sym!=b.sym||a.args.size()!=b.args.size()) return false;
    for(size_t i=0;i<a.args.size();i++) if(!unify(a.args[i],b.args[i],th)) return false;
    return true;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        string s1,s2; cin>>s1>>s2;
        size_t p1=0,p2=0;
        Term t1=parse_term(s1,p1), t2=parse_term(s2,p2);
        map<string,Term> th;
        bool ok=unify(t1,t2,th);
        if(!ok){cout<<"UNIFY FAIL\n";continue;}
        cout<<"UNIFY";
        for(auto &kv:th){
            Term r=subst(kv.second,th);
            cout<<' '<<kv.first<<'='<<show(r);
        }
        cout<<"\n";
    }
    return 0;
}
