// 算法实验2.4
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"
#include<random>
#include<algorithm>
#include<windows.h>
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
#define Max 110

int n1,n2,m,t;
int match[Max][Max],f[Max][Max],g[Max][Max];
int s1[Max],s2[Max];
random_device rd;
mt19937 ran(rd());
uniform_int_distribution<int> dist(1,100);
int random()
{ return dist(ran); }

int main()
{
    ofstream ofs("2.4data.txt");
    if(!ofs.is_open())
    {
        cout<<"failed to open\n";
        return 0;
    }
    cout<<"successfully opend\n";
    LARGE_INTEGER start,end,fre;
    QueryPerformanceFrequency(&fre);
    auto solve=[&](int n1, int n2)
    {
        int i,j;
        int ii,jj;
        QueryPerformanceCounter(&start);
        for(i=1;i<=n1;i++)
            s1[i]=random();
        for(i=1;i<=n2;i++)
            s2[i]=random();
        memset(f,0,sizeof(f));
        memset(g,0,sizeof(g));
        for(i=1;i<=n1;i++){
            for(j=1;j<=n2;j++){
                if(s1[i]==s2[j-1])
                    f[i][j]=j-1;
                else
                    f[i][j]=f[i][j-1];
            }
        }
        for(i=1;i<=n2;i++){
            for(j=1;j<=n1;j++){
                if(s2[i]==s1[j-1])
                    g[i][j]=j-1;
                else
                    g[i][j]=g[i][j-1];
            }
        }
        memset(match,0,sizeof(match));
        for(i=1;i<=n1;i++){
            for(j=1;j<=n2;j++){
                match[i][j]=max(match[i-1][j],match[i][j-1]);
                if(s1[i]==s2[j]) continue;
                ii=f[i][j];jj=g[j][i];
                if(ii==0||jj==0) continue;
                match[i][j]=max(match[i][j],match[jj-1][ii-1]+2);
            }
        }
        QueryPerformanceCounter(&end);
        double tt=double(end.QuadPart-start.QuadPart)*double(1e6) / double(fre.QuadPart);  // us
        ofs<<setw(6)<<n1
           <<setw(6)<<n2<<'\t'
           <<fixed<<setprecision(6)<<tt<<'\n';
        // printf("%d\n",match[n1][n2]);
    
    };
    // solve(100,100);
    for(int i=10;i<=110;i+=10)
        for(int j=10;j<=110;j+=10)
            solve(i,j);
    ofs.close();
    return 0;
}
