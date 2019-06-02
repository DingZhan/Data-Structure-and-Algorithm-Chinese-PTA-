#include <stdio.h>
#include <stdlib.h>

//ʹ�ò��鼯(Union-Find Set)������ѡ��㷨�������ž��䡷��p200
#define MAX_N 300002
#define MAX_M 1001

//���鼯��ÿ��������ڼ��ϵĸ������
int parents[MAX_N];
//ѧ�����ʱ�־
char bVisits[MAX_N];
//Ͱ����������ü��ϵ�����������ID���Ǹ����ID
int buckets[MAX_N];

//�ҵ�����
int find(int x)
{
    if(parents[x]==x)
        return x;
    else
        return find(parents[x]);
}
int main()
{
    int N, M, i, j, num, refRootID, rootID, id;
    //����ѧ�������;��ֲ�����
    scanf("%d%d", &N, &M);
    //�����鼯ÿ�����ָ���Լ������Լ���ǰ�Ǹ������ļ���
    for(i=1; i<=N; ++i)
        parents[i] = i;
    //����ÿ�����ֲ���Ϣ
    for(i=1; i<=M; ++i)
    {
        //��ǰ���ֲ�����
        scanf("%d", &num);
        //�ο����ڵ㣬һ��Ὣ��ǰ���о��ֲ�ѧ��ָ��ο��ڵ�
        refRootID = -1;
        for(j=0; j<num; ++j)
        {
            //����ѧ��ѧ��
            scanf("%d", &id);
            //���Ҹ�ѧ�����ڼ��ϵĸ����
            rootID = find(id);
            //���ο����������Ϊ��һ��Ԫ�صĸ����
            if(j==0)
                refRootID = rootID;
            else//��������Ԫ�صĸ��ڵ㶼ָ��ο����ڵ�
                parents[rootID] = refRootID;
        }
    }

    //��ʼ���������Ȧ����Ϊ0
    int maxNum=0;
    //����ÿ��ѧ��
    for(i=1; i<=N; ++i)
    {
        //�����ѧ���Ѿ������ʹ�
        if(bVisits[i])
            continue;
        //�ҵ���ѧ�����ڼ��ϵĸ����
        rootID = find(i);
        //�ü���Ͱ�ۼ�1��ͰID���Ǽ��ϸ��ڵ�ID
        buckets[rootID]++;
        //���ۼӱ��ж�
        if(buckets[rootID]>maxNum)
            maxNum = buckets[rootID];
    }
    printf("%d\n", maxNum);
    return 0;
}
