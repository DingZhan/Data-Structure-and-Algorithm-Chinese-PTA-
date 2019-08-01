#include <iostream>
#include <queue>

/*一根木头锯成两段，相当于从一个节点分配出两个子节点；而
最终分割出来的木头相当于树中的叶结点，木头越短，它的层次深度（Huffman符号表达长度）可以越深;
*/
/*因此这是Huffman编码问题，通过创建最小堆构建Huffman树,
通过每次把权值最小的两个二叉树合并，
这里使用优先队列priority_queue作为最小堆
Huffman具体细节参看<数据结构>慕课Huffman树与Huffman编码
*/
using namespace std;
int main()
{
    //这里使用优先队列作为最小堆
    priority_queue<int, std::vector<int>, std::greater<int> > minHeap;
    //sum就是Huffman树中非叶结点权值的累加和
    int i, N, sum=0, a, b;
    //读入N
    cin>>N;
    //读入N块最终长度的木头
    for(i=0; i<N; ++i)
    {
        cin>>a;
        //把该木头加入到最小堆中
        minHeap.push(a);
    }

    //或者循环条件改成 while(minHeap.size()!=1)
    for(i=0; i<N-1; ++i)
    {
        //弹出两个最短长度的木头
        a = minHeap.top();
        minHeap.pop();
        b = minHeap.top();
        minHeap.pop();
        //把两个最短长度的木头的和再次加入到最小堆中
        minHeap.push(a+b);
        //累加两块木头的长度
        sum+=a+b;
    }
    cout<<sum<<endl;
    return 0;
}
