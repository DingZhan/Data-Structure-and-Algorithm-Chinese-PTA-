#include <iostream>
#include <stack>

using namespace std;

//��Ŀ������ʾ˵����DFS�����Ψһ������ֱ�ӿ�������DFS�ܽ��������
//ֻ����Ҫ��DFS���޸�

/*��������������м�ڵ�3��Ҫ��2�η���
6 6 1
1 2
2 3
3 4
4 5
3 6
1 5
*/
#define MAX_N 1002
#define MAX_M 3002

//���ڽӾ����ʾͼ
bool graph[MAX_N][MAX_N];

//��DFS��������������������������
//�������ⲻ��ŷ����·����ŷ��·�����⣬��Ϊŷ����·��·��Ҫ��������бߣ������Ʋ���Ҫ�������б�

//pos�ǵ�ǰ���ʵĶ��㣬N���ܶ��������visits�Ƕ���������ʱ��λ��path������·��Ҳ�ǻ�ȥ��·��
//bFirstPrint��Ҫ���������Ƿ��ȴ�ӡ�ո�
void DFS(int pos, int N, bool visits[], stack<int> &path, bool bFirstPrint)
{
    int i;

    //����Ѿ���·����
    //���⵱ǰ��ȷ��ʵĵ��Ƿ����һ����ӡ�ĵ�֮����·�����û��·�ʹ�·����ջ�е�������
    //ֱ���ж���͵�ǰ����֮���бߣ���������������(�Ӷ���5���ʵ�����6)
    if(path.size())
    {
        bool bFirstPop=true;
        while(true)
        {
            //�����ǰ��ȷ��ʵĵ����һ����ӡ�ĵ�֮��û��·
            if(!graph[pos][path.top()])
            {
                //�����Ҫ��������һ�����㲻Ҫ�ظ���ӡ
                if(!bFirstPop)
                    cout<<" "<<path.top();
                //��������
                path.pop();
                //������Ҫ�����Ķ�����Ҫ��ӡ
                bFirstPop = false;
            }
            else
                break;
        }
        //���֮ǰ��·���е��������㣬��Ҫ�൯��һ������
        //��Щ�ֿڣ���������������(�Ӷ���5���ʵ�����6)
        if(!bFirstPop)
            cout<<" "<<path.top();
    }

    //������ǵ�һ�δ�ӡ�����ȴ�ӡһ���ո��ٴ�ӡ��ǰ����
    if(!bFirstPrint)
        cout<<" ";
    //��ӡ��ǰ����
    cout<<pos;
    //�ѵ�ǰ����ӵ�·����ջ�У�Ϊ�˺�����ԭ·����
    path.push(pos);

    //DFS��ȱ����������飬�ҵ�û�б����ʹ��Ķ���
    for(i=1; i<=N; ++i)
    {
        //�������iû�����ʹ����������Ͷ���pos֮���б�����
        if(!visits[i] && graph[pos][i])
        {
            //���÷��ʱ��λ
            visits[i] = true;
            //DFS�ݹ����
            DFS(i, N, visits, path, false);
//            visits[i] = false;
        }
    }
}

int main()
{
    int i, N, M, S, a, b, seed;
    //������ʱ��,��ʼ��Ϊfalse
    bool visits[MAX_N]={false};
    //��¼����·��
    stack<int> path;

    //���붥��������������ʼ������
    cin>>N>>M>>S;
    //����M������Ϣ�������ڽӾ���ͼ
    for(i=0; i<M; ++i)
    {
        //����ߵ���������
        cin>>a>>b;
        graph[a][b] = graph[b][a] = true;
    }

    //���������ʱ��
    visits[S] = true;
    //��ʼ����������������һ����������Ϊtrue����ʾ��һ�δ�ӡ����ҪΪ�˿��ƿո������
    DFS(S, N, visits, path, true);

    //��������
    //�����ظ���ӡ���һ������
    if(path.size())
        path.pop();
    //ԭ·���ز���ӡ
    while(!path.empty())
    {
        cout<<" ";
        cout<<path.top();
        path.pop();
    }
    //����Ƿ��ж���û�����ʹ����������˵��ͼ����ͨ����ӡһ��0
    for(i=1; i<=N; ++i)
    {
        if(!visits[i])
        {
            cout<<" 0";
            break;
        }
    }
    cout<<endl;
    return 0;
}
