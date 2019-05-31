#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//搜索出的哈希表长度
#define MAX_N 100003

//定义hash链表结构体
typedef struct User_
{
    char pass[17];
    long long id;
    struct User_ *next;
}User;

//hash表，冲突采用链表记录法
User *users[MAX_N];

//找到大于等于n的最小质数，作为哈希表长度
int MinPrime(int n)
{
    while(true)
    {
        int i;
        int t =sqrt(n);
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

//释放hash表中的动态分配内存
void FreeMemory()
{
    User *pNode, *pLast;
    int i;
    for(i=0; i<MAX_N; ++i)
    {
        if(users[i])
        {
            pNode = users[i];
            while(pNode)
            {
                pLast = pNode;
                pNode = pNode->next;
                free(pLast);
            }
            users[i] = NULL;
        }
    }
}

int main()
{
//搜索最小质数的方法
//    int n =100000;
//    printf("%d",MinPrime(n));
    int i, N, pos;
    long long id;
    char pass[17], type, lineStr[64];
    User *pNode, *pLast;

    scanf("%d", &N);
    //过滤掉第一行的回车键
    fgets(lineStr, 16, stdin);

    for(i=0; i<N; ++i)
    {
        //一行行得字符串，否则scanf("%c... 会有问题
        fgets(lineStr, 64, stdin);
        //用sscanf从字符串提取信息
        sscanf(lineStr, "%c %lld %s", &type, &id, pass);
        //获得当前hash表内的位置
        pos = (int)(id%MAX_N);
        //该位置的链表头
        pNode = pLast = users[pos];
        //如果是新建账户
        if(type=='N')
        {
            //访问该位置的链表，如果有结点的id和当前id重复，则显示该用户已存在
            while(pNode)
            {
                //结点的id和当前id重复，则表明该用户已存在
                if(pNode->id==id)
                    break;
                pLast = pNode;
                pNode = pNode->next;
            }
            //如果遍历到链表尾也没发现相同的id，则可以创建该账号
            if(pNode==NULL)
            {
                //动态分配内存
                pNode = (User*)malloc(sizeof(User));
                //把next结点置为空
                pNode->next = NULL;
                pNode->id = id;
                strcpy(pNode->pass, pass);
                //让链表尾部指向当前创建的结点
                if(pLast)
                    pLast->next = pNode;
                else //特殊情形，当前链表为空时，直接插入链表头
                    users[pos] = pNode;
                printf("New: OK\n");
            }
            else
            {
                printf("ERROR: Exist\n");
            }
        }
        else //登陆
        {
            //遍历该链表，查询是否有该账户信息
            while(pNode)
            {
                //找到了该账户
                if(pNode->id==id)
                    break;
                pNode = pNode->next;
            }
            //如果没找到该账户，则说明不存在该登陆账户
            if(pNode==NULL)
            {
                printf("ERROR: Not Exist\n");
            }
            else
            {
                //比较登陆密码
                if(strcmp(pNode->pass, pass)==0)
                    printf("Login: OK\n");
                else
                    printf("ERROR: Wrong PW\n");
            }

        }
    }
    //最后释放hash表
    FreeMemory();
    return 0;
}
