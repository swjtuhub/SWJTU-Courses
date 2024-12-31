// 算法实验3.1
#include<bits/stdc++.h>
#define MAXM 10
void Perm(int *,int,int,int,int,int set[MAXM][MAXM],int nlist[MAXM]);
using namespace std;
int qlist[MAXM]; //存放木块长度
int loss; //存放每次切割的损失
int n,len,mn=0; //存放木块的数量，长度，最少需要的木料的数量
int main()
{
    int *list;
    int set[MAXM][MAXM];
    int nlist[MAXM];
    memset(qlist, 0, sizeof(qlist));
    cin >> len;
    cin >> loss;
    n = 0;
    //每组数据输入之后用-1 作为结束，本程序只处理一组数据,如要处理多组数据可
    //做适当修改
    while (cin >> qlist[n] && qlist[n]!=-1)
        n++;
    mn = n;
    list = new int[n];
    for (int i = 0; i < n; i++) {
        list[i] = i;
    }
    memset(set, 0, sizeof(set));
    memset(nlist, 0, sizeof(nlist));
    Perm(list,0,0,n-1,1,set,nlist);
    cout<<mn<<endl;
    return 0;
}

void Perm(int *list, int level,int k, int m,int count,int set[MAXM][MAXM],int nlist[MAXM])
{
    int i;
    int nset[MAXM][MAXM];
    int mlist[MAXM];
    int klist[MAXM];
    if (m == 0) {
        for (int l = k; l <= m; l++) {
            set[count - 1][list[l]] = 1;
        }
        //判断每一行中木块长度总和+每次废掉的木块是否超过一块木料的长度
        int flag = 0;
        for (int l = 0; l < count; l++) {
            int sum = 0;
            for (int h = 0; h < n; h++) {
                if (set[l][h] == 1) {
                    sum +=qlist[h] + loss;
                }
            }
            if (sum > len + loss) {
                flag = 1;
                break;
            }
        }
        //如果所有的都满足，则当前木料的块数是一种选择
        if (flag == 0)
            mn = mn > count ? count : mn;
        return;
    }
    //如果已经取完所有的木块，则返回上一层选取其他选的方法
    if(k>m){
        return;
    }
    else{
        //对于每一块木料都有 k-m 种选取方法，并深度遍历，每次取下一个木块，
        //确保不重复取
        for(i=k;i<=m;i++){
            //获取上一次在该树上选取的木块
            for (int l = 0; l < level; l++)
                klist[l] = nlist[l];
            //继续取下一层的木块
            klist[level] = list[i];
            //获取还剩余的木块
            int left = 0;
            for (int l = 0; l <= m; l++) {
                int s;
                for( s = 0; s <= level; s++){
                    if (list[l] == klist[s])
                        break;
                }
                if (s > level) {
                    mlist[left++] = list[l];
                }
            }
            //设置当前木料所选取的所有木块，nset[l][h]=1 表示第 l 块木料可能锯
            //成第 h 块木块
            for (int l = 0; l < MAXM; l++) {
                for (int h = 0; h < MAXM; h++) {
                    nset[l][h] = set[l][h];
                }
            }
            for (int l =0; l <=level; l++) {
                nset[count-1][klist[l]] = 1;
            }
            //如果所有的木块均已取完，则是一种选择，求出满足条件的木料的数
            //量，并计算最小的木料数
            left--;
            if (left < 0) {
                int flag = 0;
                for (int l = 0; l < count; l++) {
                    int sum = 0;
                    for (int h = 0; h < n; h++) {
                        if (nset[l][h] == 1) {
                            sum += qlist[h]+loss;
                        }
                    }
                    if (sum > len + loss) {
                        flag = 1;
                        break;
                    }
                }
                if(flag==0)
                    mn = mn > count ? count : mn;
            }
            //将剩余木块作为下一个木料的所有选取方法的输入
            Perm(mlist,0,0,left,count+1,nset,klist);
            //取当前木料所对应的下一种木块的取法，每次取下一个木块，确保不
            //重复取
            Perm(list,level+1,i+1, m,count,set,klist);
        }
    }
    return;
}




