// 算法实验6.1
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define endl '\n'

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    string str;
    int k,n;
    cin>>str>>k;
    n=str.length();
    int i,j,l,r;
    l=r=i=j=0;
    // 处理0
    int len=0,pos=0;
    while(len<=k && pos<n)
    {
        if(str[pos]!='0')
            pos++,len++;
        else
        {
            k=len;
            len=0;
            l=++pos;
        }
    }
    if(l>=n)
    {
        cout<<"0\n";
        return 0;
    }
    if(k==0)
    {
        cout<<str.substr(size_t(l),n)<<endl;
        return 0;
    }

    str=str.substr(size_t(l),n);
    n=str.length();
    string res;
    multiset<char> s;
    for(i=0;i<=k;i++)
        s.insert(str[i]);
    l=0,r=k;
    while(r<n && k)
    {
        char ch=*s.begin();
        while(ch!=str[l])
        {
            s.erase(s.find(str[l]));
            l++,k;
        }  
        while(l!=r && s.upper_bound(ch)==s.end())
        {
            s.erase(s.begin());
            l++,k;
        }
        res.push_back(ch);
        s.erase(s.begin()); l++;
        if(r+1<n)
            s.insert(str[++r]);
    }
    while(l<n)
        res.push_back(str[l++]);
    cout<<res<<endl;
}
