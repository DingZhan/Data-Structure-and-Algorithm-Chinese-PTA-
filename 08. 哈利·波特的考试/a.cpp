#include <iostream>
using namespace std;

#define MAX_N 101
//任意两个结点之间的距离矩阵，即无向图
unsigned int mat[MAX_N][MAX_N];
//定义一个无效距离，即一个足够大的距离
#define MAX_LEN 10000000

int main()
{
    int i, j, k, N, M, a, b, len;
    //首先将距离矩阵中每个距离都设置为无效的距离
    for(i=0; i<MAX_N; ++i)
    {
        for(j=0; j<MAX_N; ++j)
            mat[i][j] = MAX_LEN;
    }
    //输入矩阵
    cin>>N>>M;
    for(i=0; i<M; ++i)
    {
        cin>>a>>b>>len;
        mat[a][b] = len;
        //对称矩阵
        mat[b][a] = len;
    }
    //每一轮刷新后，都要检测是否有距离被更新过，如果没有结点间的距离被更新过，
    //则说明不要再刷新矩阵
    bool bUpdated;
    while(true)
    {
        //设置当前没有矩阵元素被更新过
        bUpdated = false;
        //矩阵行号
        for(i=1; i<=N; ++i)
        {
            //矩阵列号
            for(j=1; j<=N; ++j)
            {
                if(j==i)
                    continue;
                for(k=1; k<=N; ++k)
                {
                    //如果mat[i][j]>mat[i][k]+mat[k][j],则更新mat[i][j]距离
                    if(mat[i][j]>mat[i][k]+mat[k][j])
                    {
                        mat[i][j]=mat[i][k]+mat[k][j];
                        //设置矩阵元素被更新过标志
                        bUpdated = true;
                        //同时更新对称元素，if是否不需要加？
                        if(mat[j][i]>mat[i][j])
                            mat[j][i] = mat[i][j];
                    }
                }
            }
        }
        //如果扫描一轮后，没有矩阵元素被更新过，则退出更新循环
        if(!bUpdated)
            break;
    }

    int minmaxID=-1;
    //最大距离的最小值
    int minmax = MAX_LEN;
    for(i=1; i<=N; ++i)
    {
        //计算结点i到任意一个结点的最远距离max
        int max = 0;
        for(j=1; j<=N; ++j)
        {
            if(j==i)
                continue;
            if(mat[i][j]>max)
            {
                max = mat[i][j];
            }
        }
        //如果该最远距离比当前最远距离的最小值还小，则更新最大距离的最小值
        if(max<minmax)
        {
            minmax = max;
            minmaxID = i;
        }
    }
    //如果图非连通
    if(minmaxID==-1)
    {
        cout<<"0"<<endl;
    }
    else
    {
        cout<<minmaxID<<" "<<minmax<<endl;
    }
    return 0;
}
