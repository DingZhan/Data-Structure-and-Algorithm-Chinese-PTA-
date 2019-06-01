#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100001
#define MAX_M 31

char names[MAX_N][MAX_M];
//a,bʵ��ָ�����char[MAX_N],�Ƕ�ά�����ÿһ���ַ���
int Compare(const void*a , const void *b)
{
    char *aa = (char*)a;
    char *bb = (char*)b;
    //ֱ��ʹ��strcmp��Ϊ�ֵ�ȽϷ���ֵ
    return strcmp(aa, bb);
}
int main()
{
    int i, N, count;
    char str[MAX_M];

    //��һ��Ҳ��gets������\n�鷳
    gets(str);
    //�������
    N = atoi(str);

    //�õ�ÿ��������������scanf����Ϊ���������пո�
    for(i=0; i<N; ++i)
        gets(names[i]);

    //��������������
    qsort(names, N, sizeof(names[0]), Compare);

    //��һ���ַ���Ϊ��
    str[0] = '\0';
    //��һ��ͬ���ַ�������Ϊ0
    count = 0;
    for(i=0; i<N; ++i)
    {
        //�����ǰ��������һ������ͬ�������ۼ�count
        if(strcmp(str, names[i])==0)
        {
            ++count;
        }
        else
        {
            //��ǰ��������һ��������ͬ�����ӡ��һ�������Ľ��
            if(count>0)
            {
                printf("%s %.4lf%%\n", str, count*100.0/N);
            }
            //ˢ����һ��������Ϣ
            strcpy(str, names[i]);
            //���ø�������������Ϊ1
            count = 1;
        }
    }
    //��Ҫ��©���ʣ�µ���
    if(count>0)
    {
        printf("%s %.4lf%%\n", str, count*100.0/N);
    }
    return 0;
}
