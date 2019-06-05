#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <assert.h>

using namespace std;

//���ڵ���
class TreeNode
{
public:
    TreeNode(const string& name)
    {
        left = right = parent = NULL;
        this->name = name;
    }
    //����ӣ����ֵ�, ���ڵ�ָ��
    TreeNode *left, *right, *parent;
    //ֵ:����
    string name;
};

//��������
class Tree
{
public:
    //���캯�������ڵ�ΪNULL
    Tree() {m_Root=NULL;}
    //��Ӹ����
    TreeNode* AddRoot(const string& name)
    {
        //���ͷ�֮ǰ�����ڴ�
        FreeTree();
        //���������
        m_Root =  new TreeNode(name);
        return m_Root;
    }

    //��parent����²�����ӽ��
    TreeNode* InsertChild(TreeNode *parent, const std::string& childName)
    {
        //��һ�����ӽ��
        TreeNode *child = parent->left;
        //������ǰ���ӽ��
        TreeNode *newNode =  new TreeNode(childName);
        //���ö��ӽ��ĸ����
        newNode->parent = parent;
        //�����ǰ��û�ж��ӣ��������½������Ϊ��һ������
        if(!child)
            parent->left = newNode;
        else
        {
            //�ҵ����һ�����ӣ����½��������һ�����ӵ��ұ�
            while(child->right)
                child = child->right;
            child->right = newNode;
        }
        return newNode;
    }

    //�����ֵܽ��
    TreeNode* InsertSibling(TreeNode *src, const string& name)
    {
        //�ҵ��ý���ұߵ����һ���ֵ�
        while(src->right)
            src = src->right;
        //�����½��
        TreeNode *newNode =  new TreeNode(name);
        //�Ѹý��������ұߵĽ��
        src->right = newNode;
        //�����½��ĸ���
        newNode->parent = src->parent;
        return newNode;
    }

    //��DFS����name��Ӧ�Ľ��
    TreeNode* Find(const string& name)
    {
        stack<TreeNode*> seeds;
        TreeNode *seed;
        //����ֱ�ӷ���NULL
        if(!m_Root)
            return NULL;
        //��������
        seeds.push(m_Root);
        while(!seeds.empty())
        {
            //����һ������
            seed = seeds.top();
            seeds.pop();
            //����ҵ����򷵻�
            if(seed->name==name)
                return seed;
            //���������
            if(seed->left)
                seeds.push(seed->left);
            //�����Ҷ���
            if(seed->right)
                seeds.push(seed->right);
        }
        return NULL;
    }

    //chilename�Ƿ���parentname�Ķ���
    bool IsChild(const string& parentname, const string& childname)
    {
        //�ҵ����ڵ�
        TreeNode* parent = Find(parentname);
        //���û�ҵ������㣬��ֱ�ӷ���NULL
        if(!parent)
            return false;
        TreeNode* child = parent->left;
        //�������ڵ�����ж���
        while(child)
        {
            //�ҵ��ͷ���
            if(child->name==childname)
                return true;
            child = child->right;
        }
        return false;
    }
    //�ж�siblingname�Ƿ��name���ֵܹ�ϵ
    bool IsSibling(const string& siblingname, const string& name)
    {
        //�ҵ�siblingname�Ľ��
        TreeNode*sibling = Find(siblingname);
        //���û�ҵ������㣬��ֱ�ӷ���NULL
        if(!sibling)
            return false;
        //���sibling�Ǹ���㣬��Ҳ���뷵��NULL
        if(!sibling->parent)
            return false;
        //�ӵ�һ���ֵܽ�㿪ʼ����
        TreeNode* node = sibling->parent->left;
        while(node)
        {
            //�ҵ��ͷ���
            if(node->name==name)
                return true;
            node = node->right;
        }
        return false;
    }
    //�ж�ancestorName�Ƿ���childname������
    bool IsAncestor(const string& childname, const string& ancestorName)
    {
        //��Ϊ��parent��㣬�������Ǵ���������
        //�ҵ�childname���
        TreeNode*child = Find(childname);
        //���û�ҵ��򷵻�
        if(!child)
            return false;
        //��ʼ������
        TreeNode* node = child->parent;
        while(node)
        {
            if(node->name==ancestorName)
                return true;
            //һֱ������
            node = node->parent;
        }
        return false;
    }

