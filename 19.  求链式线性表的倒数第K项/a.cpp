#include <iostream>
#include <list>
using namespace std;

int main()
{
    //һ��Ҫȡ��I/Oͬ��������ᳬʱ
    std::ios::sync_with_stdio(false);
    //ʹ��STL��list��Ϊ�����ʾ
    std::list<int> datas;
    //������K�����ĵ�����
    std::list<int>::iterator desIter;
    int count=0, v, K;
    //����K
    cin>>K;
    while(true)
    {
        cin>>v;
        //��ϸ���⣬����д��-1
        if(v<0)
            break;
        //�����ݼӵ�����β��
        datas.push_back(v);
        //������+1
        ++count;
        //�������������ΪK�����һ��Ԫ��λ�þ��ǵ�����K��Ԫ��λ��
        if(count==K)
            desIter = datas.begin();
        else if(count>K)//�������������K���������ÿ�������ƶ�һ��λ��
            ++desIter;
    }
    if(count>=K)
        cout<<*desIter<<endl;
    else
        cout<<"NULL\n";
    return 0;
}
