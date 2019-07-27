#include <iostream>
#include <queue>
using namespace std;

//ע������ͼŷ����·��ŷ����·������
//����ͼ����ŷ����·���ҽ������ж����degree��Ϊż��
//����ͼ����ŷ����·���ҽ������ж����degree��Ϊż������ֻ�����������degreeΪ����

//���������
#define MAX_N 1001
//�ڽӱ��ʾͼ
bool graph[MAX_N][MAX_N];

int main()
{
    int N, M, i, a, b, j, oddNum=0, degree;
    //���붥�����ͱ���
    cin>>N>>M;
    for(i=0; i<M; ++i)
    {
        cin>>a>>b;
        //��������ͼ�ı�
        graph[a][b] = true;
        graph[b][a] = true;
    }
    //����ÿ�������degree���������ı���Ŀ, ��һ���ļ���degreeΪ�����Ķ������
    for(i=1; i<=N; ++i)
    {
        degree = 0;
        for(j=1; j<=N; ++j)
        {
            if(graph[i][j])
                ++degree;
        }
        if(degree%2)
            ++oddNum;
    }
    //ŷ����·����
    //if(oddNum!=0 && oddNum!=2)

    //ŷ����·��������������ⶥ���degreeΪ�������򲻴���ŷ����·
    if(oddNum!=0)
        cout<<0<<endl;
    else
    {
        //���ͼ����ͨ�ԣ���������ͨ��������������Ϊ1����ͼ����ͨ
        //�������BFS����
        //������ʱ������
        bool bVisits[MAX_N]={false};
        //BFSʹ�õĶ���
        std::queue<int> seeds;
        //ͼ��ͨ�������
        int regions = 0, seed;
        //����ÿ������
        for(i=1; i<=N; ++i)
        {
            //��������ѱ����ʹ�
            if(bVisits[i])
                continue;
            //�ۼ��µ���ͨ����
            ++regions;
            //���ö�����ʱ��
            bVisits[i] = true;
            //�Ѹö���ӵ�BFS����
            seeds.push(i);
            //��ʼ�����������
            while(!seeds.empty())
            {
                //�������Ӷ���
                seed = seeds.front();
                seeds.pop();
                //�������Ӷ���������ڽӶ��㣬���û�����ʹ��ͼӵ�������
                for(j=1; j<=N; ++j)
                {
                    if(graph[seed][j] && !bVisits[j])
                    {
                        seeds.push(j);
                        bVisits[j] = true;
                    }
                }
            }
        }
        //����ж���ͨ����ĸ����������Ϊ1�����ͨ
        if(regions==1)
            cout<<1<<endl;
        else
            cout<<0<<endl;
    }
    return 0;
}
