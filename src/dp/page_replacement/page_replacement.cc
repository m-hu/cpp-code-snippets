#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#include <iomanip>
#include <sstream>
#include <queue>
#include <map>
#include <set>
#include <list>
#include <deque>
#include <numeric>
#include <functional>
using namespace std;

int main(){ios::sync_with_stdio(false);cin.tie(nullptr);
int f,m; if(!(cin>>f>>m)) return 0;
vector<long long>rq(m);for(int i=0;i<m;i++)cin>>rq[i];
long long rng=42;
auto rnd=[&]()->long long{rng=(1103515245*rng+12345)%(1LL<<31);return rng;};
int ff=0;deque<long long>fq;set<long long>fs;
for(auto p:rq){if(f<=0){ff++;continue;}
if(fs.count(p))continue;ff++;
if((int)fq.size()>=f){fs.erase(fq.front());fq.pop_front();}
fq.push_back(p);fs.insert(p);}
int lf=0;list<long long>lru;map<long long,list<long long>::iterator>pos;
for(auto p:rq){if(f<=0){lf++;continue;}
auto it=pos.find(p);
if(it!=pos.end()){lru.erase(it->second);lru.push_back(p);pos[p]=prev(lru.end());continue;}
lf++;
if((int)lru.size()>=f){pos.erase(lru.front());lru.pop_front();}
lru.push_back(p);pos[p]=prev(lru.end());}
int mf=0;set<long long>cache,marked;
for(auto p:rq){if(f<=0){mf++;continue;}
if(cache.count(p)){marked.insert(p);continue;}
mf++;
if((int)cache.size()<f){cache.insert(p);marked.insert(p);continue;}
if(marked.size()>=cache.size())marked.clear();
vector<long long>cands;
for(auto c:cache)if(!marked.count(c))cands.push_back(c);
long long ev=cands[rnd()%(long long)cands.size()];
cache.erase(ev);marked.erase(ev);cache.insert(p);marked.insert(p);}
cout<<ff<<"\n"<<lf<<"\n"<<mf<<"\n";}
