#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//采用链式结构的hash表，这是最通用的hash方式

//定义旅客的结构体，包括身份证号，英里数和一个next指针指向下一个结点
typedef struct Traveller_
{
    char ID[19];
    unsigned int miles;
    struct Traveller_ *next;
}Traveller;

//找一个合适的质数，即做索引除法又做hash表长度
#define MAX_P 100003
//不小于n的最小质数
int FindPrime(int n)
{
    int i, t;
    while(true)
    {
        t = sqrt(n);
        for(i=2; i<=t; ++i)
        {
            if(n%i==0)
                break;
        }
        if(i>t)
            break;
        ++n;
    }
    return n;
}

//给定一个身份证号，定一个公式映射到hash表某个位置
//这个hash定位公式不是固定的，公式最佳表现是能够将大量的身份证映射到hash表不同的位置
//因此，寻址的均匀性是hash表重要考核指标
int IDIndex(const char ID[19])
{
    int index=0, i, j, pow;
    //每6位做一个六位数累加到index，对于'x'也是用同样的方法
    for(i=0, pow=1; i<19; ++i)
    {
        index+=(ID[i]-'0')*pow;
        if(pow==100000)
            pow = 1;
        else
            pow*=10;
    }
    //对hash表长度取余
    return index%MAX_P;
}

//定义旅客的hash表
Traveller* hashTables[MAX_P];

int main()
{
    int N, K, M, i, mile, index;
    char ID[19];
    Traveller *pTraveller, *pPre;
    //读入旅客信息条数和最小英里数
    scanf("%d%d", &N, &K);
    for(i=0; i<N; ++i)
    {
        //读入当前一条旅客身份证号和英里数
        scanf("%s%d", &ID,&mile);
        //如果英里小于门槛线，则把英里数设置为门槛线
        if(mile<K)
            mile = K;
        //对身份证号进行寻址，映射hash表
        index = IDIndex(ID);
        //在hash该位置找到该条记录的链表
        pTraveller = hashTables[index];
        pPre = NULL;
        //遍历hash表当前位置的链表
        while(pTraveller)
        {
            //如果当前结点的身份证号和搜索的身份证号一样，则该旅客信息已经在hash表
            if(strcmp(pTraveller->ID, ID)==0)
                break;
            //设置一个链表的前置结点
            pPre = pTraveller;
            //将当前结点指向下一个结点
            pTraveller = pTraveller->next;
        }
        //如果在hash链表中已经找到了该旅客信息，则只要累加英里数
        if(pTraveller)
        {
            pTraveller->miles+=mile;
        }
        else //没找到该旅客信息，因此加入一个新结点到hash链表中
        {
            pTraveller = (Traveller*)malloc(sizeof(Traveller));
            //一定要把next指针设置为NULL
            pTraveller->next = NULL;
            strcpy(pTraveller->ID, ID);
            pTraveller->miles=mile;
            //链表非空，因此加入链表尾部
            if(pPre)
                pPre->next = pTraveller;
            else //链表为空，因此新结点要加入链表头
                hashTables[index] = pTraveller;
        }
    }
    //读入待搜索的身份证人数
    scanf("%d", &M);
    for(i=0; i<M; ++i)
    {
        //读入一条身份证
        scanf("%s", ID);
        //映射到hash表具体位置
        index = IDIndex(ID);
        //找到该位置的链表
        pTraveller = hashTables[index];
        //遍历该链表，查找该身份证是否出现过
        while(pTraveller)
        {
            //找到该身份证信息
            if(strcmp(pTraveller->ID, ID)==0)
                break;
            pTraveller = pTraveller->next;
        }
        //找到该身份证信息，打印总英里数
        if(pTraveller)
            printf("%d\n", pTraveller->miles);
        else//没找到
            printf("No Info\n");
    }

    return 0;
}