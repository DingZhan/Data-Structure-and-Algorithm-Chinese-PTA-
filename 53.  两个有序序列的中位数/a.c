#include <stdio.h>

//并集：题目有些歧义，原以为是集合(元素无重复)，结果只是简单的合并，允许重复元素
#define MAX_N 100002
//数组1，最大长度MAX_N
int S1[MAX_N];
//数组2，最大长度MAX_N
int S2[MAX_N];

int main()
{
    //k是合并后数组元素当前下标，当然这里没有必要记录整个合并后的数组
    int k, value;
    int i, j, N, desID;
    //实际数组长度
    scanf("%d", &N);
    //中位数的下标
    desID = (2*N-1)/2;
    //读入数组1
    for(i=0; i<N; ++i)
        scanf("%d", S1+i);
    //读入数组2
    for(i=0; i<N; ++i)
        scanf("%d", S2+i);

    for(i=0, j=0, k = 0; i<N && j<N; )
    {
        //S1[i]小于S2[j]，所以当前要存入的元素是S1[i],  比较len和中位数下标
        if(S1[i]<S2[j])
        {
            //如果合并后数组的当前下标k正好等于中位数下标，则找到了中位数
            if(k==desID)
            {
                value = S1[i];
                break;
            }
            //步进S1数组
            ++i;
            //步进k
            ++k;
        }
        //S1[i]大于S2[j]，所以当前要存入的元素是S2[j],  比较len和中位数下标
        else if(S1[i]>S2[j])
        {
            //如果合并后数组的当前下标k正好等于中位数下标，则找到了中位数
            if(k==desID)
            {
                value = S2[j];
                break;
            }
            //步进S2数组
            ++j;
            //步进k
            ++k;
        }
        else
        {
            //S1[i]等于S2[j]，所以当前要存入两个相同的元素, 同时比较len和中位数下标
            if(k==desID)
            {
                value = S1[i];
                break;
            }
            //步进S2数组
            i++;
            //步进k
            k++;

            if(k==desID)
            {
                value = S2[j];
                break;
            }
            //步进S2数组
            j++;
            //步进k
            k++;
        }
    }
    //可以推理出，此时一定找到了中位数，所以没有必要再去检测while(i<N) 或者 while(j<N)
    printf("%d\n", value);
    return 0;
}
