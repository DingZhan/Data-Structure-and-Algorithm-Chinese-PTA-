#include <stdio.h>
//���51��Ͱ 
#define MAX_Y 51
int main()
{
	//��ʼ��ÿ��Ͱ��Ԫ����ĿΪ0 
	int buckets[MAX_Y]={0};
	int N, i, y;
	scanf("%d", &N);
	for(i=0; i<N; ++i)
	{
		scanf("%d", &y);
		//y��Ͱ��Ա����Ŀ��1 
		++buckets[y];
	}
	for(i=0; i<MAX_Y; ++i)
	{
		if(buckets[i])
		{
			printf("%d:%d\n", i, buckets[i]);
		}
	}
	return 0;	
}
