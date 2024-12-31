// 算法实验4.3
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define endl '\n'

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,px,py;
    cin>>n>>px>>py;
    vector<vector<int>> a(n+1,vector<int>(n+1));
    int i,j,x,y,t,num=1;
    a[px][py]=-1;
    auto fun=[&](auto fun, int x, int y, int px, int py, int len)
    {
        if(len<=1)
            return;
        len/=2;
        int cnt=num++;
        if(px<x+len && py<y+len)
            fun(fun,x,y,px,py,len);
        else
        {
            a[x+len-1][y+len-1]=cnt;
            fun(fun,x,y,x+len-1,y+len-1,len);
        }

        if(px<x+len && y+len<=py)
            fun(fun,x,y+len,px,py,len);
        else
        {
            a[x+len-1][y+len]=cnt;
            fun(fun,x,y+len,x+len-1,y+len,len);
        }

        if(x+len<=px && py<y+len)
            fun(fun,x+len,y,px,py,len);
        else
        {
            a[x+len][y+len-1]=cnt;
            fun(fun,x+len,y,x+len,y+len-1,len);
        }

        if(x+len<=px && y+len<=py)
            fun(fun,x+len,y+len,px,py,len);
        else
        {
            a[x+len][y+len]=cnt;
            fun(fun,x+len,y+len,x+len,y+len,len);
        }
        
    };
    fun(fun,1,1,px,py,n);
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            cout<<a[i][j]<<' ';
        cout<<endl;
    }
}
