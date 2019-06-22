#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 1001

//�����������ص㣺������ֵ�ȸ����ֵС��������ֵ�ȸ����ֵ��
//���ȶ���(��С��): �����ֵ����������ֵ��С
//�ѿ�����������K1�Ķ���������������K2�����ȶ���
typedef struct Node_
{
    int K1;
    int K2;
    int left; //���������������
    int right;//���������������
}Node;

//�Ƿ��Ƕ�����������������ֵ�ȸ����ֵС��������ֵ�ȸ����ֵ��
bool IsBinarySearch(Node nodes[], int rootID)
{
    if(rootID==-1)
        return true;
    //������ʹ��һ����ջ�洢��������ţ�������ʹ����һ����ջ�洢���������
    int leftStack[MAX_N], rightStack[MAX_N];
    int leftStackSize=0, rightStackSize=0;
    //�����ֵ
    int rootValue = nodes[rootID].K1;
    int id;

    //�����������������Ч���������Ӻ�
    if(nodes[rootID].left>=0)
        leftStack[leftStackSize++] = nodes[rootID].left;
    while(leftStackSize)
    {
        //����������ջ�е���һ�����Ӻ�
        id = leftStack[--leftStackSize];
        //�����ӺŵĽ��ֵ����С�ڸ����ֵ
        if(nodes[id].K1>rootValue)
            return false;
        //��������ӵ�����
        if(nodes[id].left>=0)
            leftStack[leftStackSize++] = nodes[id].left;
        //��������ӵ��ҽ��
        if(nodes[id].right>=0)
            leftStack[leftStackSize++] = nodes[id].right;
    }

    //�����������������Ч���������Ӻ�
    if(nodes[rootID].right>=0)
        rightStack[rightStackSize++] = nodes[rootID].right;
    while(rightStackSize)
    {
        //����������ջ�е���һ�����Ӻ�
        id = rightStack[--rightStackSize];
        //�����ӺŵĽ��ֵ������ڸ����ֵ
        if(nodes[id].K1<rootValue)
            return false;
        //��������ӵ�����
        if(nodes[id].left>=0)
            rightStack[rightStackSize++] = nodes[id].left;
        //��������ӵ��ҽ��
        if(nodes[id].right>=0)
            rightStack[rightStackSize++] = nodes[id].right;
    }
    return true;
}

int main()
{
    //���н������
    Node nodes[MAX_N];
    int i, N, left, right;
    //Ĭ���ǵѿ�����
    bool bCartisianTree=true;

    scanf("%d", &N);
    //����N�������Ϣ
    for(i=0; i<N; ++i)
        scanf("%d%d%d%d", &nodes[i].K1, &nodes[i].K2, &nodes[i].left, &nodes[i].right);

    //����жϽ���Ƿ����� ����������+��С��
    for(i=0; i<N; ++i)
    {
        left = nodes[i].left;
        right = nodes[i].right;

        //���ȶ���(��С��): ���ֵ����������ֵ��С
        if(left>=0 && nodes[left].K2<nodes[i].K2||
            right>=0 && nodes[right].K2<nodes[i].K2)
        {
            bCartisianTree = false;
            break;
        }

        //���������н��ֵ����ȸ����ֵС
        //���������н��ֵ����ȸ����ֵ��
        //���ܹ��򵥵�д������ӱȸ����ֵС���Ҷ��ӱȸ����ֵ��
        if(!IsBinarySearch(nodes, i))
        {
            bCartisianTree = false;
            break;
        }
    }

    if(bCartisianTree)
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}
