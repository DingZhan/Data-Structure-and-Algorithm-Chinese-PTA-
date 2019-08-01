#include <iostream>
#include <queue>

/*һ��ľͷ������Σ��൱�ڴ�һ���ڵ����������ӽڵ㣻��
���շָ������ľͷ�൱�����е�Ҷ��㣬ľͷԽ�̣����Ĳ����ȣ�Huffman���ű�ﳤ�ȣ�����Խ��;
*/
/*�������Huffman�������⣬ͨ��������С�ѹ���Huffman��,
ͨ��ÿ�ΰ�Ȩֵ��С�������������ϲ���
����ʹ�����ȶ���priority_queue��Ϊ��С��
Huffman����ϸ�ڲο�<���ݽṹ>Ľ��Huffman����Huffman����
*/
/*����һ��������ͬ������������Ľ���һ��Huffman��,
Ȼ���õݹ鷽���ѷ�Ҷ�ڵ��ֵ�ۼ�һ�£���֤�����*/
using namespace std;
//�����
struct TreeNode
{
    int v; //�ڵ�ֵ
	TreeNode *left; //�������ڵ�
	TreeNode *right; //�������ڵ�
	//���캯��
	TreeNode(int vv)
	{
	    v = vv;
	    left = right = NULL;
	}
};
//���ﶨ��º���,�Ƚ������ڵ�ֵ
struct CompareTreeNode
{
    bool operator ()(const TreeNode* a,const TreeNode *b)
    {
        return a->v>b->v;
    }
};

//�õݹ鷽���ۼ�Huffman����Ҷ�ڵ��ֵ����ֵ����Ŀ��ֵ
int SumNonLeafNode(TreeNode* node)
{
    //�����Ҷ��㷵��0
    if(!node || (node->left == NULL && node->right ==NULL))
        return 0;
    //�ۼ����������ͱ����ֵ
    return node->v+SumNonLeafNode(node->left)+SumNonLeafNode(node->right);
}
//��������ɾ�����ڴ�
void FreeTree(TreeNode *node)
{
    if(!node)
        return;
    FreeTree(node->left);
    FreeTree(node->right);
    delete node;
}

int main()
{
    //����ʹ�����ȶ�����Ϊ��С�ѣ�����������ڵ�ָ�룬��Ϊ����Ҫ��Ľ���һ��Huffman��
    priority_queue<TreeNode*, std::vector<TreeNode*>, CompareTreeNode> minHeap;
    //sum����Huffman���з�Ҷ���Ȩֵ���ۼӺ�
    int i, N, sum=0, v;
    TreeNode *root, *node, *left, *right;
    //����N
    cin>>N;
    //����N�����ճ��ȵ�ľͷ
    for(i=0; i<N; ++i)
    {
        cin>>v;
        node = new TreeNode(v);
        //�Ѹ�ľͷ���뵽��С����
        minHeap.push(node);
    }

    //����ѭ�������ĳ� while(minHeap.size()!=1)
    for(i=0; i<N-1; ++i)
    {
        //����������̳��ȵ�ľͷ
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        //��������̳��ȵ�ľͷ�ĺ��ٴμ��뵽��С����
        node = new TreeNode(left->v+right->v);
        node->left = left;
        node->right = right;
        minHeap.push(node);
        //������ⲻֱ�Ӽ�����������ͨ������Huffman�������ֵ
        //�ۼ�����ľͷ�ĳ���
//        sum+=a+b;
    }
    //���������С���еĽڵ�������ĸ��ڵ�
    root = minHeap.top();
    //�����Ҷ�ڵ�ֵ�ĺ�
    sum = SumNonLeafNode(root);
    //�ͷ���
    FreeTree(root);
    //��ӡ���
    cout<<sum<<endl;
    return 0;
}
