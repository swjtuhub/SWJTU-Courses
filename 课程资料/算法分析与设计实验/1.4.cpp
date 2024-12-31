// 算法实验1.4
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<int> res;

bool topo(int n, vector<vector<int>> &a, vector<int> &in)
{
    int u;
    queue<int> q;
    for(int i = 1; i <= n; i++)
        if(in[i]==0)
            q.push(i);
    while(!q.empty())
    {
        u = q.front();
        q.pop();
        res.push_back(u);
        for(auto x: a[u])
            if(--in[x]==0)
                q.push(x);
    }
    return (res.size()==n);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;
    cin >> n>>m;
    vector<vector<int>> a(n+1);
    vector<int> in(n+1,0);
    int i,j,u,v;
    for(i = 0; i < m; i++)
    {
        cin >> u >> v;
        a[u].push_back(v);
        in[v]++;
    }
    if(topo(n,a,in))
    {
        for(auto x: res)
            cout << x << ' ';
        cout << '\n';
    }
    else
    {
        cout << "-1\n";
    }
}
