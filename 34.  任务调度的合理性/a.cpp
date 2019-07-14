#include <iostream>
#include <vector>

using namespace std;

//Ŀ�꣺��������ͼ���Ƿ��л�·

#define MAX_N 101
//�ö�ά�����ʾ����ͼ����Ч�±��1��ʼ
bool graphics[MAX_N][MAX_N];
//����ͼ�ж����Ƿ���ʹ������������ʹ��Ͳ�Ҫ�ٳ��������������
bool bVisits[MAX_N];

//�ݹ��������������·��seed��ʾ��ǰλ�ã�N��ʾ������Ŀ��
//bLoopVisits�Ǳ����Щ������������·����
//bHasLoop����Ƿ��������˻�·
//path�ǻ�··��
void DFS_HasLoop(int seed, int N, bool bLoopVisits[], bool& bHasLoop, std::vector<int>& path)
{
    //���õ�ǰλ��������·����
    bLoopVisits[seed] = true;
    //���õ�ǰλ�ñ�������
    bVisits[seed] = true;
    //�ѵ�ǰλ�üӵ�·����
    path.push_back(seed);
    int j;
    //����seedָ��ı�
    for(j=1; j<=N; ++j)
    {
        if(!graphics[seed][j])
            continue;
        //�ҵ�һ����seed->j
        //����߶���j�Ѿ��ڵ�ǰ����·�����˵���ҵ��˻�·
        if(bLoopVisits[j])
        {
            //�޳�ǰ��ǻ�·�Ĳ���·��
            while(path.front()!=j)
                path.erase(path.begin());
            path.push_back(j);
            //�������ҵ���·�ı�־
            bHasLoop = true;
            //����
            return;
        }
        //����߶���jû�����ʹ�����DFS��j
        if(!bVisits[j])
        {
            //�ݹ�DFS��j
            DFS_HasLoop(j, N, bLoopVisits, bHasLoop, path);
            //�����·��־�����ù����򷵻�
            if(bHasLoop)
                return;
        }
    }
    //��ǰ����û�����κλ�·�����Ի���
    path.pop_back();
    //��ǰ����û�����κλ�·�����Ի��˱��
    bLoopVisits[seed] = false;
    return;
}

int main()
{
    //�ر���stdio��ͬ��
    std::ios::sync_with_stdio(false);
    int i, j, N, K, v, seed;
    //��·��ǣ���ʼʱû�л�·
    bool bHasLoop=false;
    //���붥����Ŀ
    cin>>N;
    //����ÿ������
    for(i=1; i<=N; ++i)
    {
        //��������ǰ��������Ŀ
        cin>>K;
        //������������ǰ������
        for(j=0; j<K; ++j)
        {
            cin>>v;
            //��������ͼ
            graphics[v][i] = true;
        }
    }
    //�������ж��㣬�������ͼ���Ƿ��л�·
    for(i=1; i<=N; ++i)
    {
        //����ö�����֮ǰ�Ѿ������ʹ���������һ������
        if(bVisits[i])
            continue;
        //��··��
        std::vector<int> path;
        //��ʼ��ǰ·��������ʱ��
        bool bLoopVisits[MAX_N]={false};
        //DFS��⻷·
        DFS_HasLoop(i, N, bLoopVisits, bHasLoop, path);
        //�����⵽��·���˳�
        if(bHasLoop)
            break;
    }

    cout<<(bHasLoop?0:1)<<endl;
    return 0;
}

