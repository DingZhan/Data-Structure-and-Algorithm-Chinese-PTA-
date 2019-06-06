#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

//���������ṹ��
struct TreeNode
{
    //ֵ
    int v;
    //�����ӽ��
    TreeNode *left, *right;
    //���캯��
    TreeNode(int value)
    {
        v = value;
        left = right = NULL;
    }
};

//��������
class Tree
{
public:
    //���캯��
    Tree() {m_Root=NULL;}
    //��������������ӽ��
    void AddNode(int value)
    {
        AddNode(m_Root, value);
    }
    //ǰ��������ص��ַ���
    string PreOrder()
    {
        string result;
        bool bFirst=true;
        //������һ���ݹ�ǰ�������˽�к���
        PreOrder(m_Root, bFirst, result);
        return result;
    }
    //����������ص��ַ���
    string PostOrder()
    {
        string result;
        bool bFirst=true;
        //������һ���ݹ���������˽�к���
        PostOrder(m_Root, bFirst, result);
        return result;
    }
    //��������������ľ�����
    void Mirror(Tree& mirrorTree)
    {
        //���ͷž�����ԭ�����ڴ�
        mirrorTree.FreeTree();
        //�����ǰ��Ϊ��ֱ�ӷ���
        if(!m_Root)
            return;
        //����˽�еĵݹ龵����
        MirrorNode(m_Root, mirrorTree.m_Root);
    }
    //�ͷ����ڴ�
    void FreeTree()
    {
        //����˽�еݹ���������ɾ������
        Free(m_Root);
        //�Ѹ��ڵ�����ΪNULL
        m_Root = NULL;
    }
private:
    //�ڶ����������£���ǰ���������½�㣬����һ����ָ������û��߶���ָ��
    void AddNode(TreeNode *&root, int value)
    {
        //�����ǰ����Ѿ�ΪNULL�������������λ�ô����½��
        if(!root)
        {
            root = new TreeNode(value);
            return;
        }
        //����½��ֵ�ȵ�ǰ���ֵС��������
        if(value<root->v)
            AddNode(root->left, value);
        else //����½��ֵ���ڵ��ڵ�ǰ���ֵ��������
            AddNode(root->right, value);
    }

    //ǰ������ݹ麯�������ص�ǰ���������ַ���
    void PreOrder(TreeNode *node, bool& bFirst, string& result)
    {
        if(!node)
            return;
        ostringstream oss;
        //������ǵ�һ�δ�ӡ�����ȴ�ӡ���ո�
        if(!bFirst)
            oss<<" ";
        //���÷ǵ�һ�δ�ӡ���
        bFirst = false;
        oss<<node->v;
        result+=oss.str();
        //����������
        if(node->left)
            PreOrder(node->left, bFirst, result);
        //����������
        if(node->right)
            PreOrder(node->right, bFirst, result);
    }

    //��������ݹ麯�������صĺ����������ַ���
    void PostOrder(TreeNode *node, bool& bFirst, string& result)
    {
        if(!node)
            return;
        //����������
        if(node->left)
            PostOrder(node->left, bFirst, result);
        //����������
        if(node->right)
            PostOrder(node->right, bFirst, result);
        ostringstream oss;
        //������ǵ�һ�δ�ӡ�����ȴ�ӡ���ո�
        if(!bFirst)
            oss<<" ";
        oss<<node->v;
        result+=oss.str();
        //���÷ǵ�һ�δ�ӡ���
        bFirst=false;
    }
    //���������ͷ��ڴ�
    void Free(TreeNode* node)
    {
        if(!node)
            return;
        Free(node->left);
        Free(node->right);
        delete node;
    }
    //������ĵݹ麯��,srcNode��Դ����㣬mirrorNode�Ƕ�Ӧ�ľ������ľ�����
    //����mirrorNode������ָ������ã����߶���ָ��
    void MirrorNode(const TreeNode* srcNode, TreeNode *&mirrorNode)
    {
        if(!srcNode)
            return;
        //����������
        mirrorNode = new TreeNode(srcNode->v);
        //srcNode������������mirroNode��������
        MirrorNode(srcNode->left, mirrorNode->right);
        //srcNode������������mirroNode��������
        MirrorNode(srcNode->right, mirrorNode->left);
    }

private:
    //�������
    TreeNode *m_Root;
};

int main()
{
    Tree srcTree, mirrorTree;
    int i, N, v;
    string preStr, str, preStr1,preStr2, postStr;
    istringstream iss;

    //��ֱ��ʹ��cin>>����Ҫ������и��س���Ҫ�Ե������Ըɴ�һ�ζ�һ��
    std::getline(std::cin, str);
    //�õ�N
    N = atoi(str.c_str());
    //�õ�������ǰ������ַ���
    std::getline(std::cin, preStr);
    //�Ѹ�ǰ������ַ��������istringstream����׼����ȡһ��������ֵ
    iss.str(preStr);
    for(i=0; i<N; ++i)
    {
        //�õ���ǰֵ
        iss>>v;
        //�Ѹý����뵽����������
        srcTree.AddNode(v);
    }
    //�Զ���������srcTree�����񣬵�ȻmirrorTree�����Ƕ���������
    srcTree.Mirror(mirrorTree);
    //�õ�srcTree��ǰ���������ַ���
    preStr1 = srcTree.PreOrder();
    //�õ���������ǰ���������ַ���
    preStr2 = mirrorTree.PreOrder();

    //���srcTree��ǰ���������ַ����������һ��
    if(preStr1==preStr)
    {
        cout<<"YES\n";
        postStr = srcTree.PostOrder();
        cout<<postStr<<"\n";
    }
    //�����������ǰ���������ַ����������һ��
    else if(preStr2==preStr)
    {
        cout<<"YES\n";
        postStr = mirrorTree.PostOrder();
        cout<<postStr<<"\n";
    }
    else //���򶼲�һ��
        cout<<"NO\n";

    return 0;
}
