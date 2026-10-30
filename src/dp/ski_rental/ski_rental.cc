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
using namespace std;

int main(){ios::sync_with_stdio(false);cin.tie(nullptr);
long long B,T; if(!(cin>>B>>T)) return 0;
long long off=min(T,B);
long long det=(T<B)?T:(B-1)+B;
long long rnd;
if(T>=B)rnd=B*B+B*(B-1)/2;
else rnd=T*(T-1)/2+T*(2*B-T);
cout<<off<<"\n"<<det<<"\n"<<rnd<<"\n";}
