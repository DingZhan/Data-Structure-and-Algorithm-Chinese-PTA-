#include <stdio.h>
#include <stdlib.h>

//定义链表节点结构体
typedef struct LinkNode_
{
    int v;
    struct LinkNode_*next;
}LinkNode;

int main()
{
    int K, v, count=0;
    LinkNode *pHead=NULL, *pNode, *pTail=NULL, *pDesNode=NULL;
    //读入K
    scanf("%d", &K);
    while(1)
    {
        scanf("%d", &v);
        //这里仔细读题，不能写成-1
        if(v<0)
            break;
        //动态分配一个结点
        pNode = (LinkNode*)malloc(sizeof(LinkNode));
        pNode->next = NULL;
        pNode->v = v;
        //如果链表非空，则把链表尾部结点指向当前新创建的结点
        if(pTail)
            pTail->next = pNode;
        else//链表为空，把当前结点设置为头结点
            pHead = pNode;
        //移动链表尾部结点
        pTail = pNode;
        //计算器+1
        ++count;
        //如果链表里正好有K个元素了，则当前倒数第K个就是链表头结点
        if(count==K)
            pDesNode = pHead;
        else if(count>K) //否则如果结点数超过K，把目标结点每次都往后移一个结点
            pDesNode = pDesNode->next;
    }
    //如果倒数第K个结点非空
    if(pDesNode)
        printf("%d\n", pDesNode->v);
    else
        printf("NULL\n");
    //最后释放内存
    pNode = pHead;
    while(pNode)
    {
        pTail = pNode->next;
        free(pNode);
        pNode = pTail;
    }
    return 0;
}
