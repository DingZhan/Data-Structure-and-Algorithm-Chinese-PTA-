#include <iostream>
#include <iomanip>

using namespace std;

//本方法最后一个测试点用了2184 ms，因此也比较低效

#define MAX_N 10001

//如果结点i,j之间有一条直接的通路，则该元素值为1; 初始时，矩阵全部为0;
//后续扫描时，该矩阵用来存储顶点i,j之间的连通距离
unsigned char mat[MAX_N][MAX_N];

//打印矩阵，调试用
void PrintMap(int N)
{
    int i, j;
    for(i=1; i<=N; ++i)
    {
        for(j=1; j<=N; ++j)
        {
            cout<<setw(5)<<(int)mat[i][j];
        }
        cout<<"\n";
    }
    cout<<"\n\n";
}

int main()
{
    //设置高速I/O
    std::ios::sync_with_stdio(false);
    int N, M, i, a, b, j, k, t, v;
    bool bUpdated=false;

    cin>>N>>M;
    //获得邻接矩阵
    for(i=0; i<M; ++i)
    {
        cin>>a>>b;
        mat[a][b] = 1;
        mat[b][a] = 1;
    }
   // PrintMap(N);

    //最多更新几次邻接距离矩阵，这里设置为6，也是最大更新次数
    for(t=0; t<6; ++t)
    {
        //设置矩阵更新标志位
        bUpdated = false;
        for(i=1; i<=N; ++i)
        {
            for(j=1; j<=N; ++j)
            {
                if(i==j)
                    continue;
                //如果当前结点i,j 之间已经有一条距离<=6的有效路径，则不要再计算
                if(mat[i][j]>0&&mat[i][j]<=6)
                    continue;
                for(k=1; k<=N; ++k)
                {
                    //k不能和i,j相同
                    if(k==j||k==i)
                        continue;
                    //如果i->k 或 k->j之间目前还没有路径，则忽略本次循环
                    if(mat[i][k]==0 || mat[k][j]==0)
                        continue;
                    //计算i->k + k->j的路径距离和，因为mat中元素是char类型，
                    //所以用(int)防止可能的溢出
                    v = (int)mat[i][k] + mat[k][j];
                    //如果这条累加的路径距离和超过了6，则忽略；这样做也是避免溢出
                    if(v>6)
                        continue;
                    //如果当前i->j之间还没有路径，则用i->k + k->j路径
                    if(mat[i][j]==0)
                    {
                        mat[i][j] = v;
                        //设置矩阵更新标志
                        bUpdated = true;
                    }
                    else if(mat[i][j]>v) //如果当前路径距离超过i->k + k->j路径,则刷新
                    {
                        mat[i][j] = v;
                        //设置矩阵更新标志
                        bUpdated = true;
                    }
                    //考虑对称矩阵问题，更新对称元素；貌似这步骤不需要
                    if(mat[j][i]==0 && mat[i][j]!=0)
                        mat[j][i] = mat[i][j];
                    else if(mat[j][i]>mat[i][j] && mat[i][j]!=0)
                        mat[j][i] = mat[i][j];
                }
            }

        }
        //如果本轮扫描过程中没有一个节点的度得到更新，说明不需要再进行下一轮扫描
        //如果没有这个循环控制条件，会有超时问题
        if(!bUpdated)
            break;
        /*
        PrintMap(N);
        if(bUpdated)
            cout<<"Updated!";
        else
            cout<<"No Updated!";
            */
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
