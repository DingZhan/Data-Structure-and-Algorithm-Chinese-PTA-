#include <iostream>
using namespace std;

//ָ������ֵ���1000������Ԥ��2000���Ԫ��
#define MAX_N 2003

struct Item
{
    int c; //ϵ��, coefficient
    int f; //ָ��, factor
};

int main()
{
    //����ʽ��
    Item items[MAX_N];
    int i=0, n, c, f;
    //�Ƿ��Ǵ�ӡ�ĵ�һ��
    bool bFirstPrint=true;
    while(cin>>c>>f)
    {
        items[i].c = c;
        items[i].f = f;
        ++i;
        if(f<0)
            break;
    }
    //��¼n
    n = i;

    //��ÿһ��ȡ����
    for(i=0; i<n; ++i)
    {
        //���ȡ������ϵ����Ϊ0
        if(items[i].c*items[i].f)
        {
            //����ж�һ��Ҫ������ϵ����Ϊ0���棬�����д�
            if(!bFirstPrint)
                cout<<" ";
            //��ӡ��ϵ������ָ��
            cout<<items[i].c*items[i].f<<" "<<items[i].f-1;
            //��һ�δ�ӡ���Ϊfalse
            bFirstPrint = false;
        }
    }
    //���ĿǰΪֹ��û�д�ӡ����˵����������ʽֻ�г�������Ҫ��ӡ��0 0
    if(bFirstPrint)
        cout<<"0 0";
    cout<<endl;
    return 0;
}
