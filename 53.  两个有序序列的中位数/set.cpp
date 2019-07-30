#include <stdio.h>
#include <string.h>

//这个是集合方法，“并集”的错误理解
#define MAX_N 1000002
#define MAX_2N 2000004
long long S1[MAX_N];
long long S2[MAX_N];
long long S3[MAX_2N];
int main()
{
    long long len;
    long long i, j, N;
    scanf("%lld", &N);
    for(i=0; i<N; ++i)
        scanf("%lld", S1+i);
    for(i=0; i<N; ++i)
        scanf("%lld", S2+i);
    len = 0;
    for(i=0, j=0; i<N && j<N; )
    {
        if(S1[i]<S2[j])
        {
            if(len==0 || (len>0 && S3[len-1]!=S1[i]))
                S3[len++] = S1[i];
            ++i;
        }
        else if(S1[i]>S2[j])
        {
            if(len==0 || (len>0 && S3[len-1]!=S2[j]))
                S3[len++] = S2[j];
            ++j;
        }
        else
        {
            if(len==0 || (len>0 && S3[len-1]!=S1[i]))
                S3[len++] = S1[i];
            ++i;
            ++j;
        }
    }
    //if(i<N)
    {
        while(i<N)
        {
            if(len==0 || (len>0 && S3[len-1]!=S1[i]))
                S3[len++] = S1[i];
            ++i;
        }
    }
    //else if(j<N)
    {
        while(j<N)
        {
            if(len==0 || (len>0 && S3[len-1]!=S2[j]))
                S3[len++] = S2[j];
            ++j;
        }
    }
    printf("%lld\n", S3[(len-1)/2]);
}
