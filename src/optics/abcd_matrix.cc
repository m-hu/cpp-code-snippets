#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;
struct Mat{ double a,b,c,d; };
Mat mul(const Mat& X, const Mat& Y){
    return {X.a*Y.a+X.b*Y.c, X.a*Y.b+X.b*Y.d, X.c*Y.a+X.d*Y.c, X.c*Y.b+X.d*Y.d};
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m;
    if(!(cin>>m)) return 0;
    Mat sys{1,0,0,1};
    for(int i=0;i<m;i++){
        string kind;cin>>kind;
        Mat e{1,0,0,1};
        if(kind=="free"){
            double dist;cin>>dist;
            e={1,dist,0,1};
        } else if(kind=="lens"){
            double f;cin>>f;
            e={1,0,-1.0/f,1};
        } else if(kind=="mirror"){
            double f;cin>>f;
            e={1,0,-1.0/f,1};
        } else if(kind=="refract"){
            double n1,n2,R;
            cin>>n1>>n2>>R;
            // refraction at spherical surface: [[1,0],[(n1-n2)/(n2*R), n1/n2]]
            e={1,0,(n1-n2)/(n2*R), n1/n2};
        }
        sys=mul(e,sys);
    }
    double y0,theta0;
    cin>>y0>>theta0;
    double y1=sys.a*y0+sys.b*theta0;
    double th1=sys.c*y0+sys.d*theta0;
    cout<<fixed<<setprecision(6)<<sys.a<<" "<<sys.b<<" "<<sys.c<<" "<<sys.d<<"\n";
    cout<<fixed<<setprecision(6)<<y1<<" "<<th1<<"\n";
    return 0;
}
