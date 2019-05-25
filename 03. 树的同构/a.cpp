#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdlib>
using namespace std;

#define MAX_N 11

//从IO读入树的临时节点
struct TempNode
{
    TempNode() {left=right=-1;}
    char v; //值
    int left; //左儿子在数组中的索引号
    int right; //右儿子在数组中的索引号
};

//二叉树节点结构体
struct TreeNode
{
    TreeNode() {left=right=NULL;}
    char v;  //值
    TreeNode *left; //左儿子节点
    TreeNode *right; //右儿子节点
};

//为了从TempNode数组创建二叉树，需要一个中间结构体
struct SeedNode
{
    TreeNode *parent; //当前节点的二叉树父节点
    bool bLeft;//当前节点是否位于二叉树父节点的左子树
    int id; //当前节点在TempNode数组中的索引号
};

//二叉树类
class Tree
{
public:
    //构造函数
    Tree() {m_Root=NULL;}
    //从临时节点数组构建一棵二叉树
    void BuildTree(TempNode* tnodes, int n)
    {
        int i, rootID, oldRootID;
        //循环向上搜索，找到临时的根节点,就用第一个临时节点做种子
        rootID = 0;
        while(true)
        {
            //上一次根节点索引号
            oldRootID = rootID;
            for(i=0; i<n; ++i)
            {
                if(i==rootID)
                    continue;
                //如果当前节点的左儿子或者右儿子是当前根节点，则让当前根节点指向它的父节点
                if(tnodes[i].left==rootID||tnodes[i].right==rootID)
                {
                    rootID = i;
                    break;
                }
            }
            //如果上一次的根节点和这次搜索的根节点索引号一样，则搜索结束
            if(oldRootID==rootID)
                break;
        }

        //释放上一棵树的内存
        ReleaseTree();

        //从临时根节点开始，创建二叉树
        //用DFS建树
        std::vector<SeedNode> seedIDs;
        SeedNode seedNode;
        seedNode.parent = NULL; //根节点没有父节点
        seedNode.id = rootID; //根节点在TempNode数组中的索引
        //加入DFS栈
        seedIDs.push_back(seedNode);
        while(!seedIDs.empty())
        {
            //从栈里弹出一个节点
            seedNode = seedIDs.back();
            seedIDs.pop_back();

            //创建树节点
            TreeNode* node = new TreeNode();
            //如果根没有被初始化过，则第一个节点是根
            if(!m_Root)
                m_Root = node;
            //设置当前节点的值
            node->v = tnodes[seedNode.id].v;
            //如果当前节点有父亲，则设置父节点的左儿子或右儿子指针
            if(seedNode.parent)
            {
                //设置父节点的左儿子
                if(seedNode.bLeft)
                    seedNode.parent->left = node;
                else
                    seedNode.parent->right = node;
            }
            //如果当前节点有左儿子
            if(tnodes[seedNode.id].left>=0)
            {
                //加入左儿子到DFS栈
                SeedNode leftSeed;
                leftSeed.parent = node;
                leftSeed.id = tnodes[seedNode.id].left;
                leftSeed.bLeft = true;
                seedIDs.push_back(leftSeed);
            }
            //如果当前节点有右儿子
            if(tnodes[seedNode.id].right>=0)
            {
                //加入右儿子到DFS栈
                SeedNode rightSeed;
                rightSeed.parent = node;
                rightSeed.id = tnodes[seedNode.id].right;
                rightSeed.bLeft = false;
                seedIDs.push_back(rightSeed);
            }
        }
    }
    //用BFS方式同步遍历两棵树，只要发现有不同步的现象就退出
    bool IsHomogeneous(const Tree& anotherTree)
    {
        //BFS需要使用队列，这两个队列分别对应树1和树2
        std::queue<TreeNode*> seeds1, seeds2;
        TreeNode *s1, *s2;
        //先把两个树根塞入队列
        seeds1.push(m_Root);
        seeds2.push(anotherTree.m_Root);
        while(!seeds1.empty())
        {
            //如果队列1不空，而队列2空，所以肯定不同构
            if(seeds2.empty())
                return false;
            s1 = seeds1.front();
            s2 = seeds2.front();
            seeds1.pop();
            seeds2.pop();
            //如果两个节点的值不相同，则肯定不同构
            if(s1->v!=s2->v)
                return false;
            if(s1->left&&s1->right)
            {
                //如果s1有两个儿子，而s2没有两个儿子，则肯定不同构
                if(!s2->left || !s2->right)
                    return false;
                if(s1->left->v==s2->left->v)
                {
                    seeds1.push(s1->left);
                    seeds1.push(s1->right);
                    seeds2.push(s2->left);
                    seeds2.push(s2->right);
                }
                else if(s1->left->v==s2->right->v)
                {
                    seeds1.push(s1->left);
                    seeds1.push(s1->right);
                    seeds2.push(s2->right);
                    seeds2.push(s2->left);
                }
                else
                    return false;
            }
            else if(s1->left)
            {
                if(s2->left && s2->right)
                    return false;
                if(!s2->left && !s2->right)
                    return false;
                if(s2->left && s1->left->v == s2->left->v)
                {
                    seeds1.push(s1->left);
                    seeds2.push(s2->left);
                }
                else if(s2->right && s1->left->v==s2->right->v)
                {
                    seeds1.push(s1->left);
                    seeds2.push(s2->right);
                }
                else
                    return false;
            }
            else if(s1->right)
            {
                if(s2->left && s2->right)
                    return false;
                if(!s2->left && !s2->right)
                    return false;
                if(s2->left && s1->right->v == s2->left->v)
                {
                    seeds1.push(s1->right);
                    seeds2.push(s2->left);
                }
                else if(s2->right && s1->right->v==s2->right->v)
                {
                    seeds1.push(s1->right);
                    seeds2.push(s2->right);
                }
                else
                    return false;
            }
            else
            {
                if(s2->left || s2->right)
                    return false;
            }
        }
        //此时队列1为空，而如果队列2不为空，所以肯定不同构
        if(!seeds2.empty())
            return false;
        return true;
    }

