#include <iostream>
#include <vector>

using namespace std;

//目标：查找有向图中是否有环路

#define MAX_N 101
//用二维数组表示有向图，有效下标从1开始
bool graphics[MAX_N][MAX_N];
//设置图中顶点是否访问过，如果顶点访问过就不要再尝试深度优先搜索
bool bVisits[MAX_N];

//递归深度优先搜索环路，seed表示当前位置，N表示顶点数目，
//bLoopVisits是标记哪些顶点正在搜索路径里
//bHasLoop标记是否搜索到了环路
//path是环路路径
void DFS_HasLoop(int seed, int N, bool bLoopVisits[], bool& bHasLoop, std::vector<int>& path)
{
    //设置当前位置在搜索路径里
    bLoopVisits[seed] = true;
    //设置当前位置被访问了
    bVisits[seed] = true;
    //把当前位置加到路径中
    path.push_back(seed);
    int j;
    //搜索seed指向的边
    for(j=1; j<=N; ++j)
    {
        if(!graphics[seed][j])
            continue;
        //找到一条边seed->j
        //如果边顶点j已经在当前搜索路径里，则说明找到了环路
        if(bLoopVisits[j])
        {
            //剔除前面非环路的部分路径
            while(path.front()!=j)
                path.erase(path.begin());
            path.push_back(j);
            //设置了找到环路的标志
            bHasLoop = true;
            //返回
            return;
        }
        //如果边顶点j没被访问过，则DFS到j
        if(!bVisits[j])
        {
            //递归DFS到j
            DFS_HasLoop(j, N, bLoopVisits, bHasLoop, path);
            //如果环路标志被设置过，则返回
            if(bHasLoop)
                return;
        }
    }
    //当前顶点没有在任何环路，所以回退
    path.pop_back();
    //当前顶点没有在任何环路，所以回退标记
    bLoopVisits[seed] = false;
    return;
}

int main()
{
    //关闭与stdio的同步
    std::ios::sync_with_stdio(false);
    int i, j, N, K, v, seed;
    //环路标记，初始时没有环路
    bool bHasLoop=false;
    //读入顶点数目
    cin>>N;
    //对于每个顶点
    for(i=1; i<=N; ++i)
    {
        //读入它的前导顶点数目
        cin>>K;
        //读入它的所有前导顶点
        for(j=0; j<K; ++j)
        {
            cin>>v;
            //设置有向图
            graphics[v][i] = true;
        }
    }
    //遍历所有顶点，检测有向图中是否有环路
    for(i=1; i<=N; ++i)
    {
        //如果该顶点在之前已经被访问过，则检测下一个顶点
        if(bVisits[i])
            continue;
        //环路路径
        std::vector<int> path;
        //初始当前路径顶点访问标记
        bool bLoopVisits[MAX_N]={false};
        //DFS检测环路
        DFS_HasLoop(i, N, bLoopVisits, bHasLoop, path);
        //如果检测到环路则退出
        if(bHasLoop)
            break;
    }

    cout<<(bHasLoop?0:1)<<endl;
    return 0;
}

