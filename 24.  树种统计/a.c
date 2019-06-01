#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100001
#define MAX_M 31

char names[MAX_N][MAX_M];
//a,b实际指向的是char[MAX_N],是二维数组的每一行字符串
int Compare(const void*a , const void *b)
{
    char *aa = (char*)a;
    char *bb = (char*)b;
    //直接使用strcmp作为字典比较返回值
    return strcmp(aa, bb);
}
int main()
{
    int i, N, count;
    char str[MAX_M];

    //第一行也用gets，避免\n麻烦
    gets(str);
    //变成整形
    N = atoi(str);

    //得到每个树名，不能用scanf，因为树名可能有空格
    for(i=0; i<N; ++i)
        gets(names[i]);

    //对树名快速排序
    qsort(names, N, sizeof(names[0]), Compare);

    //上一个字符串为空
    str[0] = '\0';
    //上一个同名字符串个数为0
    count = 0;
    for(i=0; i<N; ++i)
    {
        //如果当前树名和上一个树名同名，则累加count
        if(strcmp(str, names[i])==0)
        {
            ++count;
        }
        else
        {
            //当前树名和上一个树名不同，则打印上一个树名的结果
            if(count>0)
            {
                printf("%s %.4lf%%\n", str, count*100.0/N);
            }
            //刷新上一个树名信息
            strcpy(str, names[i]);
            //重置该树名的树个数为1
            count = 1;
        }
    }
    //不要遗漏最后还剩下的树
    if(count>0)
    {
        printf("%s %.4lf%%\n", str, count*100.0/N);
    }
    return 0;
}
