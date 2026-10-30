
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int N,F,H,E; cin>>N>>F>>H>>E;
        vector<vector<int>> X(N,vector<int>(F));
        vector<int> Y(N);
        for(int i=0;i<N;i++){for(int f=0;f<F;f++)cin>>X[i][f];cin>>Y[i];}
        cout<<"BACKPROP\n";
        // Perceptron
        {
            vector<int> w(F,0); int b=0;
            for(int e=0;e<E;e++)for(int i=0;i<N;i++){
                int y=Y[i]==1?1:-1;
                int act=b;
                for(int f=0;f<F;f++)act+=w[f]*X[i][f];
                if(y*act<=0){ for(int f=0;f<F;f++)w[f]+=y*X[i][f]; b+=y; }
            }
            cout<<"P";
            for(int f=0;f<F;f++)cout<<' '<<w[f];
            cout<<' '<<b;
            for(int i=0;i<N;i++){
                int act=b;
                for(int f=0;f<F;f++)act+=w[f]*X[i][f];
                cout<<' '<<(act>0?1:0);
            }
            cout<<"\n";
        }
        // Logistic regression
        {
            vector<double> w(F,0.0); double b=0.0;
            for(int e=0;e<E;e++)for(int i=0;i<N;i++){
                double z=b;
                for(int f=0;f<F;f++)z+=w[f]*X[i][f];
                double p=1.0/(1.0+exp(-z));
                double err=Y[i]-p;
                for(int f=0;f<F;f++)w[f]+=0.5*err*X[i][f];
                b+=0.5*err;
            }
            cout<<"L";
            char buf[32];
            for(int f=0;f<F;f++){snprintf(buf,sizeof buf,"%.6f",w[f]);cout<<' '<<buf;}
            snprintf(buf,sizeof buf,"%.6f",b);cout<<' '<<buf;
            for(int i=0;i<N;i++){
                double z=b;
                for(int f=0;f<F;f++)z+=w[f]*X[i][f];
                double p=1.0/(1.0+exp(-z));
                cout<<' '<<(p>=0.5?1:0);
            }
            cout<<"\n";
        }
        // MLP backprop
        {
            vector<vector<double>> w1(H,vector<double>(F));
            vector<double> b1(H,0.0),w2(H);
            double b2=0.0;
            for(int h=0;h<H;h++){for(int f=0;f<F;f++)w1[h][f]=0.05*(h+f+1);w2[h]=0.05*(h+1);}
            for(int e=0;e<E;e++)for(int i=0;i<N;i++){
                vector<double> a1(H);
                for(int h=0;h<H;h++){double z=b1[h];for(int f=0;f<F;f++)z+=w1[h][f]*X[i][f];a1[h]=tanh(z);}
                double z2=b2;for(int h=0;h<H;h++)z2+=w2[h]*a1[h];
                double p=1.0/(1.0+exp(-z2));
                double d2=(p-Y[i])*p*(1.0-p);
                for(int h=0;h<H;h++){
                    double d1=d2*w2[h]*(1.0-a1[h]*a1[h]);
                    for(int f=0;f<F;f++)w1[h][f]-=0.1*d1*X[i][f];
                    b1[h]-=0.1*d1;
                }
                for(int h=0;h<H;h++)w2[h]-=0.1*d2*a1[h];
                b2-=0.1*d2;
            }
            cout<<"M";
            double loss=0;
            for(int i=0;i<N;i++){
                vector<double> a1(H);
                for(int h=0;h<H;h++){double z=b1[h];for(int f=0;f<F;f++)z+=w1[h][f]*X[i][f];a1[h]=tanh(z);}
                double z2=b2;for(int h=0;h<H;h++)z2+=w2[h]*a1[h];
                double p=1.0/(1.0+exp(-z2));
                loss+=0.5*(Y[i]-p)*(Y[i]-p);
                cout<<' '<<(p>=0.5?1:0);
            }
            loss/=N;
            char buf[32];snprintf(buf,sizeof buf,"%.6f",loss);
            cout<<' '<<buf<<"\n";
        }
    }
    return 0;
}
