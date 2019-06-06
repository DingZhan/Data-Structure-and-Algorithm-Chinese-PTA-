#include <stdio.h>
#include <stdlib.h>


#define MAX_N 230

//定义国家获奖的结构体
typedef struct Nation_
{
    //金牌数
    int gold;
    //奖牌数
    int medal;
    //总人口
    int people;
    //国家编号
    int id;
}Nation;

//金牌数递减的比较函数
int CompareByGold(const void *a, const void *b)
{
    Nation *aa = (Nation*)a;
    Nation *bb = (Nation*)b;
    return bb->gold - aa->gold;
}

//奖牌数递减的比较函数
int CompareByMedal(const void *a, const void *b)
{
    Nation *aa = (Nation*)a;
    Nation *bb = (Nation*)b;
    return bb->medal - aa->medal;
}

//平均金牌数递减的比较函数
int CompareByAveGold(const void *a, const void *b)
{
    Nation *aa = (Nation*)a;
    Nation *bb = (Nation*)b;
    double r1 = aa->gold*1.0/aa->people;
    double r2 = bb->gold*1.0/bb->people;
    if(r1>r2)
        return -1;
    else if(r1<r2)
        return 1;
    else
        return 0;
}

//平均奖牌数递减的比较函数
int CompareByAveMedal(const void *a, const void *b)
{
    Nation *aa = (Nation*)a;
    Nation *bb = (Nation*)b;
    double r1 = aa->medal*1.0/aa->people;
    double r2 = bb->medal*1.0/bb->people;
    if(r1>r2)
        return -1;
    else if(r1<r2)
        return 1;
    else
        return 0;
}

int main()
{
    //各国获奖的结构体数组
    Nation nations[MAX_N];
    //请求查询成绩的国家编号
    int request[MAX_N];
    //金牌排行榜
    int goldRank[MAX_N];
    //奖牌排行榜
    int medalRank[MAX_N];
    //平均金牌排行榜
    int aveGoldRank[MAX_N];
    //平均奖牌排行榜
    int aveMedalRank[MAX_N];
    int i, N, M, rank, lastValue;
    double lastDValue;

    //读入奥运国家数和查询的国家数
    scanf("%d%d", &N, &M);
    //读入各国奥运成绩
    for(i=0; i<N; ++i)
    {
        //设置该国编号
        nations[i].id = i;
        //读入金牌，奖牌和人口
        scanf("%d%d%d", &(nations[i].gold), &(nations[i].medal), &(nations[i].people));
    }
    //读入查询的所有国家编号
    for(i=0; i<M; ++i)
        scanf("%d", request+i);

    //按金牌数递减排序
    qsort(nations, N, sizeof(Nation), CompareByGold);
    //上一个国家的金牌数
    lastValue = -1;
    for(i=0, rank=0; i<N; ++i)
    {
        //如果本国金牌数和金牌排行榜上上一个国家金牌数不一样
        if(lastValue!=nations[i].gold)
        {
            //这里千万不能写成rank++,例如 1 1 3 4 , 其中第三个队伍是排名为第三而不是第二
            rank = i+1;
            //设置lastValue
            lastValue = nations[i].gold;
        }
        //设置本国金牌排行
        goldRank[nations[i].id] = rank;
    }

    //按奖牌数递减排序
    qsort(nations, N, sizeof(Nation), CompareByMedal);
    //上一个国家的奖牌数
    lastValue = -1;
    for(i=0, rank=0; i<N; ++i)
    {
        //如果本国奖牌数和奖牌排行榜上上一个国家奖牌数不一样
        if(lastValue!=nations[i].medal)
        {
            //这里千万不能写成rank++,例如 1 1 3 4 , 其中第三个队伍是排名为第三而不是第二
            rank = i+1;
            lastValue = nations[i].medal;
        }
        //设置本国奖牌排行
        medalRank[nations[i].id] = rank;
    }

    //按平均金牌数递减排序
    qsort(nations, N, sizeof(Nation), CompareByAveGold);
    //设置上一个国家平均金牌数
    lastDValue = 1000000.;
    for(i=0, rank=0; i<N; ++i)
    {
        //如果本国平均金牌数和平均金牌排行榜上上一个国家平均金牌数不一样
        if(lastDValue-nations[i].gold*1.0/nations[i].people>1.0e-6)
        {
            //这里千万不能写成rank++,例如 1 1 3 4 , 其中第三个队伍是排名为第三而不是第二
            rank = i+1;
            lastDValue = nations[i].gold*1.0/nations[i].people;
        }
        //设置本国平均金牌数排行
        aveGoldRank[nations[i].id] = rank;
    }

    //按平均奖牌数递减排序
    qsort(nations, N, sizeof(Nation), CompareByAveMedal);
    //设置上一个国家平均奖牌数
    lastDValue = 1000000.;
    for(i=0, rank=0; i<N; ++i)
    {
        //如果本国平均奖牌数和平均奖牌排行榜上上一个国家平均奖牌数不一样
        if(lastDValue-nations[i].medal*1.0/nations[i].people>1.0e-6)
        {
            //这里千万不能写成rank++,例如 1 1 3 4 , 其中第三个队伍是排名为第三而不是第二
            rank = i+1;
            lastDValue = nations[i].medal*1.0/nations[i].people;
        }
        //设置本国平均奖牌数排行
        aveMedalRank[nations[i].id] = rank;
    }

    int minRank;
    int minRankType;
    int nationID;
    for(i=0; i<M; ++i)
    {
        //请求查询国家的编号
        nationID = request[i];
        //设置最高排名，用金牌榜成绩作初始值
        minRank = goldRank[nationID];
        minRankType = 1;

        //如果奖牌成绩更优
        if(medalRank[nationID]<minRank)
        {
            minRank = medalRank[nationID];
            minRankType = 2;
        }
        //如果平均金牌成绩更优
        if(aveGoldRank[nationID]<minRank)
        {
            minRank = aveGoldRank[nationID];
            minRankType = 3;
        }
        //如果平均奖牌成绩更优
        if(aveMedalRank[nationID]<minRank)
        {
            minRank = aveMedalRank[nationID];
            minRankType = 4;
        }
        //第一个不打印空格
        if(i)
            printf(" ");
        printf("%d:%d", minRank, minRankType);
    }
    printf("\n");
    return 0;
}
