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
    //Floyd算法，k一定要放在最外层
    for(k=1; k<=N; ++k)
    {
        //矩阵行号
        for(i=1; i<=N; ++i)
        {
            //矩阵列号
            for(j=1; j<=N; ++j)
            {
                if(j==i)
                    continue;
                //如果mat[i][j]>mat[i][k]+mat[k][j],则更新mat[i][j]距离
                if(mat[i][j]>mat[i][k]+mat[k][j])
                {
                    mat[i][j]=mat[i][k]+mat[k][j];
                    /*
                    //同时更新对称元素，if是否不需要加？
                    if(mat[j][i]>mat[i][j])
                        mat[j][i] = mat[i][j];
                    */
                }
            }
        }
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
