#include <iostream>
#include <iomanip>

using namespace std;

//Floyd算法，一定要记住中间结点k一定要放在最外层循环
#define MAX_N 10001

//如果结点i,j之间有一条直接的通路，则该元素值为1; 初始时，矩阵全部为0;
//后续扫描时，该矩阵用来存储顶点i,j之间的连通距离
unsigned char mat[MAX_N][MAX_N];

int main()
{
    //设置高速I/O
    std::ios::sync_with_stdio(false);
    int N, M, i, a, b, j, k, v;

    cin>>N>>M;

    //获得邻接矩阵
    for(i=0; i<M; ++i)
    {
        cin>>a>>b;
        mat[a][b] = 1;
        mat[b][a] = 1;
    }

    //Floyd算法，中间结点k一定要放在最外层循环
    for(k=1; k<=N; ++k)
    {
        for(i=1; i<=N; ++i)
        {
            if(i==k)
                continue;
            //如果i->k 或 k->j之间目前还没有路径，则忽略本次循环
            if(mat[i][k]==0)
                continue;
            for(j=1; j<=N; ++j)
            {
                if(i==j||j==k)
                    continue;
                //如果i->k 或 k->j之间目前还没有路径，则忽略本次循环
                if(mat[k][j]==0)
                    continue;
                v = (int)mat[i][k] + mat[k][j];
                //如果这条累加的路径距离和超过了6，则忽略；这样做也是避免溢出
                if(v>6)
                    continue;
                //如果当前i->j之间还没有路径，则用i->k + k->j路径
                if(mat[i][j]==0)
                    mat[i][j] = v;
                else if(mat[i][j]>v) //如果当前路径距离超过i->k + k->j路径,则刷新
                    mat[i][j] = v;
                    /*
                //考虑对称矩阵问题，更新对称元素；貌似这步骤不需要
                if(mat[j][i]==0 && mat[i][j]!=0)
                    mat[j][i] = mat[i][j];
                else if(mat[j][i]>mat[i][j] && mat[i][j]!=0)
                    mat[j][i] = mat[i][j];
                    */
            }
        }
    }


    //一一打印每个节点度小于等于6的百分比
    for(i=1; i<=N; ++i)
    {
        //初始k=1，因为结点i自己也算在有效的邻接顶点内
        k=1;
        for(j=1; j<=N; ++j)
        {
            if(i==j)
                continue;
            //结点j和结点i之间路径的距离<=6,则是一个有效的邻接顶点
            //mat[i][j]==0表示i,j之间没有有效的路
            if(mat[i][j]>0 && mat[i][j]<=6)
                ++k;
        }
        cout<<i<<": "<<std::fixed<<std::setprecision(2)<<k*100.0/N<<"%\n";
    }
}
