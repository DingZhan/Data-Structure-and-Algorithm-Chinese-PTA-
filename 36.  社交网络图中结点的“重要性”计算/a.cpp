#include <iostream>
#include <iomanip>

using namespace std;

//��Floyd�㷨��������ͼ��������������·��
#define INF 100000000
//���������
#define MAX_N 10001
//���ڽӾ�������ʾͼ�������������<i,j>֮��û��ͨ·����diss[i][j]=INF
int diss[MAX_N][MAX_N];
int main()
{
    int N, M, K, i, j, k, a, b;
    double v;
    //���붥�����ͱ���
    cin>>N>>M;
    //��ʼ�������ڽӾ���������������㶼����ͨ
    for(i=1; i<=N; ++i)
    {
        for(j=1; j<=N; ++j)
            diss[i][j] = INF; //��ʼ������ͨ
    }
    //����M����
    for(i=0; i<M; ++i)
    {
        cin>>a>>b;
        //�����ڽӾ������a��b�����Ϊ1
        diss[a][b] = diss[b][a] = 1;
    }
    //����Floyd�㷨������������������̾���
    //Floyd�㷨��kһ��Ҫ���������
    for(k=1; k<=N; ++k)
    {
        for(i=1; i<=N; ++i)
        {
            if(i==k)
                continue;
            for(j=1; j<=N; ++j)
            {
                if(j==i || j==k)
                    continue;
                //���<i,j>�����С��<i,k>+<k,j>�������<i,j>�����
                if(diss[i][j]>diss[i][k]+diss[k][j])
                    diss[i][j]=diss[i][k]+diss[k][j];
            }
        }
    }
    //�����ѯ�Ķ�����Ŀ
    cin>>K;
    //����K������
    for(i=0; i<K; ++i)
    {
        //��Ҫ����Ķ�����k
        cin>>k;
        //�ۼӶ���k���������ж����ľ���
        v = 0.0;
        for(j=1; j<=N; ++j)
        {
            //��Ҫ�ۼ��Լ�
            if(k==j)
                continue;
            //���<k,j>�����ͨ�����ֵ����Ϊ0.0���˳��ۼӼ���
            if(diss[k][j]==INF)
            {
                v = 0.0;
                break;
            }
            //�ۼӾ���
            v+=diss[k][j];
        }
        //���ݹ�ʽ�����Ȩֵ
        if(v!=0.0)
            v = (N-1)/v;
        cout<<"Cc("<<k<<")="<<std::fixed<<setprecision(2)<<v<<endl;
    }
}
