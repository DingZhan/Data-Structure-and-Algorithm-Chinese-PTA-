#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1001

int main()
{
    //������ģ�����
    //A���ڶ���
    int A[MAX_N];
    //B���ڶ���
    int B[MAX_N];
    int iA, iB, sizeA=0, sizeB=0, N, id, i;
    //�Ƿ��һ�δ�ӡ�������һ�δ�ӡ����Ҫ��ӡ�ո�
    int bFirst=1;

    //��������
    scanf("%d", &N);
    for(i=0; i<N; ++i)
    {
        scanf("%d", &id);
        //��λ������ж���ż����������A�����Ŷ�
        if(id&1)
            A[sizeA++] = id;
        else//ż������B�����Ŷ�
            B[sizeB++] = id;
    }

    //���α�iA, iBͬ��������������
    for(iA=0, iB=0; iA<sizeA && iB<sizeB;)
    {
        if(!bFirst)
            printf(" ");
        //�ȴ�ӡA���н����������
        printf("%d", A[iA++]);
        //���A���л����ˣ����ӡ��
        if(iA<sizeA)
            printf(" %d", A[iA++]);
        //���Ŵ�ӡB���н����������
        printf(" %d", B[iB++]);
        bFirst=0;
    }
    //���A���л�����
    while(iA<sizeA)
    {
        if(!bFirst)
            printf(" ");
        printf("%d", A[iA++]);
        bFirst = 0;
    }
    //���B���л�����
    while(iB<sizeB)
    {
        if(!bFirst)
            printf(" ");
        printf("%d", B[iB++]);
        bFirst = 0;
    }
    printf("\n");
    return 0;
}