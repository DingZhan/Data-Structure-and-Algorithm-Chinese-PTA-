#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

//���ڵ�ṹ��
struct TreeNode
{
    //Ŀ¼���ļ������Ƿ���Ŀ¼���ļ�
    TreeNode(const string& name, bool bDir)
    {
        this->name = name;
        this->bDir = bDir;
        //��ʼ������������ΪNULL
        left = right = NULL;
    }
    //����ӣ����ֵ�
    TreeNode *left, *right;
    //Ŀ¼���ļ���
    string name;
    //�ý���Ƿ���Ŀ¼
    bool bDir;
};

//���ȽϺ��������ַ����ֵ����š�Ŀ¼����Ŀ¼���Ƚϣ��ļ������ļ����Ƚ�
bool CompareNode(const TreeNode* a, const TreeNode* b)
{
    return a->name<b->name;
}

//�������ࣨĿ¼����
struct Tree
{
public:
    Tree()
    {
        //��ʼ������ΪNULL
        m_Root = NULL;
    }
    //����һ��Ŀ¼���ļ����
    void InsertNode(const string& name)
    {
        //�����Ϊ�գ���ʼ������Ϊroot
        if(!m_Root)
            InitTree();
        //pParent�Ǹ����
        TreeNode *pParent = m_Root;
        string curName = name, dirName;
        size_t pos;
        //levelCount�ǵ�ǰ·������
        int levelCount=0;

        //����·���ָ���һ������Ŀ¼
        while(true)
        {
            //����·���ָ���
            pos = curName.find_first_of('\\');
            //û�ҵ��ָ�������ǰ���ļ���������ļ�����parent�����
            if(pos==string::npos)
            {
                InsertNode(pParent, curName, false);
                break;
            }
            else if(pos==curName.size()-1)//�ָ��������һ���ַ���������·���������·�����
            {
                //�����һ���ָ���ɾ��
                curName.erase(curName.end()-1);
                InsertNode(pParent, curName, true);
                break;
            }
            else
            {
                //�õ���ǰ·����
                dirName.assign(curName.begin(), curName.begin()+pos);
                //�����·����ͬʱ��õ�ǰ·�����
                pParent = InsertNode(pParent, dirName, true);
                //�ۼӵ�ǰ·������
                ++levelCount;
                //�����·����������һ��Ŀ¼
                curName.erase(curName.begin(), curName.begin()+pos+1);
            }
        }
    }
    //��pParent����²����ļ���·��
    TreeNode* InsertNode(TreeNode *pParent, const string& name, bool bDir)
    {
        if(!pParent)
            return NULL;
        //son��pParent��һ�����ӽ��,pPre�Ǳ�����ǰһ�����
        TreeNode *son = pParent->left, *pPre=NULL;
        //�����Ӳ�Ϊ��
        while(son)
        {
            //�����·�����ļ��Ѿ�����pParent�����
            if(son->name==name && son->bDir==bDir)
                return son;
            //����ǰһ�����
            pPre = son;
            //���ֵܽ�����
            son = son->right;
        }
        //����һ�����
        TreeNode* pNode = new TreeNode(name, bDir);
        //���ǰһ�����Ϊ�գ���˵��pParent�»�û�ж���
        if(!pPre)
            pParent->left = pNode;
        else//����pPre�����ֵ�����Ϊ��ǰ�����Ľ��
            pPre->right = pNode;
        return pNode;
    }
    //��ʼ����
    void InitTree()
    {
        //������ǿգ������ͷ����ڴ�
        if(m_Root)
            FreeTree();
        //���������
        m_Root = new TreeNode("root", true);
    }
    //�ͷ�Ŀ¼���ڴ�
    void FreeTree()
    {
        //����˽�еݹ麯��
        FreeTree(m_Root);
        //����������ΪNULL
        m_Root = NULL;
    }
    //��ӡĿ¼��
    void Print()
    {
        //����˽�еݹ��ӡ������0�ǵ�ǰĿ¼�������������ƿո��ӡ����
        PrintTree(m_Root, 0);
    }
private:
    //��������ͷ����ڴ�
    void FreeTree(TreeNode* pNode)
    {
        if(!pNode)
            return;
        FreeTree(pNode->left);
        FreeTree(pNode->right);
        delete pNode;
    }
    //�ݹ��ӡĿ¼����levelCount�ǵ�ǰĿ¼��������������ƿո�Ĵ�ӡ��Ŀ
    void PrintTree(TreeNode* pParent, int levelCount)
    {
        if(!pParent)
            return;
        std::vector<TreeNode*> fileNodes;
        std::vector<TreeNode*> dirNodes;
        TreeNode *pNode = pParent->left;
        int i;
        //���ݵ�ǰĿ¼���������ӡ�����Ŀո�
        for(i=0; i<levelCount; ++i)
            cout<<"  ";
        //��ӡ·�����ļ���
        cout<<pParent->name<<endl;
        //�������·���򷵻�
        if(!pParent->bDir)
            return;
        //�õ���ǰ·�������е��ļ�����Ŀ¼�������ڲ�ͬ��������
        while(pNode)
        {
            if(pNode->bDir)
                dirNodes.push_back(pNode);
            else
                fileNodes.push_back(pNode);
            pNode = pNode->right;
        }

        //��Ŀ¼�������ֵ�����
        sort(dirNodes.begin(), dirNodes.end(), CompareNode);
        //�ݹ���ô�ӡ
        for(i=0; i<dirNodes.size(); ++i)
            PrintTree(dirNodes[i], levelCount+1);

        //���ļ��������ֵ�����
        sort(fileNodes.begin(), fileNodes.end(), CompareNode);
        //�ݹ���ô�ӡ
        for(i=0; i<fileNodes.size(); ++i)
            PrintTree(fileNodes[i], levelCount+1);
    }

private:
    //����
    TreeNode *m_Root;
};

int main()
{
    //�ر�I/Oͬ��
    std::ios::sync_with_stdio(false);
    int N, i;
    string name;
    //����Ŀ¼��
    Tree tree;

    //��getline��Ҫ�Ե����Ļس���
    getline(cin, name);
    //�õ�N����¼
    N = atoi(name.c_str());

    //�õ�N����¼
    for(i=0; i<N; ++i)
    {
        getline(cin, name);
        //��·�����ļ�������
        tree.InsertNode(name);
    }
    //��ӡ��
    tree.Print();
    return 0;
}
