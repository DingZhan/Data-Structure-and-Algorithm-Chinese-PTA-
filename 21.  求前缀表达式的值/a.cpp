#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

/*ǰ׺���ʽ��ֵ:
  Ҫ��������ɨ����ʽ����������֣���ŵ�����ջ�У�
  ��Ϊ��������������ջ�е����������ݣ����м��㣬Ȼ�󽫼������ٴ�ѹ������ջ��
  ɨ�赽���ʽ�����ʱɨ��������������ջ��Ψһ�����ݾ�����������ս����
*/
int main()
{
    //��һ���ַ�������ȡ�ķ�������
    std::vector<string> tokens;
    //����ջ
    std::stack<double> dataStack;
    string lineStr, token;
    double data1, data2;

    //�õ�һ���ַ���
    std::getline(cin, lineStr);
    //�������ַ�������ʽ���ַ���
    istringstream iss(lineStr);
    //��ȡÿ�����ţ��ַ������Կո�ָ���
    while(true)
    {
        //��ȡһ�����ţ��ַ�����
        iss>>token;
        //�����ȡʧ�ܣ�������ȡ����
        if(iss.fail())
            break;
        //�Ѷ�ȡ�ķ��ż����������
        tokens.push_back(token);
    }
    int i;
    //���������������
    for(i=(int)tokens.size()-1; i>=0; --i)
    {
        //�����ǰ���Ŵ������������������Ҫ������ջ�е����������ݽ��м���
        if(tokens[i].size()==1 &&(
           tokens[i][0]=='+'||
           tokens[i][0]=='-'||
           tokens[i][0]=='*'||
           tokens[i][0]=='/'))
        {
            //�������ջ��û������������������ǷǷ�ǰ׺���ʽ�������ջȻ���˳�ѭ��
            if(dataStack.size()<2)
            {
                //error happened, so clear stack
                while(!dataStack.empty())
                    dataStack.pop();
                break;
            }
            //������ջ�е����������ݽ��м���
            data1 = dataStack.top();
            dataStack.pop();
            data2 = dataStack.top();
            dataStack.pop();
            if(tokens[i][0]=='+')
                data1 = data1+data2;
            else if(tokens[i][0]=='-')
                data1 = data1-data2;
            else if(tokens[i][0]=='*')
                data1 = data1*data2;
            else if(tokens[i][0]=='/')
            {
                if(data2==0)
                {
                    //�����쳣����һ�����Ե㣬���Ա��봦����쳣
                    //�����ջȻ���˳�ѭ��
                    //error happened, so clear stack
                    while(!dataStack.empty())
                        dataStack.pop();
                    break;
                }
                data1 = data1/data2;
            }
            //�Ѽ�������ݽ��ѹ�����ݶ�ջ
            dataStack.push(data1);
            //������һ�η��Ž���
            continue;
        }
        else
            //��ǰ���������֣��Ѹ�����ѹ�����ݶ�ջ
            dataStack.push(atof(tokens[i].c_str()));
    }

    //����������ݶ�ջ��Ԫ�ظ�����Ϊ1����˵���ǷǷ�ǰ׺���ʽ
    if(dataStack.size()!=1)
        cout<<"ERROR"<<endl;
    else
        cout<<std::fixed<<std::setprecision(1)<<dataStack.top()<<endl;

    return 0;
}
