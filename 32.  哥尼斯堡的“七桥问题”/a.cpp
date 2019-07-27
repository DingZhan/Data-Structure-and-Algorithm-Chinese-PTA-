#include <iostream>
#include <queue>
using namespace std;

//注意无向图欧拉回路和欧拉道路的区别
//无向图存在欧拉回路当且仅当所有顶点的degree都为偶数
//无向图存在欧拉道路当且仅当所有顶点的degree都为偶数或者只有两个顶点的degree为奇数

//顶点最大数
#define MAX_N 1001
//邻接表表示图
bool graph[MAX_N][MAX_N];

int main()
{
    int N, M, i, a, b, j, oddNum=0, degree;
    //读入顶点数和边数
    cin>>N>>M;
    for(i=0; i<M; ++i)
    {
        cin>>a>>b;
        //设置无向图的边
        graph[a][b] = true;
        graph[b][a] = true;
    }
    //计算每个顶点的degree：即关联的边数目, 进一步的计算degree为奇数的顶点个数
    for(i=1; i<=N; ++i)
    {
        degree = 0;
        for(j=1; j<=N; ++j)
        {
            if(graph[i][j])
                ++degree;
        }
        if(degree%2)
            ++oddNum;
    }
    //欧拉道路条件
    //if(oddNum!=0 && oddNum!=2)

    //欧拉回路条件，如果有任意顶点的degree为奇数，则不存在欧拉回路
    if(oddNum!=0)
        cout<<0<<endl;
    else
    {
        //检查图的连通性，即计算连通区域个数，如果不为1，则图非连通
        //这里采用BFS搜索
        //顶点访问标记数组
        bool bVisits[MAX_N]={false};
        //BFS使用的队列
        std::queue<int> seeds;
        //图连通区域个数
        int regions = 0, seed;
        //遍历每个顶点
        for(i=1; i<=N; ++i)
        {
            //如果顶点已被访问过
            if(bVisits[i])
                continue;
            //累加新的连通区域
            ++regions;
            //设置顶点访问标记
            bVisits[i] = true;
            //把该顶点加到BFS队列
            seeds.push(i);
            //开始宽度优先搜索
            while(!seeds.empty())
            {
                //弹出种子顶点
                seed = seeds.front();
                seeds.pop();
                //遍历种子顶点的所有邻接顶点，如果没被访问过就加到队列中
                for(j=1; j<=N; ++j)
                {
                    if(graph[seed][j] && !bVisits[j])
                    {
                        seeds.push(j);
                        bVisits[j] = true;
                    }
                }
            }
        }
        //最后，判断连通区域的个数，如果不为1则非连通
        if(regions==1)
            cout<<1<<endl;
        else
            cout<<0<<endl;
    }
    return 0;
}
