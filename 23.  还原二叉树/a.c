
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 52

//定义树结点结构体
typedef struct Node_
{
    char v;
    struct Node_ *left, *right;
}Node;

//根据前序遍历和中序遍历结果构建二叉树，最后一个参数要传入一个二级指针，表示当前子树得根结点
void BuildTree(char preStr[], char inStr[], int n, Node **root)
{
    //如果当前子树为空
    if(n==0)
        return;
    //前序遍历的第一个元素就是当前子树的根结点
    //查找根节点在中序遍历中的位置，从而将中序遍历分成左右两棵子树
    int pos = strchr(inStr, preStr[0])-inStr;
    //创建根结点
    *root = (Node*)malloc(sizeof(Node));
    (*root)->v = preStr[0];
    (*root)->left = (*root)->right = NULL;
    //分解左右子树的时候，需要确认划分好左右子树
    //递归创建左子树
    BuildTree(preStr+1, inStr, pos, &((*root)->left));
    //递归创建右子树
    BuildTree(preStr+pos+1, inStr+pos+1, n-pos-1, &((*root)->right));
}

//树的高度：左右子树较高的那个高度值再加1
int GetHeight(Node* root)
{
    if(!root)
        return 0;
    int h1 = GetHeight(root->left);
    int h2 = GetHeight(root->right);
    if(h1>h2)
        return h1+1;
    else
        return h2+1;
}

//用后续遍历释放树内存
void FreeTree(Node *root)
{
    if(!root)
        return;
    FreeTree(root->left);
    FreeTree(root->right);
    free(root);
}

int main()
{
    char inStr[MAX_N], preStr[MAX_N];
    int i, N, h;
    Node *root=NULL;

    scanf("%d", &N);
    //过滤掉第一行的回车键
    fgets(preStr, MAX_N, stdin);
    //得到先序遍历
    fgets(preStr, MAX_N, stdin);
    //fgets会多得到一个\n，所以得手动删除
    preStr[N] = '\0';
    //得到中序遍历
    fgets(inStr, MAX_N, stdin);
    //fgets会多得到一个\n，所以得手动删除
    inStr[N] = '\0';

    //创建二叉树
    BuildTree(preStr, inStr, N, &root);
    //得到高度
    h = GetHeight(root);
    printf("%d\n", h);
    //释放树
    FreeTree(root);

    return 0;
}
