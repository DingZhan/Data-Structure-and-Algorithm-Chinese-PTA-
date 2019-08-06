#include <iostream>
#include <queue>

using namespace std;

//Floyd 算法
#define MAX_N 501
#define INF 10000000
//邻接矩阵表示图
int graph[MAX_N][MAX_N];
//顶点i至顶点j的最短路径的条数
int shortestPathNums[MAX_N][MAX_N];
int maxTeamsInShortestPath[MAX_N][MAX_N];
vector<int> pathes[MAX_N][MAX_N];

int main()
{
    int N, M, S, D, i, j, k, a, b, dis, maxTeams,lastID;
    int teams[MAX_N];
    //读入顶点数和边数
    cin>>N>>M>>S>>D;
    for(i=0; i<N; ++i)
    {
        cin>>teams[i];
        for(j=0; j<N; ++j)
            graph[i][j] = INF;
    }
    for(i=0; i<M; ++i)
    {
        cin>>a>>b>>dis;
        //设置无向图的边长度
        graph[a][b] = graph[b][a] = dis;
        maxTeamsInShortestPath[a][b] = teams[a]+teams[b];
        maxTeamsInShortestPath[b][a] = teams[a]+teams[b];
        shortestPathNums[a][b] = shortestPathNums[b][a] = 1;
    }
    //Floyd
    for(k=0; k<N; ++k)
    {
        for(i=0; i<N; ++i)
        {
            if(i==k)
                continue;
            for(j=0; j<N; ++j)
            {
                if(j==i ||j==k)
                    continue;
                if(graph[i][k]==INF||graph[k][j]==INF)
                    continue;
                dis = graph[i][k]+graph[k][j];
                if(dis<graph[i][j])
                {
                    shortestPathNums[i][j] = 1;
                    shortestPathNums[j][i] = 1;
                    graph[i][j] = dis;
                    graph[j][i] = dis;
                    maxTeamsInShortestPath[i][j] = maxTeamsInShortestPath[i][k]+
                       maxTeamsInShortestPath[k][j]-teams[k];
                    maxTeamsInShortestPath[j][i] = maxTeamsInShortestPath[i][j];

                    pathes[i][j] = pathes[i][k];
                    pathes[i][j].push_back(k);
                    pathes[i][j].insert(pathes[i][j].end(), pathes[k][j].begin(), pathes[k][j].end());

                    pathes[j][i] = pathes[j][k];
                    pathes[j][i].push_back(k);
                    pathes[j][i].insert(pathes[j][i].end(), pathes[k][i].begin(), pathes[k][i].end());
                }
                else if(dis==graph[i][j])
                {
                    ++shortestPathNums[i][j];
                    //++shortestPathNums[j][i];
                    maxTeams = maxTeamsInShortestPath[i][k]+
                       maxTeamsInShortestPath[k][j]-teams[k];
                    if(maxTeamsInShortestPath[i][j]< maxTeams)
                    {
                        maxTeamsInShortestPath[j][i] = maxTeamsInShortestPath[i][j] = maxTeams;
                        pathes[i][j] = pathes[i][k];
                        pathes[i][j].push_back(k);
                        pathes[i][j].insert(pathes[i][j].end(), pathes[k][j].begin(), pathes[k][j].end());

                        pathes[j][i] = pathes[j][k];
                        pathes[j][i].push_back(k);
                        pathes[j][i].insert(pathes[j][i].end(), pathes[k][i].begin(), pathes[k][i].end());

                    }
                }
            }
        }
    }
    cout<<shortestPathNums[S][D]<<" "<<maxTeamsInShortestPath[S][D]<<endl;
    cout<<S;
    lastID = S;
    for(i=0; i<pathes[S][D].size(); ++i)
    {
        if(pathes[S][D][i]==lastID)
            continue;
        cout<<" "<<pathes[S][D][i];
        lastID = pathes[S][D][i];
    }
    if(lastID==D)
        cout<<endl;
    else
        cout<<" "<<D<<endl;
    return 0;
}

