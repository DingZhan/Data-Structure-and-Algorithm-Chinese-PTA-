#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 1001

//二叉搜索树特点：左子树值比根结点值小，右子树值比根结点值大
//优先队列(最小堆): 根结点值比左、右子树值都小
//笛卡尔树：关于K1的二叉搜索树，关于K2的优先队列
typedef struct Node_
{
    int K1;
    int K2;
    int left; //左子树结点索引号
    int right;//右子树结点索引号
}Node;

//是否是二叉搜索树，左子树值比根结点值小，右子树值比根结点值大
bool IsBinarySearch(Node nodes[], int rootID)
{
    if(rootID==-1)
        return true;
    //左子树使用一个堆栈存储结点索引号，右子树使用另一个堆栈存储结点索引号
    int leftStack[MAX_N], rightStack[MAX_N];
    int leftStackSize=0, rightStackSize=0;
    //根结点值
    int rootValue = nodes[rootID].K1;
    int id;

    //如果左子树索引号有效，加入种子号
    if(nodes[rootID].left>=0)
        leftStack[leftStackSize++] = nodes[rootID].left;
    while(leftStackSize)
    {
        //从左子树堆栈中弹出一个种子号
        id = leftStack[--leftStackSize];
        //该种子号的结点值必须小于根结点值
        if(nodes[id].K1>rootValue)
            return false;
        //加入该种子的左结点
        if(nodes[id].left>=0)
            leftStack[leftStackSize++] = nodes[id].left;
        //加入该种子的右结点
        if(nodes[id].right>=0)
            leftStack[leftStackSize++] = nodes[id].right;
    }

    //如果右子树索引号有效，加入种子号
    if(nodes[rootID].right>=0)
        rightStack[rightStackSize++] = nodes[rootID].right;
    while(rightStackSize)
    {
        //从右子树堆栈中弹出一个种子号
        id = rightStack[--rightStackSize];
        //该种子号的结点值必须大于根结点值
        if(nodes[id].K1<rootValue)
            return false;
        //加入该种子的左结点
        if(nodes[id].left>=0)
            rightStack[rightStackSize++] = nodes[id].left;
        //加入该种子的右结点
        if(nodes[id].right>=0)
            rightStack[rightStackSize++] = nodes[id].right;
    }
    return true;
}

int main()
{
    //所有结点数组
    Node nodes[MAX_N];
    int i, N, left, right;
    //默认是笛卡尔树
    bool bCartisianTree=true;

    scanf("%d", &N);
    //读入N个结点信息
    for(i=0; i<N; ++i)
        scanf("%d%d%d%d", &nodes[i].K1, &nodes[i].K2, &nodes[i].left, &nodes[i].right);

    //逐个判断结点是否满足 搜索二叉树+最小堆
    for(i=0; i<N; ++i)
    {
        left = nodes[i].left;
        right = nodes[i].right;

        //优先队列(最小堆): 结点值比左、右子树值都小
        if(left>=0 && nodes[left].K2<nodes[i].K2||
            right>=0 && nodes[right].K2<nodes[i].K2)
        {
            bCartisianTree = false;
            break;
        }

        //左子树所有结点值必须比根结点值小
        //右子树所有结点值必须比根结点值大
        //不能够简单地写成左儿子比根结点值小，右儿子比根结点值大
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
