#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200001

//�����к���浽һ��������
long long phones[MAX_N];

//����ȽϺ���,��Ϊ��long long���ͣ����Բ���ֱ����(long long*)a-(long long*)b�򻯣������
int Compare(const void *a, const void *b)
{
    long long *aa=(long long*)a;
    long long *bb=(long long*)b;
    if(*aa<*bb)
        return -1;
    else if(*aa>*bb)
        return 1;
    else
        return 0;
}
int main()
{
    int N, i, maxCount=0, sameNum, lastCount;
    long long a, b, maxPhone, lastPhone=-1;
    //����ͨ����¼����
    scanf("%d", &N);
    //��������ͨ����¼
    for(i=0; i<N; ++i)
    {
        //%lld��long long���Ͷ����ʽ
        scanf("%lld%lld", &a, &b);
        //��˫������洢��������
        phones[2*i] = a;
        phones[2*i+1] = b;
    }
    //�������������,�����С��������
    qsort(phones, 2*N, sizeof(long long), Compare);

    //��ʼ�����������飬������ͬ�������
    for(i=0, lastCount=-1; i<2*N; ++i)
    {
        //�����ǰ���������һ�����룬���ۼӸú����ͨ������
        if(lastPhone==phones[i])
        {
            lastCount++;
        }
        else //��ǰ���벻������һ�����룬��Ҫ����˭��ͨ��������
        {
            //�����һ�������ͨ���������ڼ�¼�����ͨ������
            //��ˢ�����ͨ�������ļ�¼
            if(lastCount>maxCount)
            {
                maxPhone = lastPhone;
                maxCount = lastCount;
                //���õ�ǰ���ͨ����¼����Ϊ1
                sameNum=1;
            }
            //�����һ�������ͨ���������ڼ�¼�����ͨ������
            //���ۼӵ�ǰ���ͨ����¼����
            else if(lastCount==maxCount)
                sameNum++;
            //������һ���绰���룬��ͨ������
            lastPhone = phones[i];
            lastCount = 1;
        }
    }
    //�����ѭ��������δ��������
    if(lastCount>maxCount)
    {
        maxPhone = lastPhone;
        maxCount = lastCount;
        sameNum=1;
    }
    else if(lastCount==maxCount)
        sameNum++;

    if(sameNum==1)
    {
        printf("%lld %d\n", maxPhone, maxCount);
    }
    else
    {
        printf("%lld %d %d\n", maxPhone, maxCount, sameNum);
    }

    return 0;
}
