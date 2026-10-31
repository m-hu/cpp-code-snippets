
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
typedef vector<string> Alt;
struct Rule{ string lhs; vector<Alt> alts; };
vector<string> syms_of(const string& s){
    vector<string> r;
    for(size_t i=0;i<s.size();){
        if(s[i]>='A'&&s[i]<='Z'){
            string t; t+=s[i]; i++;
            while(i<s.size()&&s[i]=='\''){t+=s[i];i++;}
            r.push_back(t);
        } else { string t; t+=s[i]; i++; r.push_back(t); }
    }
    return r;
}
string show_alt(const Alt& a){
    if(a.empty())return "@";
    string r;
    for(auto &s:a)r+=s;
    return r;
}
string fresh_for(const string& base, const vector<Rule>& rules){
    string b=base;
    while(true){
        b+="'";
        bool used=false;
        for(auto &rl:rules)if(rl.lhs==b)used=true;
        if(!used)return b;
    }
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int R;cin>>R;
        vector<Rule> rules;
        for(int i=0;i<R;i++){
            string line;cin>>line;
            size_t eq=line.find('=');
            string lhs=line.substr(0,eq);
            vector<Alt> alts;
            size_t st=eq+1;
            while(true){
                size_t bar=line.find('|',st);
                string a=(bar==string::npos)?line.substr(st):line.substr(st,bar-st);
                if(a=="@"||a.empty())alts.push_back({});
                else alts.push_back(syms_of(a));
                if(bar==string::npos)break;
                st=bar+1;
            }
            rules.push_back({lhs,alts});
        }
        int n0=rules.size();
        for(int i=0;i<n0;i++){
            for(int j=0;j<i;j++){
                vector<Alt> na;
                for(auto &a:rules[i].alts){
                    if(!a.empty()&&a[0]==rules[j].lhs){
                        for(auto &b:rules[j].alts){
                            Alt c=b;
                            for(size_t k=1;k<a.size();k++)c.push_back(a[k]);
                            na.push_back(c);
                        }
                    } else na.push_back(a);
                }
                rules[i].alts=na;
            }
            // dedup
            vector<Alt> dd;
            for(auto &a:rules[i].alts){
                bool f=false;
                for(auto &b:dd)if(a==b){f=true;break;}
                if(!f)dd.push_back(a);
            }
            rules[i].alts=dd;
            // immediate elimination
            vector<Alt> rec,nonrec;
            for(auto &a:rules[i].alts){
                if(!a.empty()&&a[0]==rules[i].lhs){
                    Alt c(a.begin()+1,a.end());
                    rec.push_back(c);
                } else nonrec.push_back(a);
            }
            if(!rec.empty()){
                string np=fresh_for(rules[i].lhs,rules);
                vector<Alt> nalts;
                if(nonrec.empty()){ nalts.push_back({np}); }
                else for(auto &b:nonrec){ Alt c=b; c.push_back(np); nalts.push_back(c); }
                rules[i].alts=nalts;
                vector<Alt> palts;
                for(auto &c:rec){ Alt d=c; d.push_back(np); palts.push_back(d); }
                if(!nonrec.empty())palts.push_back({});
                rules.push_back({np,palts});
            }
        }
        // left factoring to fixed point
        for(int round=0;round<20;round++){
            bool any=false;
            for(size_t i=0;i<rules.size()&&!any;i++){
                map<string,vector<int>> groups;
                for(size_t k=0;k<rules[i].alts.size();k++){
                    string key=rules[i].alts[k].empty()?"":rules[i].alts[k][0];
                    groups[key].push_back(k);
                }
                for(auto &gp:groups){
                    if(gp.second.size()<2)continue;
                    vector<Alt> g;
                    for(int k:gp.second)g.push_back(rules[i].alts[k]);
                    size_t pre=0;
                    while(true){
                        bool ok=true;
                        for(size_t k=1;k<g.size();k++){
                            if(pre>=g[k].size()||pre>=g[0].size()||g[k][pre]!=g[0][pre]){ok=false;break;}
                        }
                        if(!ok||pre>=g[0].size())break;
                        pre++;
                    }
                    if(pre==0)continue;
                    string np=fresh_for(rules[i].lhs,rules);
                    Alt prefix(g[0].begin(),g[0].begin()+pre);
                    vector<Alt> keep,suflist;
                    vector<char> in_g(rules[i].alts.size(),0);
                    for(int k:gp.second)in_g[k]=1;
                    Alt first_new=prefix; first_new.push_back(np);
                    bool placed=false;
                    for(size_t k=0;k<rules[i].alts.size();k++){
                        if(in_g[k]){
                            if(!placed){keep.push_back(first_new);placed=true;}
                            Alt suf(rules[i].alts[k].begin()+pre,rules[i].alts[k].end());
                            suflist.push_back(suf);
                        } else keep.push_back(rules[i].alts[k]);
                    }
                    rules[i].alts=keep;
                    rules.push_back({np,suflist});
                    any=true;
                    break;
                }
            }
            if(!any)break;
        }
        cout<<"GRAMMAR "<<rules.size()<<"\n";
        for(auto &rl:rules){
            cout<<rl.lhs<<"=";
            for(size_t k=0;k<rl.alts.size();k++){if(k)cout<<'|';cout<<show_alt(rl.alts[k]);}
            cout<<"\n";
        }
    }
    return 0;
}
