#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100001
//����ȽϺ���
int Compare(const void*a, const void *b)
{
	int *aa = (int*)a; //���޷�������ָ��ǿ��ת���ɾ��������
	int *bb = (int*)b;
	return *aa - *bb; //�������Ϳ��Խ�if - else if - elseģʽ�򻯳ɼ������������;��Բ���
}
//����ջ������������ó�ȫ�ֱ��� 
int datas[MAX_N];
int main()
{
	int i, N;
	scanf("%d", &N);
	for(i=0; i<N; ++i)
	{
		scanf("%d", datas+i);
	}
	//���ÿ�����������ͷ�ļ�stdlib.h
	qsort(datas, N, sizeof(datas[0]), Compare);
	for(i=0; i<N; ++i)
	{
		//����һ��Ԫ���⣬ÿ��Ԫ�ش�ӡ֮ǰ�ȴ�ӡ���ո�
		if(i!=0)
			printf(" ");
		printf("%d", datas[i]);
	}
	printf("\n");
	return 0;	
}
