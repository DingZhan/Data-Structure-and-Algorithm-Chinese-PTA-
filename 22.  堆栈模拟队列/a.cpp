#include <iostream>
#include <stack>

using namespace std;

int main()
{
    int N1, N2, n, data;
    char op;
    //��S1�������е���ڣ�������β��λ�ã���S2�������еĳ��ڣ�������ǰ��λ��
    stack<int> S1, S2;
    //����������ջ�ĳ�������
    cin>>N1>>N2;
    //��ջʵ�ʿ�ʹ�õĳ���Ϊ��Сֵ
    n = min(N1, N2);
    //��������
    while(true)
    {
        //�������������
        cin>>op;
        //�������
        if(op=='A')
        {
            //��������
            cin>>data;
            //�������β��λ�õĿռ仹δ������ֱ����ӵ�����β�����ڵĶ�ջ
            if(S1.size()<n)
                S1.push(data);
            else
            {
                //S1�����������ʱS2�ǿգ�������������ݣ���ΪS2�Ƕ��е�front��
                //��S2�ǿյ�����£�S1�������ǲ���ת�õ�S1��
                if(!S2.empty())
                    cout<<"ERROR:Full\n";
                else
                {
                    //S2Ϊ�գ����Կ����Ƚ�S1����ȫ��ת�õ�S2��Ȼ�����������ӵ�S1
                    while(!S1.empty())
                    {
                        //S1����ת�õ�S2��
                        S2.push(S1.top());
                        S1.pop();
                    }
                    //��data��ӵ�����β��
                    S1.push(data);
                }
            }
        }
        //��������
        else if(op=='D')
        {
            //���S2�ǿգ�������ǰ�������ݣ����ӡ������
            if(!S2.empty())
            {
                //��ӡǰ������
                cout<<S2.top()<<endl;
                //����
                S2.pop();
            }
            else
            {
                //����ǰ��Ϊ�գ�����Ҫ������β�����ݵ��õ�����ǰ��
                //��ʱ���S1ҲΪ�գ�������β��ҲΪ�գ�����������Ϊ��
                if(S1.empty())
                    cout<<"ERROR:Empty\n";
                else
                {
                    //������β�����ݵ��õ�����ǰ��
                    while(!S1.empty())
                    {
                        S2.push(S1.top());
                        S1.pop();
                    }
                    //��ӡ����ǰ������
                    cout<<S2.top()<<endl;
                    //����
                    S2.pop();
                }
            }
        }
        //termination
        else if(op=='T')
            break;
    }
    return 0;
}
