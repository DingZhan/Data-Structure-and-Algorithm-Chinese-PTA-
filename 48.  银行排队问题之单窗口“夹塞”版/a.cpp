#include <iostream>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

//排队人员信息结构体
struct Queuer
{
    char name[4]; //排队人名字
    int RT; //rank time, 开始排队的时间，输入
    int JT; //job time，任务持续时间，输入
    int ST; //start time, 任务实际开始时间，计算
    int ET; //end time,任务实际结束时间，计算
    bool bVisited; //访问标记位
    int friendRoundID; //朋友圈ID
    Queuer()
    {
        //初始化没有被服务
        bVisited = false;
        //初始化朋友圈ID为0，表示目前没有朋友
        friendRoundID = 0;
    }
};
//最多排队人数
#define MAX_N 10002
//排队人员数组
Queuer qs[MAX_N];

int main()
{
    //名字映射到朋友圈ID
    map<string, int> nameMapFriendRoundID;
    //map迭代器
    map<string, int>::iterator it;
    //名字
    char name[4];
    //currentTime是当前时间，currentFriendRoundID是当前服务对象的朋友圈ID
    int i, j, N, M, currentTime, currentFriendRoundID;
    //读入排队人个数N，朋友圈数M
    cin>>N>>M;
    //读入M个朋友圈信息，朋友圈编号从1开始
    for(i=1; i<=M; ++i)
    {
        //读入当前朋友圈i有多少人
        cin>>j;
        //读入j个朋友的名字
        while(j-->0)
        {
            cin>>name;
            //将该名字映射到朋友圈ID
            nameMapFriendRoundID[name] = i;
        }
    }

    //读入N个排队人信息
    for(i=0; i<N; ++i)
    {
        //读入名字、排队时间、任务时间
        cin>>qs[i].name>>qs[i].RT>>qs[i].JT;
        //如果任务时间超过60分钟，则截断为60分钟（读题）
        if(qs[i].JT>60)
            qs[i].JT = 60;
        //找到该排队人对应的朋友圈编号
        it = nameMapFriendRoundID.find(qs[i].name);
        //如果该排队人有朋友圈，则设置该排队人朋友圈编号
        if(it!=nameMapFriendRoundID.end())
            qs[i].friendRoundID = it->second;
    }

    //初始化当前时间为0
    currentTime = 0;
    //循环，直到排队的所有人都被服务了
    while(true)
    {
        //找一个编号最小且没有被服务的人
        for(i=0; i<N; ++i)
        {
            if(!qs[i].bVisited)
                break;
        }
        //如果找不到，则所有人都被服务了，退出循环
        if(i==N)
            break;
        //设置该人访问标记
        qs[i].bVisited = true;
        //如果他的入队时间超过当前时间，则说明窗口有一段时间是空闲的，没事，直接调整当前时间
        if(qs[i].RT>currentTime)
            currentTime = qs[i].RT;
        //将当前服务开始时间设置为当前时间
        qs[i].ST = currentTime;
        //将当前服务结束时间设置为当前时间+任务持续时间
        qs[i].ET = currentTime+qs[i].JT;
        //设置当前服务对象所在的朋友圈
        currentFriendRoundID = qs[i].friendRoundID;
        //同时刷新当前时间为任务结束时间
        currentTime = qs[i].ET;
        //打印当前被服务人的姓名
        cout<<qs[i].name<<endl;

        //搜索所有未被访问且已经在排队的朋友
        //该人有朋友圈
        if(currentFriendRoundID!=0)
        {
            while(true)
            {
                //搜索所有未被访问且已经在排队的朋友
                for(j=i+1; j<N; ++j)
                {
                    if(!qs[j].bVisited && qs[j].friendRoundID==currentFriendRoundID &&
                       qs[j].RT<=currentTime)
                        break;
                }
                //没找到这样的朋友，则退出循环
                if(j==N)
                    break;
                //设置该朋友被访问过标记
                qs[j].bVisited = true;
                //设置该朋友任务开始时间为当前时间
                qs[j].ST = currentTime;
                //设置该朋友任务结束时间为当前时间+任务持续时间
                qs[j].ET = currentTime+qs[j].JT;
                //更新当前时间
                currentTime = qs[j].ET;
                //打印朋友姓名
                cout<<qs[j].name<<endl;
            }
        }
    }

    //累加所有人员的等待时间
    double waitTimes=0;
    for(i=0; i<N; ++i)
    {
        //等待时间就是任务开始时间减去排队开始时间
        waitTimes+=qs[i].ST-qs[i].RT;
    }
    cout<<std::fixed<<std::setprecision(1)<<waitTimes/N;
    return 0;
}
