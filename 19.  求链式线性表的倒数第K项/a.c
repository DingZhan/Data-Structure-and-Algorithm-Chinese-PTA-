#include <stdio.h>
#include <stdlib.h>

//��������ڵ�ṹ��
typedef struct LinkNode_
{
    int v;
    struct LinkNode_*next;
}LinkNode;

int main()
{
    int K, v, count=0;
    LinkNode *pHead=NULL, *pNode, *pTail=NULL, *pDesNode=NULL;
    //����K
    scanf("%d", &K);
    while(1)
    {
        scanf("%d", &v);
        //������ϸ���⣬����д��-1
        if(v<0)
            break;
        //��̬����һ�����
        pNode = (LinkNode*)malloc(sizeof(LinkNode));
        pNode->next = NULL;
        pNode->v = v;
        //�������ǿգ��������β�����ָ��ǰ�´����Ľ��
        if(pTail)
            pTail->next = pNode;
        else//����Ϊ�գ��ѵ�ǰ�������Ϊͷ���
            pHead = pNode;
        //�ƶ�����β�����
        pTail = pNode;
        //������+1
        ++count;
        //���������������K��Ԫ���ˣ���ǰ������K����������ͷ���
        if(count==K)
            pDesNode = pHead;
        else if(count>K) //����������������K����Ŀ����ÿ�ζ�������һ�����
            pDesNode = pDesNode->next;
    }
    //���������K�����ǿ�
    if(pDesNode)
        printf("%d\n", pDesNode->v);
    else
        printf("NULL\n");
    //����ͷ��ڴ�
    pNode = pHead;
    while(pNode)
    {
        pTail = pNode->next;
        free(pNode);
        pNode = pTail;
    }
    return 0;
}
