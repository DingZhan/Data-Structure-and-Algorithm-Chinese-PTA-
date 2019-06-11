#include <iostream>
#include <queue>

//使用STL的优先队列解决这个问题
using namespace std;

int main()
{
    //禁止同步，使用高速I/O
    std::ios::sync_with_stdio(false);
    //小顶堆的写法
//    priority_queue<int, vector<int>, greater<int> > datas;
    //使用优先队列作为大顶堆
    priority_queue<int> datas;
    int i, N, M, v;
    //读入总富翁人数和前M个富翁人数
    cin>>N>>M;
    //读入所有富翁的资产
    for(i=0; i<N; ++i)
    {
        //读入资产
        cin>>v;
        //插入堆
        datas.push(v);
    }
    //打印前M个富翁
    for(i=0; i<M; ++i)
    {
        //如果M个数大于N，有可能优先队列已经空了
        if(datas.empty())
            break;
        //空格采用前置打印方法
        if(i)
            cout<<" ";
        //打印堆顶元素
        cout<<datas.top();
        //弹出堆顶元素
        datas.pop();
    }
    cout<<endl;
    return 0;
}
