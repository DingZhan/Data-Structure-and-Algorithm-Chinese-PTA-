#include <iostream>
#include <queue> //���ȶ���ͷ�ļ�

using namespace std;

//������Ϣ�ṹ��
struct MSG
{
    //��Ϣ��
    char name[11];
    //��Ϣ���ȼ�
    int level;
    //��Ϣid����������Ϣidֵ��С
    int id;
    //��Ϣ�ṹ�ȽϺ���
    friend bool operator <(const MSG &a, const MSG &b)
    {
        //levelԽ�����ȼ���
        if(a.level>b.level)
            return true;
        else if(a.level<b.level)
            return false;
        else
        {
            //level��ͬ������£�idԽС�����ȼ�Խ��
            return a.id>b.id;
        }
    }

};


int main()
{
    int N, i, id=0;
    string op;
    MSG msg;
    //���ȶ���
    priority_queue<MSG> Q;
    //��������Ϣ��
    cin>>N;
    //����������Ϣ
    for(i=0; i<N; ++i)
    {
        //�ȶ���һ��������
        cin>>op;
        //����������Ϣ
        if(op=="PUT")
        {
            //��ȡ��Ϣ������Ϣ���ȼ�
            cin>>msg.name>>msg.level;
            //���ø���Ϣ��id
            msg.id = id++;
            //��ӵ����ȶ���
            Q.push(msg);
        }
        else //��ȡһ����Ϣ
        {
            //������ȶ���Ϊ��
            if(Q.empty())
                cout<<"EMPTY QUEUE!\n";
            else
            {
                //������ȶ�����Ԫ��
                msg = Q.top();
                //������Ԫ��
                Q.pop();
                cout<<msg.name<<endl;
            }
        }
    }
    return 0;
}
