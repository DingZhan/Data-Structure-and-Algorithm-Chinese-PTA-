#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

//定义树结点结构体
struct TreeNode
{
    //值
    int v;
    //左右子结点
    TreeNode *left, *right;
    //构造函数
    TreeNode(int value)
    {
        v = value;
        left = right = NULL;
    }
};

//定义树类
class Tree
{
public:
    //构造函数
    Tree() {m_Root=NULL;}
    //往二叉搜索树添加结点
    void AddNode(int value)
    {
        AddNode(m_Root, value);
    }
    //前序遍历返回的字符串
    string PreOrder()
    {
        string result;
        bool bFirst=true;
        //调用另一个递归前序遍历的私有函数
        PreOrder(m_Root, bFirst, result);
        return result;
    }
    //后序遍历返回的字符串
    string PostOrder()
    {
        string result;
        bool bFirst=true;
        //调用另一个递归后序遍历的私有函数
        PostOrder(m_Root, bFirst, result);
        return result;
    }
    //构造二叉搜索树的镜像树
    void Mirror(Tree& mirrorTree)
    {
        //先释放镜像树原来的内存
        mirrorTree.FreeTree();
        //如果当前树为空直接返回
        if(!m_Root)
            return;
        //调用私有的递归镜像函数
        MirrorNode(m_Root, mirrorTree.m_Root);
    }
    //释放树内存
    void FreeTree()
    {
        //调用私有递归后序遍历的删除函数
        Free(m_Root);
        //把根节点重置为NULL
        m_Root = NULL;
    }
private:
    //在二叉搜索树下，当前结点下添加新结点，这里一定是指针的引用或者二级指针
    void AddNode(TreeNode *&root, int value)
    {
        //如果当前结点已经为NULL，则就在这个结点位置创建新结点
        if(!root)
        {
            root = new TreeNode(value);
            return;
        }
        //如果新结点值比当前结点值小，往左走
        if(value<root->v)
            AddNode(root->left, value);
        else //如果新结点值大于等于当前结点值，往右走
            AddNode(root->right, value);
    }

    //前序遍历递归函数，返回的前序遍历后的字符串
    void PreOrder(TreeNode *node, bool& bFirst, string& result)
    {
        if(!node)
            return;
        ostringstream oss;
        //如果不是第一次打印，则先打印个空格
        if(!bFirst)
            oss<<" ";
        //设置非第一次打印标记
        bFirst = false;
        oss<<node->v;
        result+=oss.str();
        //遍历左子树
        if(node->left)
            PreOrder(node->left, bFirst, result);
        //遍历右子树
        if(node->right)
            PreOrder(node->right, bFirst, result);
    }

    //后序遍历递归函数，返回的后序遍历后的字符串
    void PostOrder(TreeNode *node, bool& bFirst, string& result)
    {
        if(!node)
            return;
        //遍历左子树
        if(node->left)
            PostOrder(node->left, bFirst, result);
        //遍历右子树
        if(node->right)
            PostOrder(node->right, bFirst, result);
        ostringstream oss;
        //如果不是第一次打印，则先打印个空格
        if(!bFirst)
            oss<<" ";
        oss<<node->v;
        result+=oss.str();
        //设置非第一次打印标记
        bFirst=false;
    }
    //后续遍历释放内存
    void Free(TreeNode* node)
    {
        if(!node)
            return;
        Free(node->left);
        Free(node->right);
        delete node;
    }
    //镜像结点的递归函数,srcNode是源树结点，mirrorNode是对应的镜像树的镜像结点
    //这里mirrorNode必须是指针的引用，或者二级指针
    void MirrorNode(const TreeNode* srcNode, TreeNode *&mirrorNode)
    {
        if(!srcNode)
            return;
        //创建镜像结点
        mirrorNode = new TreeNode(srcNode->v);
        //srcNode的左子树镜像到mirroNode的右子树
        MirrorNode(srcNode->left, mirrorNode->right);
        //srcNode的右子树镜像到mirroNode的左子树
        MirrorNode(srcNode->right, mirrorNode->left);
    }

private:
    //树根结点
    TreeNode *m_Root;
};

int main()
{
    Tree srcTree, mirrorTree;
    int i, N, v;
    string preStr, str, preStr1,preStr2, postStr;
    istringstream iss;

    //不直接使用cin>>，主要是最后有个回车键要吃掉，所以干脆一次读一行
    std::getline(std::cin, str);
    //得到N
    N = atoi(str.c_str());
    //得到待检测的前序遍历字符串
    std::getline(std::cin, preStr);
    //把该前序遍历字符串打包到istringstream流，准备读取一个个整数值
    iss.str(preStr);
    for(i=0; i<N; ++i)
    {
        //得到当前值
        iss>>v;
        //把该结点加入到搜索二叉树
        srcTree.AddNode(v);
    }
    //对二叉搜索树srcTree做镜像，当然mirrorTree不再是二叉搜索树
    srcTree.Mirror(mirrorTree);
    //得到srcTree的前序遍历结果字符串
    preStr1 = srcTree.PreOrder();
    //得到镜像树的前序遍历结果字符串
    preStr2 = mirrorTree.PreOrder();

    //如果srcTree的前序遍历结果字符串和输入的一样
    if(preStr1==preStr)
    {
        cout<<"YES\n";
        postStr = srcTree.PostOrder();
        cout<<postStr<<"\n";
    }
    //如果镜像树的前序遍历结果字符串和输入的一样
    else if(preStr2==preStr)
    {
        cout<<"YES\n";
        postStr = mirrorTree.PostOrder();
        cout<<postStr<<"\n";
    }
    else //否则都不一样
        cout<<"NO\n";

    return 0;
}
