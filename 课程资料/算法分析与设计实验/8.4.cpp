#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define endl '\n'

#ifndef ONLINE_JUDGE
#include "debug.h" //https://github.com/Heltion/debug.h/blob/main/debug.h
#else
#define debug(...) 42
#define debug_assert(...) 42
#endif

int dx[]={-1,-1,0,1,1,1,0,-1};
int dy[]={0,-1,-1,-1,0,1,1,1};
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;
    cin>>n>>m;
    vector<string> s(2*n);
    int i,j,k;
    for(i=0;i<n;i++)
    {
        string str;
        cin>>str;
        s[2*i].resize(2*m);
        s[2*i+1].resize(2*m);
        for(j=0;j<m;j++)
        {
            if(str[j]=='\\')
            {
                int x=i*2, y=j*2;
                s[x][y]=s[x+1][y+1]='\\';
                s[x][y+1]=s[x+1][y]=' ';
            }
            else
            {
                int x=i*2, y=j*2;
                s[x][y+1]=s[x+1][y]='/';
                s[x][y]=s[x+1][y+1]=' ';
            }
        }
    }

    int res=0;
    vector<vector<int>> vis(2*n+2, vector<int>(2*m+2));
    auto dfs=[&](auto dfs, int cnt, int x, int y)->void
    {
        if(s[x][y]!= ' ')
            return;
        debug(vector{cnt,x,y});
        vis[x][y]=1;
        res=max(res,cnt);
        for(int i=0;i<8;i++)
        {
            int nx=x+dx[i];
            int ny=y+dy[i];
            auto ok=[&](int nx, int ny)
            {
                if(nx<0 || ny<0 || nx>=2*n || ny>=2*m || vis[nx][ny] || s[nx][ny]!=' ')
                    return 0;
                return 1;
            };
            if(ok(nx,ny))
            {
                if(abs(dx[i])+abs(dy[i])<2)
                    dfs(dfs,cnt+1,nx,ny);
                else
                {
                    if(dx[i]*dy[i]==1)
                    {
                        if(s[x][ny]==s[nx][y] && s[x][ny]=='/')
                            continue;
                        dfs(dfs,cnt+1,nx,ny);
                    }
                    else
                    {
                        if(s[x][ny]==s[nx][y] && s[x][ny]=='\\')
                            continue;
                        dfs(dfs,cnt+1,nx,ny);
                    }
                }
            }
        }
    };
    for(i=0;i<2*n;i++)
        for(j=0;j<2*m;j++)
            if(!vis[i][j])
            {
                debug(pii{i,j});
                dfs(dfs,1,i,j);
            }
    
    cout<<res<<endl;
}  
