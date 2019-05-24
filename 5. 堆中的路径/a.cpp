#include <iostream>

using namespace std;

#define MAX_N 1002 //考虑数组第一个元素做哨兵
#define MAX_M 1000
#define MIN_VALUE -1000000

class MinHeap
{
public:
    MinHeap()
    {
        m_Size = 0;
        m_Elements[0] = MIN_VALUE; //哨兵
    }

    void Insert(int data)
    {
        int child;
        //当前要插入的元素位于队的最后, ++m_Size是因为哨兵
        child = ++m_Size;
        //如果当前待插入元素的值比父节点要小
        while(m_Elements[child/2]>data)
        {
            //则把父节点下移到当前儿子节点
            m_Elements[child] = m_Elements[child/2];
            //继续向上搜索
            child/=2;
        }
        //最后插入当前元素
        m_Elements[child] = data;
    }

    //用一种效率不高但可以接受的方法创建一个堆，即一次次调用Insert
    void BuildHeap(int *datas, int n)
    {
        int i;
        m_Size = 0;
        for(i=0; i<n; ++i)
            Insert(datas[i]);
    }

    //从下向上打印节点值
    void PrintPathToRoot(int id)
    {
        bool bFirstPrint=true;
        while(id>0)
        {
            if(!bFirstPrint)
                cout<<" ";
            cout<<m_Elements[id];
            bFirstPrint = false;
            id/=2;
        }
        cout<<"\n";
    }
private:
    int m_Size;
    int m_Elements[MAX_N];
};

int main()
{
    MinHeap minHeap;
    int datas[MAX_N], ids[MAX_M];
    int N, M, i;

    cin>>N>>M;

	//理论上可以直接调用N次minHeap.Insert，但实际工程中有O(log(N))方法建堆
    for(i=0; i<N; ++i)
        cin>>datas[i];

	//下标是从1开始的，所以0位置放置哨兵正好
    for(i=0; i<M; ++i)
        cin>>ids[i];

	//建堆
    minHeap.BuildHeap(datas, N);

    //自下向上打印节点路径
    for(i=0; i<M; ++i)
        minHeap.PrintPathToRoot(ids[i]);

    return 0;
}
