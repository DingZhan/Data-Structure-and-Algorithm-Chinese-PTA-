#include <stdio.h>
//最多51个桶 
#define MAX_Y 51
int main()
{
	//初始化每个桶中元素数目为0 
	int buckets[MAX_Y]={0};
	int N, i, y;
	scanf("%d", &N);
	for(i=0; i<N; ++i)
	{
		scanf("%d", &y);
		//y号桶中员工数目加1 
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