    //释放整棵树的内存
    void ReleaseTree()
    {
        ReleaseNode(m_Root);
        m_Root = NULL;
    }
    //调试函数，用BSF打印树节点
    void BFSPrint()
    {
        std::queue<TreeNode*> seeds;
        if(m_Root)
            seeds.push(m_Root);
        TreeNode *pNode;
        while(!seeds.empty())
        {
            pNode = seeds.front();
            seeds.pop();
            cout<<pNode->v<<" ";
            if(pNode->left)
                seeds.push(pNode->left);
            if(pNode->right)
                seeds.push(pNode->right);
        }
        cout<<"\n";
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
public:
    TreeNode *m_Root;
};
int main()
{
    TempNode tnodes[MAX_N];
    int i, n;
    char v;
    std::string leftID, rightID;
    Tree tree1, tree2;
    cin>>n;
    for(i=0; i<n; ++i)
    {
        cin>>v>>leftID>>rightID;
        tnodes[i].v = v;
        tnodes[i].left = tnodes[i].right = -1;
        if(leftID!="-")
            tnodes[i].left = atoi(leftID.c_str());
        if(rightID!="-")
            tnodes[i].right = atoi(rightID.c_str());
    }
    tree1.BuildTree(tnodes, n);

    cin>>n;
    for(i=0; i<n; ++i)
    {
        cin>>v>>leftID>>rightID;
        tnodes[i].v = v;
        tnodes[i].left = tnodes[i].right = -1;
        if(leftID!="-")
            tnodes[i].left = atoi(leftID.c_str());
        if(rightID!="-")
            tnodes[i].right = atoi(rightID.c_str());
    }
    tree2.BuildTree(tnodes, n);

    if(tree1.IsHomogeneous(tree2))
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;
}
