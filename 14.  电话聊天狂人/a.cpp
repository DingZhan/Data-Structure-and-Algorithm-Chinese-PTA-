#include <iostream>
#include <map>

using namespace std;

int main()
{
    int N, i, maxCount=-1, sameNum=0;
    //��Ϊ�绰��11λ�����Բ�����unsigned int��ֻ����long long
    //��ȻҲ������char[]����Ҫ12���ֽ�,û��8���ֽ�long long����
    long long a, b, maxPhone;
    //��STL��map���������κ�һ���绰����ӳ�䵽ͨ������,��<phone, number>
    std::map<long long, int> phoneMapCounts;
    //map�ĵ�����
    std::map<long long, int>::iterator it;
    //����N
    cin>>N;
    //����N��ͨ����¼����ͨ��˫�������ô�������1
    for(i=0; i<N; ++i)
    {
        cin>>a>>b;
        ++phoneMapCounts[a];
        ++phoneMapCounts[b];
    }
    //����һ��map�������ҳ����ͨ������
    //��Ϊmap��key����phone number����key���ǰ���С�������е�
    //������������"����������˲�Ψһ���������������С�ĺ��뼰��ͨ������"
    for(it=phoneMapCounts.begin(); it!=phoneMapCounts.end(); ++it)
    {
        //�����ǰ�����Ӧ��ͨ���������ڵ�ǰ���ͨ������������¼�¼
        if(it->second>maxCount)
        {
            maxCount = it->second;
            maxPhone = it->first;
            //��ͬ��ͨ����������������Ϊ1
            sameNum = 1;
        }
        //�����ǰ�����Ӧ��ͨ���������ڵ�ǰ���ͨ�����������ۼ�����
        else if(it->second==maxCount)
        {
            ++sameNum;
        }
    }
    //������ͨ������ֻ��һ��
    if(sameNum==1)
    {
        cout<<maxPhone<<" "<<maxCount<<endl;
    }
    else
    {
        cout<<maxPhone<<" "<<maxCount<<" "<<sameNum<<endl;
    }

    return 0;
}
