#include <iostream>
#include <queue>

/*一根木头锯成两段，相当于从一个节点分配出两个子节点；而
最终分割出来的木头相当于树中的叶结点，木头越短，它的层次深度（Huffman符号表达长度）可以越深;
*/
/*因此这是Huffman编码问题，通过创建最小堆构建Huffman树,
通过每次把权值最小的两个二叉树合并，
这里使用优先队列priority_queue作为最小堆
Huffman具体细节参看<数据结构>慕课Huffman树与Huffman编码
*/
/*和上一个方法不同，这里我们真的建立一棵Huffman树,
然后用递归方法把非叶节点的值累加一下，验证这棵树*/
using namespace std;
//树结点
struct TreeNode
{
    int v; //节点值
	TreeNode *left; //左子树节点
	TreeNode *right; //右子树节点
	//构造函数
	TreeNode(int vv)
	{
	    v = vv;
	    left = right = NULL;
	}
};
//这里定义仿函数,比较两个节点值
struct CompareTreeNode
{
    bool operator ()(const TreeNode* a,const TreeNode *b)
    {
        return a->v>b->v;
    }
};

//用递归方法累加Huffman树非叶节点的值，该值就是目标值
int SumNonLeafNode(TreeNode* node)
{
    //如果是叶结点返回0
    if(!node || (node->left == NULL && node->right ==NULL))
        return 0;
    //累加左右子树和本身的值
    return node->v+SumNonLeafNode(node->left)+SumNonLeafNode(node->right);
}
//后续遍历删除树内存
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
    //这里使用优先队列作为最小堆，传入的是树节点指针，因为我们要真的建立一颗Huffman树
    priority_queue<TreeNode*, std::vector<TreeNode*>, CompareTreeNode> minHeap;
    //sum就是Huffman树中非叶结点权值的累加和
    int i, N, sum=0, v;
    TreeNode *root, *node, *left, *right;
    //读入N
    cin>>N;
    //读入N块最终长度的木头
    for(i=0; i<N; ++i)
    {
        cin>>v;
        node = new TreeNode(v);
        //把该木头加入到最小堆中
        minHeap.push(node);
    }

    //或者循环条件改成 while(minHeap.size()!=1)
    for(i=0; i<N-1; ++i)
    {
        //弹出两个最短长度的木头
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        //把两个最短长度的木头的和再次加入到最小堆中
        node = new TreeNode(left->v+right->v);
        node->left = left;
        node->right = right;
        minHeap.push(node);
        //这里故意不直接计算结果，我们通过遍历Huffman树计算该值
        //累加两块木头的长度
//        sum+=a+b;
    }
    //最后留在最小堆中的节点就是树的根节点
    root = minHeap.top();
    //计算非叶节点值的和
    sum = SumNonLeafNode(root);
    //释放树
    FreeTree(root);
    //打印结果
    cout<<sum<<endl;
    return 0;
}
