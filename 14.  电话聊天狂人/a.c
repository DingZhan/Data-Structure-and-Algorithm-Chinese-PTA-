#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200001

//将所有号码存到一个数组李
long long phones[MAX_N];

//号码比较函数,因为是long long类型，所以不好直接用(long long*)a-(long long*)b简化，怕溢出
int Compare(const void *a, const void *b)
{
    long long *aa=(long long*)a;
    long long *bb=(long long*)b;
    if(*aa<*bb)
        return -1;
    else if(*aa>*bb)
        return 1;
    else
        return 0;
}
int main()
{
    int N, i, maxCount=0, sameNum, lastCount;
    long long a, b, maxPhone, lastPhone=-1;
    //读入通话记录总数
    scanf("%d", &N);
    //读入所有通话记录
    for(i=0; i<N; ++i)
    {
        //%lld是long long类型读入格式
        scanf("%lld%lld", &a, &b);
        //把双方号码存储到数组中
        phones[2*i] = a;
        phones[2*i+1] = b;
    }
    //对数组快速排序,号码从小到大排列
    qsort(phones, 2*N, sizeof(long long), Compare);

    //开始对排序后的数组，计算相同号码情况
    for(i=0, lastCount=-1; i<2*N; ++i)
    {
        //如果当前号码等于上一个号码，则累加该号码的通话次数
        if(lastPhone==phones[i])
        {
            lastCount++;
        }
        else //当前号码不等于上一个号码，需要分析谁的通话次数多
        {
            //如果上一个号码的通话次数大于记录的最大通话次数
            //则刷新最大通话次数的记录
            if(lastCount>maxCount)
            {
                maxPhone = lastPhone;
                maxCount = lastCount;
                //重置当前最大通话记录人数为1
                sameNum=1;
            }
            //如果上一个号码的通话次数等于记录的最大通话次数
            //则累加当前最大通话记录人数
            else if(lastCount==maxCount)
                sameNum++;
            //重置上一个电话号码，和通话次数
            lastPhone = phones[i];
            lastCount = 1;
        }
    }
    //最后处理循环结束后未处理的情况
    if(lastCount>maxCount)
    {
        maxPhone = lastPhone;
        maxCount = lastCount;
        sameNum=1;
    }
    else if(lastCount==maxCount)
        sameNum++;

    if(sameNum==1)
    {
        printf("%lld %d\n", maxPhone, maxCount);
    }
    else
    {
        printf("%lld %d %d\n", maxPhone, maxCount, sameNum);
    }

    return 0;
}
