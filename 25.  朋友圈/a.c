#include <stdio.h>
#include <stdlib.h>

//使用并查集(Union-Find Set)，刘汝佳《算法竞赛入门经典》，p200
#define MAX_N 300002
#define MAX_M 1001

//并查集的每个结点所在集合的根结点编号
int parents[MAX_N];
//学生访问标志
char bVisits[MAX_N];
//桶，用来计算该集合的人数，集合ID就是根结点ID
int buckets[MAX_N];

//找到树根
int find(int x)
{
    if(parents[x]==x)
        return x;
    else
        return find(parents[x]);
}
int main()
{
    int N, M, i, j, num, refRootID, rootID, id;
    //读入学生总数和俱乐部总数
    scanf("%d%d", &N, &M);
    //将并查集每个结点指向自己，即自己当前是个独立的集合
    for(i=1; i<=N; ++i)
        parents[i] = i;
    //读入每个俱乐部信息
    for(i=1; i<=M; ++i)
    {
        //当前俱乐部人数
        scanf("%d", &num);
        //参考根节点，一会会将当前所有俱乐部学生指向参考节点
        refRootID = -1;
        for(j=0; j<num; ++j)
        {
            //读入学生学号
            scanf("%d", &id);
            //查找该学生所在集合的根结点
            rootID = find(id);
            //将参考根结点设置为第一个元素的根结点
            if(j==0)
                refRootID = rootID;
            else//其他所有元素的根节点都指向参考根节点
                parents[rootID] = refRootID;
        }
    }

    //初始化最大朋友圈人数为0
    int maxNum=0;
    //遍历每个学生
    for(i=1; i<=N; ++i)
    {
        //如果该学生已经被访问过
        if(bVisits[i])
            continue;
        //找到该学生所在集合的根结点
        rootID = find(i);
        //该集合桶累加1，桶ID就是集合根节点ID
        buckets[rootID]++;
        //边累加边判断
        if(buckets[rootID]>maxNum)
            maxNum = buckets[rootID];
    }
    printf("%d\n", maxNum);
    return 0;
}
