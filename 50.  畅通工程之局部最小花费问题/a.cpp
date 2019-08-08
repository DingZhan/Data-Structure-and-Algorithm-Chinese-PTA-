#include <iostream>
#include <algorithm>

#define MAX_N 101
#define MAX_M 5002 //最多边数

using namespace std;

//这是最小生成树问题，因此采用MST - Minimal Spanning Tree
//这里使用并查集合并集合

//边（道路）信息结构体
struct Edge
{
    int a; //顶点1
    int b; //顶点2
    int cost; //道路成本
};

//未建设道路成本按从小到大排序
bool Compare(const Edge& a, const Edge & b)
{
    return a.cost<b.cost;
}

//利用并查集合并顶点集合
int fathers[MAX_N];
//从一个顶点id，找到它的根节点rootID，根节点特点是rootID = fathers[rootID]
int FindRoot(int id)
{
    //找到了根节点
    if(id==fathers[id])
        return id;
    //继续往上找根节点id
    return FindRoot(fathers[id]);
}

int main()
{
    //未建设的道路数组，已建设的道路不放在该数组中
    Edge edges[MAX_M];
    int N, i, j, M, connect, a, b, cost;
    //读入顶点数
    cin>>N;
    //即将读入的道路信息数
    M = N*(N-1)/2;
    //初始化fathers数组元素都指向自己，即初始状态下每个元素都是一个独立的集合
    for(i=1; i<=N; ++i)
        fathers[i] = i;
    //读入每条边的信息，如果该边还未建设，则把该边信息加到未建设道路数组
    for(i=0, j=0; i<M; ++i)
    {
        //道路顶点a、顶点b、成本、是否已建设好
        cin>>a>>b>>cost>>connect;
        //如果当前道路已经建设好了，直接合并顶点a和顶点b的两个集合
        if(connect)
        {
            //查找顶点a所在集合的根节点id
            a = FindRoot(a);
            //查找顶点b所在集合的根节点id
            b = FindRoot(b);
            //如果两个集合的根节点不同，则合并集合
            if(b!=a)
                fathers[b] = a; //合并集合
        }
        else //当前道路还未建设，所以把道路信息加到未建设道路数组中
        {
            edges[j].a = a;
            edges[j].b = b;
            edges[j].cost = cost;
            ++j;
        }
    }
    //设置未建设道路的数组长度
    M = j;
    //对未建设道路的成本按从小到大进行排序，
    sort(edges, edges+M, Compare);

    //最小生成树MST建设道路成本
    int sum =0;
    //测试未建设道路的两个顶点所在集合，如果两个集合不同，则合并两个集合（即建设一条道路）
    for(i=0; i<M; ++i)
    {
        //查找顶点a所在集合的根节点id
        a = FindRoot(edges[i].a);
        //查找顶点b所在集合的根节点id
        b = FindRoot(edges[i].b);
        //顶点所在的两个集合不同
        if(b!=a)
        {
            //合并集合
            fathers[b] = a;
            //建设这条道路
            sum+=edges[i].cost;
        }
    }
    cout<<sum<<endl;
    return 0;
}
