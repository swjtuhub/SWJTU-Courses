// 算法实验2.2
#include<bits/stdc++.h>
#include<random>
using namespace std;
typedef long long ll;
int n;
mt19937 random(time(0));
ofstream ofs("data.txt");
vector<int> a,b,c,arr;

void quick_sort(int l, int r)
{
    if(l>=r)
        return;
    int i=l,j=r;
    int t=a[l];
    while(i-j)
    {
        while(i-j && a[i]>=t)
            i++;
        while(i-j && a[j]<=t)
            j--;
        swap(a[i],a[j]);
    }
    swap(a[i],a[l]);
    quick_sort(l,i-1);
    quick_sort(i+1,r);
}

void merge_sort(int l, int r)
{
    if(l==r)
        return;
    int mid=(l+r)/2;
    merge_sort(l,mid), merge_sort(mid+1,r);
    int i=l,j=mid+1,k=l;
    while(i<=mid && j<=r)
    {
        if(a[i]<a[j])
            b[k++]=a[i++];
        else
            b[k++]=a[j++];
    }
    while(i<=mid)
        b[k++]=a[i++];
    while (j<=r)
        b[k++]=a[j++];
    for(i=l;i<=r;i++)
        a[i]=b[i];
}

void heap_sort()
{
    int cnt=0;
    auto push=[&](int x)    // 压入
    {
        c[++cnt]=x;
        int t=cnt;
        while(t/2 && c[t/2]>c[t])   // 上浮
        {
            swap(c[t],c[t/2]);
            t/=2;
        }
    };

    auto down=[&](auto down, int u)->void     // 下沉
    {
        int lc=u*2,rc=lc+1;
        int v=u;
        if(lc<=cnt && c[v]>c[lc])   v=lc;
        if(rc<=cnt && c[v]>c[rc])   v=rc;
        if(u-v)
        {
            swap(c[u],c[v]);
            down(down,v);
        }
    };

    auto pop=[&]()      // 删除
    {
        a[1]=a[cnt--];
        down(down,1);
    };

    for(int i=0;i<n;i++)
        push(arr[i]);
}

void solve(int m)
{
    n=m;
    a.clear(),b.clear(),c.clear(),arr.clear();
    a.resize(2*n),b.resize(2*n),c.resize(2*n),arr.resize(n);
    int i;
    for(i=0;i<n;i++)
    {
        arr[i]=random();
        a[i]=b[i]=arr[i];
    }

    clock_t s1,s2,s3,e1,e2,e3;
    
    s1=clock();
    quick_sort(0,n);
    e1=clock();

    s2=clock();
    merge_sort(0,n);
    e2=clock();
    
    s3=clock();
    heap_sort();
    e3=clock();
    
    ofs<<setw(7)<<n<<'\t'
      <<setw(7)<<(e1-s1)<<'\t'
      <<setw(7)<<(e2-s2)<<'\t'
      <<setw(7)<<(e3-s3)<<'\n';
}

int main()
{
    if(!ofs.is_open())
    {
        cout<<"Failed to open data.txt\n";
        return 0;
    }
    for(int i=1e3;i<1e5;i+=1e3)
        solve(i);
    for(int i=1e5;i<=1e6;i+=1e5)
        solve(i);
    ofs.close();
}

