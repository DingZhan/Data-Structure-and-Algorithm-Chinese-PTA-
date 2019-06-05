#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <assert.h>

using namespace std;

//树节点类
class TreeNode
{
public:
    TreeNode(const string& name)
    {
        left = right = parent = NULL;
        this->name = name;
    }
    //左儿子，右兄弟, 父节点指针
    TreeNode *left, *right, *parent;
    //值:名字
    string name;
};

//二叉树类
class Tree
{
public:
    //构造函数，根节点为NULL
    Tree() {m_Root=NULL;}
    //添加根结点
    TreeNode* AddRoot(const string& name)
    {
        //先释放之前的树内存
        FreeTree();
        //创建根结点
        m_Root =  new TreeNode(name);
        return m_Root;
    }

    //在parent结点下插入儿子结点
    TreeNode* InsertChild(TreeNode *parent, const std::string& childName)
    {
        //第一个儿子结点
        TreeNode *child = parent->left;
        //创建当前儿子结点
        TreeNode *newNode =  new TreeNode(childName);
        //设置儿子结点的父结点
        newNode->parent = parent;
        //如果当前还没有儿子，则把这个新结点设置为第一个儿子
        if(!child)
            parent->left = newNode;
        else
        {
            //找到最后一个儿子，把新结点挂在最后一个儿子的右边
            while(child->right)
                child = child->right;
            child->right = newNode;
        }
        return newNode;
    }

    //插入兄弟结点
    TreeNode* InsertSibling(TreeNode *src, const string& name)
    {
        //找到该结点右边的最后一个兄弟
        while(src->right)
            src = src->right;
        //创建新结点
        TreeNode *newNode =  new TreeNode(name);
        //把该结点挂在最右边的结点
        src->right = newNode;
        //设置新结点的父亲
        newNode->parent = src->parent;
        return newNode;
    }

    //用DFS搜索name对应的结点
    TreeNode* Find(const string& name)
    {
        stack<TreeNode*> seeds;
        TreeNode *seed;
        //树空直接返回NULL
        if(!m_Root)
            return NULL;
        //加入根结点
        seeds.push(m_Root);
        while(!seeds.empty())
        {
            //弹出一个种子
            seed = seeds.top();
            seeds.pop();
            //如果找到，则返回
            if(seed->name==name)
                return seed;
            //加入左儿子
            if(seed->left)
                seeds.push(seed->left);
            //加入右儿子
            if(seed->right)
                seeds.push(seed->right);
        }
        return NULL;
    }

    //chilename是否是parentname的儿子
    bool IsChild(const string& parentname, const string& childname)
    {
        //找到父节点
        TreeNode* parent = Find(parentname);
        //如果没找到这个结点，则直接返回NULL
        if(!parent)
            return false;
        TreeNode* child = parent->left;
        //遍历父节点的所有儿子
        while(child)
        {
            //找到就返回
            if(child->name==childname)
                return true;
            child = child->right;
        }
        return false;
    }
    //判断siblingname是否和name是兄弟关系
    bool IsSibling(const string& siblingname, const string& name)
    {
        //找到siblingname的结点
        TreeNode*sibling = Find(siblingname);
        //如果没找到这个结点，则直接返回NULL
        if(!sibling)
            return false;
        //如果sibling是根结点，则也必须返回NULL
        if(!sibling->parent)
            return false;
        //从第一个兄弟结点开始遍历
        TreeNode* node = sibling->parent->left;
        while(node)
        {
            //找到就返回
            if(node->name==name)
                return true;
            node = node->right;
        }
        return false;
    }
    //判断ancestorName是否是childname的祖先
    bool IsAncestor(const string& childname, const string& ancestorName)
    {
        //因为有parent结点，所以我们从下往上找
        //找到childname结点
        TreeNode*child = Find(childname);
        //如果没找到则返回
        if(!child)
            return false;
        //开始往上找
        TreeNode* node = child->parent;
        while(node)
        {
            if(node->name==ancestorName)
                return true;
            //一直往上找
            node = node->parent;
        }
        return false;
    }

    //释放树内存
    void FreeTree()
    {
        Free(m_Root);
        m_Root = NULL;
    }
private:
    //后序遍历释放树内存
    void Free(TreeNode *root)
    {
        if(!root)
            return;
        Free(root->left);
        Free(root->right);
        delete root;
    }
public:
    TreeNode *m_Root;
};

