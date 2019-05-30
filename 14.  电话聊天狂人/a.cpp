#include <iostream>
#include <map>

using namespace std;

int main()
{
    int N, i, maxCount=-1, sameNum=0;
    //因为电话是11位，所以不能用unsigned int，只能用long long
    //当然也可以用char[]，但要12个字节,没有8个字节long long划算
    long long a, b, maxPhone;
    //用STL的map容器，将任何一个电话号码映射到通话次数,即<phone, number>
    std::map<long long, int> phoneMapCounts;
    //map的迭代器
    std::map<long long, int>::iterator it;
    //输入N
    cin>>N;
    //读入N条通话记录，将通话双方的引用次数都加1
    for(i=0; i<N; ++i)
    {
        cin>>a>>b;
        ++phoneMapCounts[a];
        ++phoneMapCounts[b];
    }
    //遍历一遍map容器，找出最大通话次数
    //因为map的key就是phone number，而key就是按从小到大排列的
    //所以正好满足"如果这样的人不唯一，则输出狂人中最小的号码及其通话次数"
    for(it=phoneMapCounts.begin(); it!=phoneMapCounts.end(); ++it)
    {
        //如果当前号码对应的通话次数大于当前最大通话次数，则更新记录
        if(it->second>maxCount)
        {
            maxCount = it->second;
            maxPhone = it->first;
            //把同样通话次数的人数重置为1
            sameNum = 1;
        }
        //如果当前号码对应的通话次数等于当前最大通话次数，则累加人数
        else if(it->second==maxCount)
        {
            ++sameNum;
        }
    }
    //如果最大通话次数只有一人
    if(sameNum==1)
    {
        cout<<maxPhone<<" "<<maxCount<<endl;
    }
    else
    {
        cout<<maxPhone<<" "<<maxCount<<" "<<sameNum<<endl;
    }

    return 0;
}
