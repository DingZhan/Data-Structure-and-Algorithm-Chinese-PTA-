#include <iostream>
#include <queue>

#define MAX_N 11

//用二维数组记录图连通状况
bool graph[MAX_N][MAX_N];

void BFS(int N)
{
    int i, j, seed;
    //顶点访问标记数组
    bool bVerticesTakens[MAX_N]={false};
    //遍历所有顶点
    for(i=0; i<N; ++i)
    {
        //如果当前顶点已经被访问过，则忽略
        if(bVerticesTakens[i])
            continue;
        //设置当前顶点的访问标记
        bVerticesTakens[i] = true;
        //宽度优先遍历所以用队列
        std::queue<int> seeds;
        std::cout<<"{";
        seeds.push(i);
        while(!seeds.empty())
        {
            seed = seeds.front();
            std::cout<<" "<<seed;
            seeds.pop();
            //找到和顶点seed共边的所有顶点
            for(j=0; j<N; ++j)
            {
                //如果和seed共边，并且没有被访问过
                if(graph[seed][j] && !bVerticesTakens[j])
                {
                    //设置顶点j的访问标记
                    bVerticesTakens[j] = true;
                    //把j加到队列
                    seeds.push(j);
                }
            }
        }
        std::cout<<" }\n";
    }
}

//深度优先遍历递归方法
void DFS_Interator(int seed, int N, bool* bTakens)
{
    int i;
    std::cout<<" "<<seed;
    //找到和顶点seed共边的所有顶点
    for(i=0; i<N; ++i)
    {
        //如果和seed共边，并且没有被访问过
        if(graph[seed][i] && !bTakens[i])
        {
            //设置顶点i的访问标记
            bTakens[i] = true;
            //以顶点i为种子，深度优先遍历
            DFS_Interator(i, N, bTakens);
        }
    }
}

//深度优先遍历接口函数
void DFS(int N)
{
    //顶点访问标记数组
    bool bTakens[MAX_N]={false};
    int i;
    //遍历所有顶点
    for(i=0; i<N; ++i)
    {
        //如果当前顶点已经被访问过，则忽略
        if(bTakens[i])
            continue;
        std::cout<<"{";
        //设置当前顶点的访问标记
        bTakens[i] = true;
        //深度优先遍历
        DFS_Interator(i, N, bTakens);
        std::cout<<" }\n";
    }
}


int main()
{
    int i, N, E, v1, v2;
    std::cin>>N>>E;
    for(i=0; i<E; ++i)
    {
        std::cin>>v1>>v2;
        //设置顶点之间的连通标记
        graph[v1][v2]=true;
        graph[v2][v1]=true;
    }
    //深度优先遍历
    DFS(N);
    //宽度优先遍历
    BFS(N);
}