//定义一个文字结点结构体
struct TextNode
{
    //缩进空格数
    int indent;
    //名字
    string name;
    //绑定的TreeNode结构，也就是当前TextNode对应的TreeNode结点
    TreeNode *node;
    TextNode()
    {
        node = NULL;
    }
};

int main()
{
    int i, j, N, M;
    string name, str, name1, name2, keyword;
    istringstream iss;
    size_t pos;
    Tree tree;
    TreeNode *node;
    //TextNode结构体栈，用来判断是否插入父子结点、兄弟结点
    stack<TextNode> indentNames;
    TextNode tn;

    //得到一行输入
    std::getline(cin, str);
    iss.clear();
    iss.str(str);
    //读入家谱行数和判断语句个数
    iss>>N>>M;

    //读入家谱
    for(i=0; i<N; ++i)
    {
        //得到一行家谱
        std::getline(cin, str);
        //计算前置空格数
        pos = str.find_first_not_of(' ');
        //得到名字
        name.assign(str.begin()+pos, str.end());
 //       cout<<"Test name: "<<name<<endl;
        //创建根结点
        if(i==0)
        {
            //在数上创建根结点，同时把该结点保存在文本结点中
            tn.node = tree.AddRoot(name);
            tn.name = name;
            tn.indent = pos;
            //把文本结点加入栈
            indentNames.push(tn);
            continue;
        }
        //得到上一个文本结点
        TextNode lastTN = indentNames.top();

        //如果两个缩进是一样的，所以是兄弟
        if(lastTN.indent==pos)
        {
            //插入兄弟结点
            node = tree.InsertSibling(lastTN.node, name);
            tn.name = name;
            tn.node = node;
            tn.indent = pos;
            //加入本文节点到栈
            indentNames.push(tn);
        }
        //缩进更多，所以是上一个结点的第一个儿子
        else if(lastTN.indent<pos)
        {
            node = tree.InsertChild(lastTN.node, name);
            tn.name = name;
            tn.node = node;
            tn.indent = pos;
            indentNames.push(tn);
        }
        else//上一个结点和他所有兄弟都要从栈里弹出来，因为当前结点是他们的叔叔、叔伯辈
        {
            //弹出上一个结点
            indentNames.pop();
            while(!indentNames.empty())
            {
                //弹出结点，直到碰到了同辈结点
                if(indentNames.top().indent==pos)
                    break;
                indentNames.pop();
            }
            //加些断言
            assert(!indentNames.empty());
            //得到已加入的上一个兄弟结点
            lastTN = indentNames.top();
            assert(lastTN.indent==pos);
            //插入当前的兄弟结点
            node = tree.InsertSibling(lastTN.node, name);
            tn.name = name;
            tn.node = node;
            tn.indent = pos;
            //把该结点加入栈
            indentNames.push(tn);
        }
    }

    //读取判断语句
    /*
X is a child of Y
X is the parent of Y
X is a sibling of Y
X is a descendant of Y
X is an ancestor of Y
*/
    for(i=0; i<M; ++i)
    {
        //得到一行语句
        getline(std::cin, str);
        iss.clear();
        iss.str(str);
        //用流方式获得关键字和name1, name2，恰好所有断言都是6个单词组合
        iss>>name1>>str>>str>>keyword>>str>>name2;
        //if(str.find("child")!=string::npos)
        //关键字1：儿子
        if(keyword=="child")
        {
            if(tree.IsChild(name2, name1))
                cout<<"True\n";
            else
                cout<<"False\n";
        }
        //关键字2：父亲
        else if(keyword=="parent")
        {
            if(tree.IsChild(name1, name2))
                cout<<"True\n";
            else
                cout<<"False\n";
        }
        //关键字3：兄弟
        else if(keyword=="sibling")
        {
            if(tree.IsSibling(name1, name2))
                cout<<"True\n";
            else
                cout<<"False\n";
        }
        //关键字4：后代
        else if(keyword=="descendant")
        {
            if(tree.IsAncestor(name1, name2))
                cout<<"True\n";
            else
                cout<<"False\n";
        }
        //关键字5：祖先
        else if(keyword=="ancestor")
        {
            if(tree.IsAncestor(name2, name1))
                cout<<"True\n";
            else
                cout<<"False\n";
        }
    }
    return 0;
}

