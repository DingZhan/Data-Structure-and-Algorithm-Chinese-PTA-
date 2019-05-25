#include <iostream>
using namespace std;

#define MAX_K 100000
int main()
{
    int K, i, v;
    //从第0到第i个元素的有效累加和，所谓“有效”累加和是指当和为负数，则将和设置成0
    int s[MAX_K]={0};
    //实时扫描当前s数组中当前元素的最大值
    int maxS=0;

    cin>>K;
    for(i=0; i<K; ++i)
    {
        cin>>v;
        if(i==0)
            s[i]=(v>0?v:0);
        else
        {
            s[i]=s[i-1]+v;
            //计算有效累加和
            if(s[i]<0)
                s[i] = 0;
        }
        if(s[i]>maxS)
            maxS = s[i];
    }
    cout<<maxS<<endl;
}
