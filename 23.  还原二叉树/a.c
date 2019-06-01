
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 52

//���������ṹ��
typedef struct Node_
{
    char v;
    struct Node_ *left, *right;
}Node;

//����ǰ��������������������������������һ������Ҫ����һ������ָ�룬��ʾ��ǰ�����ø����
void BuildTree(char preStr[], char inStr[], int n, Node **root)
{
    //�����ǰ����Ϊ��
    if(n==0)
        return;
    //ǰ������ĵ�һ��Ԫ�ؾ��ǵ�ǰ�����ĸ����
    //���Ҹ��ڵ�����������е�λ�ã��Ӷ�����������ֳ�������������
    int pos = strchr(inStr, preStr[0])-inStr;
    //���������
    *root = (Node*)malloc(sizeof(Node));
    (*root)->v = preStr[0];
    (*root)->left = (*root)->right = NULL;
    //�ֽ�����������ʱ����Ҫȷ�ϻ��ֺ���������
    //�ݹ鴴��������
    BuildTree(preStr+1, inStr, pos, &((*root)->left));
    //�ݹ鴴��������
    BuildTree(preStr+pos+1, inStr+pos+1, n-pos-1, &((*root)->right));
}

//���ĸ߶ȣ����������ϸߵ��Ǹ��߶�ֵ�ټ�1
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

//�ú��������ͷ����ڴ�
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
    //���˵���һ�еĻس���
    fgets(preStr, MAX_N, stdin);
    //�õ��������
    fgets(preStr, MAX_N, stdin);
    //fgets���õ�һ��\n�����Ե��ֶ�ɾ��
    preStr[N] = '\0';
    //�õ��������
    fgets(inStr, MAX_N, stdin);
    //fgets���õ�һ��\n�����Ե��ֶ�ɾ��
    inStr[N] = '\0';

    //����������
    BuildTree(preStr, inStr, N, &root);
    //�õ��߶�
    h = GetHeight(root);
    printf("%d\n", h);
    //�ͷ���
    FreeTree(root);

    return 0;
}
