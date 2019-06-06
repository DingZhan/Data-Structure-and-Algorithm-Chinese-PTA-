#include <iostream>
#include <cmath>

using namespace std;

//计算出的大于1000的最小质数
#define MAX_P 1009

#define EMPTY_VALUE  -100000000
//这个API用来找到不小于N的最小质数，用来做最大hash表的长度
int MinPrime(int N)
{
    int P = N;
    int i, t;
    while(true)
    {
        t=sqrt(P);
        for(i=2; i<=t; ++i)
        {
            if(P%i==0)
                break;
        }
        if(i>t)
            break;
        ++P;
    }
    return P;
}

int main()
{
    int N, P, i, j, k,key;
    int hashTable[MAX_P];

    //读入待插入的关键字总数N 和 散列表的长度P
    cin>>N>>P;
    //将hash表中内容全部置为空
    for(i=0; i<P; ++i)
        hashTable[i] = EMPTY_VALUE;
    //读入N个关键字
    for(k=0; k<N; ++k)
    {
        //得到关键字
        cin>>key;
        //计算关键字在hash表中的位置
        i = key%P;
        //如果当前待插入的位置i内容为空，或者内容和关键字一样，则将关键字插入该位置并打印位置
        if(hashTable[i]==EMPTY_VALUE||hashTable[i]==key)
        {
            //将关键字插入hash表位置i
            hashTable[i] = key;
            //第一次不打印前置空格
            if(k!=0)
                cout<<" ";
            //打印位置
            cout<<i;
        }
        else//否则，有冲突发生
        {
            //采用线性探测法，找到合适的插入位置
            for(j=1; ;++j)
            {
                //如果该位置为空或者内容正好和关键字一样，则插入该位置
                if(hashTable[(i+j)%P]==EMPTY_VALUE||hashTable[(i+j)%P]==key)
                {
                    i = (i+j)%P;
                    hashTable[i] = key;
                    //如果非第一次打印，则打印前置空格
                    if(k!=0)
                        cout<<" ";
                    cout<<i;
                    break;
                }
            }
        }
    }
    return 0;
}
