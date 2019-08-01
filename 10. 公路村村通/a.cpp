#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 1001
#define MAX_M 3003

//Minimal Spanning Tree, MST 最小生成树, 这里使用并查集方法解决MST问题
//参考刘汝佳, <算法竞赛入门经典> p200

struct Edge
{
    int u; //起点
    int v; //终点
    int w; //造价
};
Edge edges[MAX_M];
short p[MAX_N]; //并查集的每个结点所在树的根结点

//边权比较函数
bool CompareWeight(const Edge& a ,const Edge&b)
{
    if(a.w<b.w)
        return true;
    else
        return false;
}
int findRoot(int x)
{
    if(p[x]==x)
        return x;
    else
        return findRoot(p[x]);
}
int main()
{
    int i, j, N, M, sum=0, edgesInTree=0;
    //输入矩阵
    cin>>N>>M;
    //读入所有边信息
    for(i=0; i<M; ++i)
        cin>>edges[i].u>>edges[i].v>>edges[i].w;
    //初始化并查集
    for(i=1; i<=N; ++i)
        p[i] = i;
    //对边的权值按从小到大排序
    std::sort(edges, edges+M, CompareWeight);

    //Kruskal算法，见刘汝佳 p200
    //MST中如果树中边的数目+1等于顶点数，则已经生成MST，可以退出循环
    for(i=0; i<M && edgesInTree+1!=N; ++i)
    {
        int x = findRoot(edges[i].u);
        int y = findRoot(edges[i].v);
        if(x!=y)
        {
            sum+=edges[i].w;
            p[x] = y;
            ++edgesInTree;
        }
    }

    //如果树中边的数目不等于顶点数-1，则不是一颗MST
    if(edgesInTree+1!=N)
        cout<<"-1\n";
    else
        cout<<sum<<endl;
    return 0;
}
