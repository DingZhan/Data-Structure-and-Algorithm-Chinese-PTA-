#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 1001
#define MAX_M 3003

//Minimal Spanning Tree, MST 最小生成树, 这里使用并查集方法解决MST问题
//参考刘汝佳, <算法竞赛入门经典> p200

//定义边结构体
struct Edge
{
    int u; //边的端点
    int v; //边的另一个端点
    int w; //每条边的造价(权值)
};

//最多MAX_M条边
Edge edges[MAX_M];
//并查集的每个结点所在树的根结点
short p[MAX_N];

//边比较函数,按权值从小到大排列
bool CompareWeight(const Edge& a ,const Edge&b)
{
    if(a.w<b.w)
        return true;
    else
        return false;
}

//并查集中，找到结点x所在树的树根结点
int findRoot(int x)
{
    //如果树根结点就是他自己，则已经到了根结点
    if(p[x]==x)
        return x;
    else
        return findRoot(p[x]);//否则往父结点继续向上查找
}

int main()
{
    int i, j, N, M, sum=0;
    //输入结点数和边数
    cin>>N>>M;
    //读入所有边信息
    for(i=0; i<M; ++i)
        cin>>edges[i].u>>edges[i].v>>edges[i].w;
    //初始化并查集，当前结点都是一棵独立的树
    for(i=1; i<=N; ++i)
        p[i] = i;

    //对边的权值按从小到大排序
    std::sort(edges, edges+M, CompareWeight);

    //Kruskal算法，见刘汝佳 p200
    for(i=0; i<M; ++i)
    {
        //找到当前边一个端点所在的集合编号
        int x = findRoot(edges[i].u);
        //找到当前边另一个端点所在的集合编号
        int y = findRoot(edges[i].v);
        //如果不是同一个集合，因为这条边的存在，所以合并两个集合
        if(x!=y)
        {
            //把边权值累加
            sum+=edges[i].w;
            //将一个根的父节点设置为另一个树的根结点
            p[x] = y;
        }
    }

    //判断连通性，如果有结点和第一个结点不在同一个集合，则图不连通
    int root = findRoot(1);
    for(i=2; i<=N; ++i)
    {
        int root2 = findRoot(i);
        if(root2!=root)
            break;
    }

    //不连通
    if(i<=N)
        cout<<"-1\n";
    else//连通
        cout<<sum<<endl;
    return 0;
}
