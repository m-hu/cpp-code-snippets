#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// Minkowski sum of two convex polygons: convex hull (Andrew monotone
// chain) of all pairwise vertex sums. Exact integer arithmetic.
struct Pt{long long x,y;};
long long cross(const Pt&o,const Pt&a,const Pt&b){return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;if(!(cin>>n))return 0;
    vector<Pt>A(n);for(auto&p:A)cin>>p.x>>p.y;
    int m;cin>>m;
    vector<Pt>B(m);for(auto&p:B)cin>>p.x>>p.y;
    vector<Pt>pts;pts.reserve((size_t)n*m);
    for(auto&a:A)for(auto&b:B)pts.push_back({a.x+b.x,a.y+b.y});
    sort(pts.begin(),pts.end(),[](const Pt&a,const Pt&b){return a.x<b.x||(a.x==b.x&&a.y<b.y);});
    pts.erase(unique(pts.begin(),pts.end(),[](const Pt&a,const Pt&b){return a.x==b.x&&a.y==b.y;}),pts.end());
    vector<Pt>lo,hi;
    for(auto&q:pts){while(lo.size()>=2&&cross(lo[lo.size()-2],lo.back(),q)<=0)lo.pop_back();lo.push_back(q);}
    for(auto it=pts.rbegin();it!=pts.rend();++it){while(hi.size()>=2&&cross(hi[hi.size()-2],hi.back(),*it)<=0)hi.pop_back();hi.push_back(*it);}
    lo.pop_back();hi.pop_back();
    vector<Pt>hull=lo;hull.insert(hull.end(),hi.begin(),hi.end());
    cout<<hull.size()<<"\n";
    for(auto&p:hull)cout<<p.x<<" "<<p.y<<"\n";
    return 0;
}
