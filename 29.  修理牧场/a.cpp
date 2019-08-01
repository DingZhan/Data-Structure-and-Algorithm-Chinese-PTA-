#include <iostream>
#include <queue>

/*һ��ľͷ������Σ��൱�ڴ�һ���ڵ����������ӽڵ㣻��
���շָ������ľͷ�൱�����е�Ҷ��㣬ľͷԽ�̣����Ĳ����ȣ�Huffman���ű�ﳤ�ȣ�����Խ��;
*/
/*�������Huffman�������⣬ͨ��������С�ѹ���Huffman��,
ͨ��ÿ�ΰ�Ȩֵ��С�������������ϲ���
����ʹ�����ȶ���priority_queue��Ϊ��С��
Huffman����ϸ�ڲο�<���ݽṹ>Ľ��Huffman����Huffman����
*/
using namespace std;
int main()
{
    //����ʹ�����ȶ�����Ϊ��С��
    priority_queue<int, std::vector<int>, std::greater<int> > minHeap;
    //sum����Huffman���з�Ҷ���Ȩֵ���ۼӺ�
    int i, N, sum=0, a, b;
    //����N
    cin>>N;
    //����N�����ճ��ȵ�ľͷ
    for(i=0; i<N; ++i)
    {
        cin>>a;
        //�Ѹ�ľͷ���뵽��С����
        minHeap.push(a);
    }

    //����ѭ�������ĳ� while(minHeap.size()!=1)
    for(i=0; i<N-1; ++i)
    {
        //����������̳��ȵ�ľͷ
        a = minHeap.top();
        minHeap.pop();
        b = minHeap.top();
        minHeap.pop();
        //��������̳��ȵ�ľͷ�ĺ��ٴμ��뵽��С����
        minHeap.push(a+b);
        //�ۼ�����ľͷ�ĳ���
        sum+=a+b;
    }
    cout<<sum<<endl;
    return 0;
}
