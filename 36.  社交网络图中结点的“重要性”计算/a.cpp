#include <iostream>
#include <iomanip>

using namespace std;

//用Floyd算法计算整张图中任意两点的最短路径
#define INF 100000000
//顶点最大数
#define MAX_N 10001
//用邻接距离矩阵表示图，如果两个顶点<i,j>之间没有通路，则diss[i][j]=INF
int diss[MAX_N][MAX_N];
int main()
{
    int N, M, K, i, j, k, a, b;
    double v;
    //读入顶点数和边数
    cin>>N>>M;
    //初始化设置邻接距离矩阵中任意两点都不连通
    for(i=1; i<=N; ++i)
    {
        for(j=1; j<=N; ++j)
            diss[i][j] = INF; //初始化非连通
    }
    //读入M条边
    for(i=0; i<M; ++i)
    {
        cin>>a>>b;
        //设置邻接距离矩阵a，b间距离为1
        diss[a][b] = diss[b][a] = 1;
    }
    //采用Floyd算法，计算任意两点间的最短距离
    //Floyd算法中k一定要放在最外层
    for(k=1; k<=N; ++k)
    {
        for(i=1; i<=N; ++i)
        {
            if(i==k)
                continue;
            for(j=1; j<=N; ++j)
            {
                if(j==i || j==k)
                    continue;
                //如果<i,j>间距离小于<i,k>+<k,j>，则更新<i,j>间距离
                if(diss[i][j]>diss[i][k]+diss[k][j])
                    diss[i][j]=diss[i][k]+diss[k][j];
            }
        }
    }
    //读入查询的顶点数目
    cin>>K;
    //读入K个顶点
    for(i=0; i<K; ++i)
    {
        //需要计算的顶点编号k
        cin>>k;
        //累加顶点k到其它所有顶点间的距离
        v = 0.0;
        for(j=1; j<=N; ++j)
        {
            //不要累加自己
            if(k==j)
                continue;
            //如果<k,j>间非连通，则该值设置为0.0，退出累加计算
            if(diss[k][j]==INF)
            {
                v = 0.0;
                break;
            }
            //累加距离
            v+=diss[k][j];
        }
        //根据公式计算该权值
        if(v!=0.0)
            v = (N-1)/v;
        cout<<"Cc("<<k<<")="<<std::fixed<<setprecision(2)<<v<<endl;
    }
}
