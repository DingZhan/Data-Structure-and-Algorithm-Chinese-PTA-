#include <iostream>
#include <list>
using namespace std;

int main()
{
    //一定要取消I/O同步，否则会超时
    std::ios::sync_with_stdio(false);
    //使用STL的list作为链表表示
    std::list<int> datas;
    //倒数第K个结点的迭代器
    std::list<int>::iterator desIter;
    int count=0, v, K;
    //读入K
    cin>>K;
    while(true)
    {
        cin>>v;
        //仔细读题，不能写成-1
        if(v<0)
            break;
        //把数据加到链表尾部
        datas.push_back(v);
        //计数器+1
        ++count;
        //如果计数器正好为K，则第一个元素位置就是倒数第K个元素位置
        if(count==K)
            desIter = datas.begin();
        else if(count>K)//如果计数器超过K，则迭代器每次往后移动一个位置
            ++desIter;
    }
    if(count>=K)
        cout<<*desIter<<endl;
    else
        cout<<"NULL\n";
    return 0;
}
