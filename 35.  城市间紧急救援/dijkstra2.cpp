#include <iostream>
#include <queue>
#include <stack>

using namespace std;

/*
4 5 3 0
20 30 40 10
0 1 1
1 3 2
0 3 3
0 2 2
2 3 1
*/
//Dijkstra 算法
#define MAX_N 501
#define INF 100000000
//邻接矩阵表示图, INF表示两个顶点间没有路
int weights[MAX_N][MAX_N];
//每个顶点的救援队伍数目
int teams[MAX_N];
//顶点S至其它任意顶点的最短路径的权值和
int dis[MAX_N];
//顶点S至其它任意顶点的最短路径的条数
int shortestPathNums[MAX_N];
//顶点S至其它任意顶点j的最短路径中最多救援队伍数目
int maxAidTeamNums[MAX_N];
//顶点S至其它任意顶点的最短路径中最多救援队伍数目, 该路径父指针
int fathers[MAX_N];
//所有顶点访问标记位
bool visits[MAX_N];

int GetAidTeams(int fathers[], int d)
{
    int teamSum=0;
    while(d!=-1)
    {
        teamSum+=teams[d];
        d = fathers[d];
    }
    return teamSum;
}
int main()
{
    int N, M, S, D, i, j, k, a, b, w, maxTeams,lastID;
    //读入顶点数和边数
    cin>>N>>M>>S>>D;
    for(i=0; i<N; ++i)
    {
        cin>>teams[i];
        for(j=0; j<N; ++j)
            weights[i][j] = INF;
    }
    for(i=0; i<M; ++i)
    {
        cin>>a>>b>>w;
        //设置无向图的边长度
        weights[a][b] = weights[b][a] = w;
//        maxAidTeamNums[a][b] = teams[a]+teams[b];
//        maxAidTeamNums[b][a] = teams[a]+teams[b];
//        shortestPathNums[a][b] = shortestPathNums[b][a] = 1;
    }

    //Dijkstra 算法
    for(i=0; i<N; ++i)
    {
        dis[i] = INF;
        fathers[i] = -1;
        if(weights[S][i]<INF)
        {
            maxAidTeamNums[i] = teams[S]+teams[i];
            shortestPathNums[i] = 1;
            fathers[i] = S;
        }
    }
    dis[S] = 0;
//    maxAidTeamNums[S]  = teams[S];
    for(i=0; i<N; ++i)
    {
        //choose a minimal dis[k] which is not visited
        int minDis = INF;
        for(j=0; j<N; ++j)
        {
            if(!visits[j] && dis[j]<minDis)
            {
                minDis = dis[j];
                k = j;
            }
        }
        visits[k] = true;

        for(j=0; j<N; ++j)
        {
            if(dis[j]>dis[k]+weights[k][j])
            {
                dis[j] = dis[k]+weights[k][j];
//                maxAidTeamNums[j] = teams[j]+maxAidTeamNums[k];
                shortestPathNums[j] = 1;
                fathers[j] = k;
                maxAidTeamNums[j] = GetAidTeams(fathers, j);
//                maxAidTeamNums[j] = GetAidTeams(fathers, j);
            }
            else if(dis[j]==dis[k]+weights[k][j])
            {
                ++shortestPathNums[j];

                int temp  = fathers[j];
                fathers[j] = k;
                int maxTeamNums = GetAidTeams(fathers, j);
                if(maxTeamNums>maxAidTeamNums[j])
                {
                    fathers[j] = k;
                    maxAidTeamNums[j] = maxTeamNums;
                }
                else
                    fathers[j] = temp;
                /*
                if(maxAidTeamNums[j]<teams[j]+maxAidTeamNums[k])
                {
                    maxAidTeamNums[j] = teams[j]+maxAidTeamNums[k];
                    fathers[j] = k;
                }*/
            }
        }
    }
    cout<<shortestPathNums[D]<<" "<<maxAidTeamNums[D]<<endl;
    stack<int> ids;
    lastID = D;
    while(lastID!=-1)
    {
        ids.push(lastID);
        lastID = fathers[lastID];
    }
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
