#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100001
//定义比较函数
int Compare(const void*a, const void *b)
{
	int *aa = (int*)a; //把无符号类型指针强制转换成具体的类型
	int *bb = (int*)b;
	return *aa - *bb; //整数类型可以将if - else if - else模式简化成减法，浮点类型绝对不行
}
//担心栈溢出，所以设置成全局变量 
int datas[MAX_N];
int main()
{
	int i, N;
	scanf("%d", &N);
	for(i=0; i<N; ++i)
	{
		scanf("%d", datas+i);
	}
	//调用快速排序函数，头文件stdlib.h
	qsort(datas, N, sizeof(datas[0]), Compare);
	for(i=0; i<N; ++i)
	{
		//除第一个元素外，每个元素打印之前先打印个空格
		if(i!=0)
			printf(" ");
		printf("%d", datas[i]);
	}
	printf("\n");
	return 0;	
}