    //�ͷ����ڴ�
    void FreeTree()
    {
        Free(m_Root);
        m_Root = NULL;
    }
private:
    //��������ͷ����ڴ�
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

//����һ�����ֽ��ṹ��
struct TextNode
{
    //�����ո���
    int indent;
    //����
    string name;
    //�󶨵�TreeNode�ṹ��Ҳ���ǵ�ǰTextNode��Ӧ��TreeNode���
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
    //TextNode�ṹ��ջ�������ж��Ƿ���븸�ӽ�㡢�ֵܽ��
    stack<TextNode> indentNames;
    TextNode tn;

    //�õ�һ������
    std::getline(cin, str);
    iss.clear();
    iss.str(str);
    //��������������ж�������
    iss>>N>>M;

    //�������
    for(i=0; i<N; ++i)
    {
        //�õ�һ�м���
        std::getline(cin, str);
        //����ǰ�ÿո���
        pos = str.find_first_not_of(' ');
        //�õ�����
        name.assign(str.begin()+pos, str.end());
 //       cout<<"Test name: "<<name<<endl;
        //���������
        if(i==0)
        {
            //�����ϴ�������㣬ͬʱ�Ѹý�㱣�����ı������
            tn.node = tree.AddRoot(name);
            tn.name = name;
            tn.indent = pos;
            //���ı�������ջ
            indentNames.push(tn);
            continue;
        }
        //�õ���һ���ı����
        TextNode lastTN = indentNames.top();

        //�������������һ���ģ��������ֵ�
        if(lastTN.indent==pos)
        {
            //�����ֵܽ��
            node = tree.InsertSibling(lastTN.node, name);
            tn.name = name;
            tn.node = node;
            tn.indent = pos;
            //���뱾�Ľڵ㵽ջ
            indentNames.push(tn);
        }
        //�������࣬��������һ�����ĵ�һ������
        else if(lastTN.indent<pos)
        {
            node = tree.InsertChild(lastTN.node, name);
            tn.name = name;
            tn.node = node;
            tn.indent = pos;
            indentNames.push(tn);
        }
        else//��һ�������������ֵܶ�Ҫ��ջ�ﵯ��������Ϊ��ǰ��������ǵ����塢�岮��
        {
            //������һ�����
            indentNames.pop();
            while(!indentNames.empty())
            {
                //������㣬ֱ��������ͬ�����
                if(indentNames.top().indent==pos)
                    break;
                indentNames.pop();
            }
            //��Щ����
            assert(!indentNames.empty());
            //�õ��Ѽ������һ���ֵܽ��
            lastTN = indentNames.top();
            assert(lastTN.indent==pos);
            //���뵱ǰ���ֵܽ��
            node = tree.InsertSibling(lastTN.node, name);
            tn.name = name;
            tn.node = node;
            tn.indent = pos;
            //�Ѹý�����ջ
            indentNames.push(tn);
        }
    }

    //��ȡ�ж����
    /*
X is a child of Y
X is the parent of Y
X is a sibling of Y
X is a descendant of Y
X is an ancestor of Y
*/
    for(i=0; i<M; ++i)
    {
        //�õ�һ�����
        getline(std::cin, str);
        iss.clear();
        iss.str(str);
        //������ʽ��ùؼ��ֺ�name1, name2��ǡ�����ж��Զ���6���������
        iss>>name1>>str>>str>>keyword>>str>>name2;
        //if(str.find("child")!=string::npos)
        //�ؼ���1������
        if(keyword=="child")
        {
            if(tree.IsChild(name2, name1))
                cout<<"True\n";
            else
                cout<<"False\n";
        }
        //�ؼ���2������
        else if(keyword=="parent")
        {
            if(tree.IsChild(name1, name2))
                cout<<"True\n";
            else
                cout<<"False\n";
        }
        //�ؼ���3���ֵ�
        else if(keyword=="sibling")
        {
            if(tree.IsSibling(name1, name2))
                cout<<"True\n";
            else
                cout<<"False\n";
        }
        //�ؼ���4�����
        else if(keyword=="descendant")
        {
            if(tree.IsAncestor(name1, name2))
                cout<<"True\n";
            else
                cout<<"False\n";
        }
        //�ؼ���5������
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

