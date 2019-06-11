#include <iostream>
#include <vector>
#include <algorithm>

//使用vector+快速排序
using namespace std;

int main()
{
    //禁止同步，使用高速I/O
    std::ios::sync_with_stdio(false);
    vector<int> datas;
    int i, N, M, v;
    //读入总富翁人数和前M个富翁人数
    cin>>N>>M;
    //读入所有富翁的资产
    for(i=0; i<N; ++i)
    {
        //读入资产
        cin>>v;
        //添加到vector末尾
        datas.push_back(v);
    }
    std::sort(datas.begin(), datas.end(), std::greater<int>() );
    //打印前M个富翁
    for(i=0; i<M; ++i)
    {
        //如果M个数大于N，有可能vector已经空了
        if(i>=datas.size())
            break;
        //空格采用前置打印方法
        if(i)
            cout<<" ";
        //打印元素
        cout<<datas[i];
    }
    cout<<endl;
    return 0;
}
