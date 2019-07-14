#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//贪心算法：
//1.正优惠券降序排列
//2.负优惠券升序排列
//3.正商品价值降序排列
//4.负商品价值升序排列
//5.正优惠券和正商品价值数组同步乘积并累加求和,负优惠券和负商品价值数组同步乘积并累加求和
int main()
{
    //关闭与stdio的同步
    std::ios::sync_with_stdio(false);
    int i, j, N, M, v;
    //用long long保险些，考虑可能溢出
    long long sum=0;
    //将优惠卷和商品价值分为正负，所以用四个vector存储数据
    std::vector<int> couponPos, couponNeg, valuePos, valueNeg;
    cin>>N;
    for(i=0; i<N; ++i)
    {
        cin>>v;
        //正负优惠卷存入不同的vector
        if(v>0)
            couponPos.push_back(v);
        else
            couponNeg.push_back(v);
    }
    cin>>M;
    for(i=0; i<M; ++i)
    {
        cin>>v;
        //正负商品价值存入不同的vector
        if(v>0)
            valuePos.push_back(v);
        else
            valueNeg.push_back(v);
    }
    //正优惠券降序排列
    std::sort(couponPos.begin(), couponPos.end(), std::greater<int>());
    //负优惠券升序排列
    std::sort(couponNeg.begin(), couponNeg.end());
    //正商品价值降序排列
    std::sort(valuePos.begin(), valuePos.end(), std::greater<int>());
    //负商品价值升序排列
    std::sort(valueNeg.begin(), valueNeg.end());
    //贪心算法：正优惠券和正商品价值数组同步乘积并累加求和
    for(i=0; i<couponPos.size() && i<valuePos.size(); ++i)
        sum+=(long long)(couponPos[i])*(valuePos[i]);
    //负优惠券和负商品价值数组同步乘积并累加求和
    for(i=0; i<couponNeg.size() && i<valueNeg.size(); ++i)
        sum+=(long long)(couponNeg[i])*(valueNeg[i]);
    cout<<sum<<endl;
    return 0;
}
