#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

//树节点结构体
struct TreeNode
{
    //目录或文件名，是否是目录或文件
    TreeNode(const string& name, bool bDir)
    {
        this->name = name;
        this->bDir = bDir;
        //初始化左右子树都为NULL
        left = right = NULL;
    }
    //左儿子，右兄弟
    TreeNode *left, *right;
    //目录或文件名
    string name;
    //该结点是否是目录
    bool bDir;
};

//结点比较函数，按字符串字典序排。目录名与目录名比较，文件名与文件名比较
bool CompareNode(const TreeNode* a, const TreeNode* b)
{
    return a->name<b->name;
}

//二叉树类（目录树）
struct Tree
{
public:
    Tree()
    {
        //初始化树根为NULL
        m_Root = NULL;
    }
    //插入一个目录或文件结点
    void InsertNode(const string& name)
    {
        //如果根为空，初始化树根为root
        if(!m_Root)
            InitTree();
        //pParent是父结点
        TreeNode *pParent = m_Root;
        string curName = name, dirName;
        size_t pos;
        //levelCount是当前路径层数
        int levelCount=0;

        //根据路径分隔符一层层剥离目录
        while(true)
        {
            //查找路径分隔符
            pos = curName.find_first_of('\\');
            //没找到分隔符，则当前是文件，插入该文件名到parent结点下
            if(pos==string::npos)
            {
                InsertNode(pParent, curName, false);
                break;
            }
            else if(pos==curName.size()-1)//分隔符是最后一个字符，所以是路径，插入该路径结点
            {
                //把最后一个分隔符删除
                curName.erase(curName.end()-1);
                InsertNode(pParent, curName, true);
                break;
            }
            else
            {
                //得到当前路径名
                dirName.assign(curName.begin(), curName.begin()+pos);
                //插入该路径，同时获得当前路径结点
                pParent = InsertNode(pParent, dirName, true);
                //累加当前路径层数
                ++levelCount;
                //剥离该路径，继续下一级目录
                curName.erase(curName.begin(), curName.begin()+pos+1);
            }
        }
    }
    //在pParent结点下插入文件或路径
    TreeNode* InsertNode(TreeNode *pParent, const string& name, bool bDir)
    {
        if(!pParent)
            return NULL;
        //son是pParent第一个儿子结点,pPre是遍历的前一个结点
        TreeNode *son = pParent->left, *pPre=NULL;
        //当儿子不为空
        while(son)
        {
            //如果该路径或文件已经存在pParent结点下
            if(son->name==name && son->bDir==bDir)
                return son;
            //设置前一个结点
            pPre = son;
            //往兄弟结点遍历
            son = son->right;
        }
        //分配一个结点
        TreeNode* pNode = new TreeNode(name, bDir);
        //如果前一个结点为空，则说明pParent下还没有儿子
        if(!pPre)
            pParent->left = pNode;
        else//否则将pPre的右兄弟设置为当前创建的结点
            pPre->right = pNode;
        return pNode;
    }
    //初始化树
    void InitTree()
    {
        //如果树非空，则先释放树内存
        if(m_Root)
            FreeTree();
        //创建根结点
        m_Root = new TreeNode("root", true);
    }
    //释放目录树内存
    void FreeTree()
    {
        //调用私有递归函数
        FreeTree(m_Root);
        //将树根重置为NULL
        m_Root = NULL;
    }
    //打印目录树
    void Print()
    {
        //调用私有递归打印函数，0是当前目录层数，用来控制空格打印数量
        PrintTree(m_Root, 0);
    }
private:
    //后序遍历释放树内存
    void FreeTree(TreeNode* pNode)
    {
        if(!pNode)
            return;
        FreeTree(pNode->left);
        FreeTree(pNode->right);
        delete pNode;
    }
    //递归打印目录树，levelCount是当前目录层次数，用来控制空格的打印数目
    void PrintTree(TreeNode* pParent, int levelCount)
    {
        if(!pParent)
            return;
        std::vector<TreeNode*> fileNodes;
        std::vector<TreeNode*> dirNodes;
        TreeNode *pNode = pParent->left;
        int i;
        //根据当前目录层次数，打印两倍的空格
        for(i=0; i<levelCount; ++i)
            cout<<"  ";
        //打印路径或文件名
        cout<<pParent->name<<endl;
        //如果不是路径则返回
        if(!pParent->bDir)
            return;
        //得到当前路径下所有的文件名和目录名，放在不同的数组里
        while(pNode)
        {
            if(pNode->bDir)
                dirNodes.push_back(pNode);
            else
                fileNodes.push_back(pNode);
            pNode = pNode->right;
        }

        //对目录名进行字典排序
        sort(dirNodes.begin(), dirNodes.end(), CompareNode);
        //递归调用打印
        for(i=0; i<dirNodes.size(); ++i)
            PrintTree(dirNodes[i], levelCount+1);

        //对文件名进行字典排序
        sort(fileNodes.begin(), fileNodes.end(), CompareNode);
        //递归调用打印
        for(i=0; i<fileNodes.size(); ++i)
            PrintTree(fileNodes[i], levelCount+1);
    }

private:
    //树根
    TreeNode *m_Root;
};

int main()
{
    //关闭I/O同步
    std::ios::sync_with_stdio(false);
    int N, i;
    string name;
    //定义目录树
    Tree tree;

    //用getline主要吃掉最后的回车键
    getline(cin, name);
    //得到N条记录
    N = atoi(name.c_str());

    //得到N条记录
    for(i=0; i<N; ++i)
    {
        getline(cin, name);
        //把路径或文件插入树
        tree.InsertNode(name);
    }
    //打印树
    tree.Print();
    return 0;
}
