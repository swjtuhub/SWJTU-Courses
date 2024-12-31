//算法实验4.1
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define endl '\n'
int n,k;
vector<int> a;

void quick_sort(int l, int r)
{
    if(l>=r)
        return;
    int i=l,j=r,t=a[l];
    while(i!=j)
    {
        while(i<j && a[j]<=t)
            j--;
        while(i<j && a[i]>=t)
            i++;
        swap(a[i],a[j]);
    }
    swap(a[i],a[l]);
    quick_sort(l,i-1);
    quick_sort(i+1,r);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>k;
    a.resize(n);
    int i;
    for(i=0;i<n;i++)
        cin>>a[i];
    quick_sort(0,n-1);
    cout<<a[k-1];
}
