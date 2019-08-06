#include <iostream>
#include <queue>
#include <stack>

using namespace std;

/*
5条最短路径（长度为10）
8 13 2 5
20 30 40 10 28 10 30 50
0 1 1
1 3 2
0 3 3
0 2 2
2 3 2
1 4 4
4 5 3
1 5 7
3 5 8
3 6 1
3 7 2
6 7 1
5 7 6
*/

//Dijkstra算法，因为这是单源最短路径问题
//测试点2纠结太久了，主要就是最短路径有多条时候的刷新问题
//最大顶点数
#define MAX_N 501
//无穷大
#define INF 100000000

//用邻接矩阵表示图, 元素值为INF表示两个顶点间没有路，初始化为INF
int weights[MAX_N][MAX_N];
//每个顶点的救援队伍数目，从输入读入每个顶点的救援队数目
int teams[MAX_N];
//顶点S至其它任意顶点的最短路径的权值和，初始化为INF
int dis[MAX_N];
//顶点S至其它任意顶点的最短路径的条数，初始化为0
int shortestPathNums[MAX_N];
//顶点S至其它任意顶点j的最短路径中最多救援队伍数目，初始化为0
int maxAidTeamNums[MAX_N];
//最短路径的父亲节点编号，初始化为-1
int fathers[MAX_N];
//所有顶点访问标记位，初始化为false
bool visits[MAX_N];

int main()
{
    int N, M, S, D, i, j, k, a, b, w, lastID;
    //读入图的顶点数、边数、出发顶点编号、目标顶点编号
    cin>>N>>M>>S>>D;
    //读入每个顶点的救援队数目，存到teams数组里，顺便把weights数组初始化为INF
    for(i=0; i<N; ++i)
    {
        cin>>teams[i];
        for(j=0; j<N; ++j)
            weights[i][j] = INF;
    }
    //读入M条边信息：顶点1、顶点2、距离
    for(i=0; i<M; ++i)
    {
        //顶点1、顶点2、距离
        cin>>a>>b>>w;
        //设置无向图的边长度，即权值
        weights[a][b] = weights[b][a] = w;
    }

    //Dijkstra算法初始化：将dis数组初始化为INF，fathers数组初始化为-1
    for(i=0; i<N; ++i)
    {
        dis[i] = INF;
        fathers[i] = -1;
    }

    //初始化dis[S]为0，即起点到自己的最短距离为0
    dis[S] = 0;
    //这里要初始化shortestPathNums[S]为1，测试点2纠结了很久
    shortestPathNums[S]=1;
    //同时要把maxAidTeamNums[S]设置为teams[S],即起点最多的救援队伍数目
    maxAidTeamNums[S]  = teams[S];

    //开始Dijkstra算法
    for(i=0; i<N; ++i)
    {
        //首先从dis数组中选择一个从未被访问过的顶点到S的最小距离
        int minDis = INF;
        k = -1;
        for(j=0; j<N; ++j)
        {
            if(!visits[j] && dis[j]<minDis)
            {
                minDis = dis[j];
                k = j;
            }
        }
        //防止非连通图的情况
        if(k==-1)
            continue;
        //标记访问标志（或者集合标志，见慕课）
        visits[k] = true;

        //刷新每个顶点最短距离
        for(j=0; j<N; ++j)
        {
            if(weights[k][j]==INF)
                continue;
            //如果<S,j>路径中插入顶点k反而能使路径变短
            if(dis[j]>dis[k]+weights[k][j])
            {
                //更新<S,j>的最短路径
                dis[j] = dis[k]+weights[k][j];
                //刷新<S,j>最短路径的救援队伍数目
                maxAidTeamNums[j] = teams[j]+maxAidTeamNums[k];
                //这里不能将shortestPathNums[j]设置为1，测试点2纠结了很久
                //shortestPathNums[j] = 1;
                //<S,j>最短路径数目应该和<S,k>一样
                shortestPathNums[j] = shortestPathNums[k];
                //更新j的父亲节点编号为k
                fathers[j] = k;
            }
            //如果<S,j>路径中插入顶点k后可以使最短路径等长
            else if(dis[j]==dis[k]+weights[k][j])
            {
                //这个错误纠结了很久，不是加1，而是累加从k而来的所有path数目
                //++shortestPathNums[j];
                //累加从k而来的所有path数目
                shortestPathNums[j]+=shortestPathNums[k];
                //计算加入顶点k后路径的救援队数目
                int maxTeamNums = teams[j]+maxAidTeamNums[k];
                //如果该队伍数目超过了当前<S,j>路径中救援队数目，则更新这条最短路径，插入节点k
                if(maxTeamNums>maxAidTeamNums[j])
                {
                    //更新j的父节点
                    fathers[j] = k;
                    //更新<S,j>的救援队数目
                    maxAidTeamNums[j] = maxTeamNums;
                }
            }
        }
    }

    //打印<S,D>最短路径的条数和最多救援队伍数目
    cout<<shortestPathNums[D]<<" "<<maxAidTeamNums[D]<<endl;

    //利用堆栈追踪出<S,D>的最短路径
    stack<int> ids;
    lastID = D;
    while(lastID!=-1)
    {
        ids.push(lastID);
        lastID = fathers[lastID];
    }
    //用bFirstPrint控制空格输出
    bool bFirstPrint=true;
    while(!ids.empty())
    {
        if(!bFirstPrint)
            cout<<" ";
        cout<<ids.top();
        ids.pop();
        bFirstPrint = false;
    }
    cout<<endl;
    return 0;
}
