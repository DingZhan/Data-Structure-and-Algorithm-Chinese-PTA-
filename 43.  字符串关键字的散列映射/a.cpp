#include <iostream>
#include <cmath>

using namespace std;

//大于1000的最小质数，找到1009这个合适的质数
#define MAX_P 1009

//hash表，表中内容是字符串
std::string hashTable[MAX_P];

//这个API用来找到一个比N大两倍的最小质数，用来做最大hash表的长度
int MinPrime(int N)
{
    int P = 2*N;
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
    int N, P, i, j, k, len, sum, pow32;

    std::string str;
    //读入待插入的关键字总数N 和 散列表的长度P
    cin>>N>>P;
    //读入N个关键字
    for(k=0; k<N; ++k)
    {
        cin>>str;
        //得到关键字长度
        len = str.length();
        sum = 0;
        //32^的指数
        pow32 = 1;
        //得到后三个关键字的起始位置，需要注意关键字长度有可能小于3
        j = std::max(len-3, 0);
        //对后三个关键字进行映射码计算
        for(i=len-1; i>=j; --i)
        {
            sum+=(str[i]-'A')*pow32;
            pow32*=32;
        }
        //根据映射码计算在hash表中的位置
        i = sum%P;
        //如果当前待插入的位置i内容为空，或者内容和关键字一样，则将关键字插入该位置并打印位置
        if(hashTable[i].empty()||hashTable[i]==str)
        {
            //将关键字插入hash表位置i
            hashTable[i] = str;
            //第一次不打印前置空格
            if(k!=0)
                cout<<" ";
            //打印位置
            cout<<i;
        }
        else//否则，有冲突发生
        {
            //采用平方法，找到合适的插入位置
            //先正向检测，后逆向检测
            for(j=1; ;++j)
            {
                //平方法正向检测，如果该位置为空或者内容正好和关键字一样，则插入该位置
                if(hashTable[(i+j*j)%P].empty()||hashTable[(i+j*j)%P]==str)
                {
                    i = (i+j*j)%P;
                    hashTable[i] = str;
                    //如果非第一次打印，则打印前置空格
                    if(k!=0)
                        cout<<" ";
                    cout<<i;
                    break;
                }
                //平方法逆向检测，如果该位置为空或者内容正好和关键字一样，则插入该位置
                //这里累加了1000*P,是为了把偏移后的位置弄成正数
                else if(hashTable[(i-j*j+1000*P)%P].empty()||hashTable[(i-j*j+1000*P)%P]==str)
                {
                    i = (i-j*j+1000*P)%P;
                    hashTable[i] = str;
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
