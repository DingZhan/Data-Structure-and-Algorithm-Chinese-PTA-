#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 11

//二叉树节点结构体
struct TreeNode
{
    TreeNode(int vv=0)
    {
        left=right=NULL;
        v = vv;
    }
    int v;  //值
    TreeNode *left; //左儿子节点
    TreeNode *right; //右儿子节点
};

//二叉搜索树类
class Tree
{
public:
    //构造函数
    Tree()
    {
        m_Root=NULL;
    }

    //从临时节点数组构建一棵二叉树
    void BuildTree(int* values, int n)
    {
        //先释放上一棵的内存
        ReleaseTree();
        int i;
        //往树中插入节点
        for(i=0; i<n; ++i)
            InsertNode(m_Root, values[i]);
    }
    //释放整棵树的内存
    void ReleaseTree()
    {
        ReleaseNode(m_Root);
        m_Root = NULL;
    }
    //比较两颗树是否完全一样，这里用DFS方法一一比较每个节点的值，有不一样的则立刻退出
    bool IsSameTree(const Tree& anotherTree)
    {
        //因为是vector，所以是深度遍历
        std::vector<TreeNode*> seeds1, seeds2;
        //如果一棵树为空，而另一棵也为空，则两棵树一样
        if(!m_Root && !anotherTree.m_Root)
            return true;
        //如果一棵树为空，而另一棵不为空，则两棵树不一样
        if(m_Root && !anotherTree.m_Root||
                !m_Root && anotherTree.m_Root)
            return false;
        //如果根的值都不一样，则不需要再遍历了
        if(m_Root->v!=anotherTree.m_Root->v)
            return false;

        //先把两个树根加到堆栈中
        seeds1.push_back(m_Root);
        seeds2.push_back(anotherTree.m_Root);
        TreeNode *pNode1, *pNode2;
        while(!seeds1.empty())
        {
            if(seeds2.empty())
                return false;
            //从栈顶弹出两个树节点
            pNode1 = seeds1.back();
            pNode2 = seeds2.back();
            seeds1.pop_back();
            seeds2.pop_back();

            //比较左子树节点
            if(pNode1->left)
            {
                if(!pNode2->left)
                    return false;
                if(pNode1->left->v!=pNode2->left->v)
                    return false;
                seeds1.push_back(pNode1->left);
                seeds2.push_back(pNode2->left);
            }
            else
            {
                if(pNode2->left)
                    return false;
            }

            //比较右子树节点
            if(pNode1->right)
            {
                if(!pNode2->right)
                    return false;
                if(pNode1->right->v!=pNode2->right->v)
                    return false;
                seeds1.push_back(pNode1->right);
                seeds2.push_back(pNode2->right);
            }
            else
            {
                if(pNode2->right)
                    return false;
            }
        }
        //如果第二棵树还没有遍历完，则两棵树不一样
        if(!seeds2.empty())
            return false;
        //最后，两棵树完全一样
        return true;
    }
private:
    //后续遍历释放节点所有内存 postorder
    void ReleaseNode(TreeNode *node)
    {
        if(!node)
            return;
        ReleaseNode(node->left);
        ReleaseNode(node->right);
        delete node;
    }
    //递归函数：往树节点中插入指定的值，这里node必须是指针的引用或者指针的指针
    void InsertNode(TreeNode *&node,int v)
    {
        //如果当前节点为空，则创建该节点
        if(!node)
        {
            node = new TreeNode(v);
            return;
        }
        //值比当前节点值小，往左走
        if(v<=node->v)
            InsertNode(node->left, v);
        else //值比当前节点值大，往右走
            InsertNode(node->right, v);
    }
public:
    TreeNode *m_Root;
};
int main()
{
    int i, j, N, L;
    int values[MAX_N];
    Tree tree1, tree2;
    while(true)
    {
        cin>>N;
        if(N==0)
            break;
        cin>>L;
        for(i=0; i<N; ++i)
            cin>>values[i];
        tree1.BuildTree(values, N);
        for(j=0; j<L; ++j)
        {
            for(i=0; i<N; ++i)
                cin>>values[i];
            tree2.BuildTree(values, N);
            if(tree1.IsSameTree(tree2))
                cout<<"Yes"<<endl;
            else
                cout<<"No"<<endl;
        }
    }
}
