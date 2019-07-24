#include <iostream>
#include <string>
#include <stack>

using namespace std;


//具体算法，参考MOOC(数据结构-何钦明，陈越) 线性结构-堆栈
/*从头到尾读取中缀表达式的每个对象，对不同对象按不同情况处理。
1.运算数：直接输出
2.左括号：压入堆栈
3.右括号: 将栈顶的运算符弹出并输出，直到遇到左括号(出栈，不输出)
4.运算符:
  :若优先级大于栈顶运算符时，则把它压栈；
  :若优先级小于等于栈顶运算符时，将栈顶运算符弹出并输出；再比较新的栈顶运算符，
  直到该运算符大于栈顶运算符优先级为止，然后将该运算符压栈；
5.若各对象处理完毕，则把堆栈中存留的运算符一并输出。
*/


int main()
{
    stack<char> S1;
    char c;
    int i;
    bool bFirstPrint=true;
    std::string data;
    std::string str;

    //得到一行中缀表达式
    getline(cin, str);
    for(i=0; i<str.size(); ++i)
    {
        c = str[i];
        //如果数据串为空，而此时出现字符'-',则如果当前为第一个字符或者是左括号后的第一个字符，
        //则认为其表示负号，而不是减号
        if(data.empty() && c=='-' && (i==0||str[i-1]=='('))
        {
            //添加负号
            data = "-";
            //读取下一个字符
            continue;
        }
        //如果数据串为空，而此时出现字符'+',如果当前为第一个字符或者是左括号后的第一个字符
        //则认为其表示正号，而不是加号
        else if(data.empty()&& c=='+' && (i==0||str[i-1]=='(') )
        {
            data = "+";
            continue;
        }

        //如果当前字符是数字或者是'.'，则加到数字串中
        if(isdigit(c)||c=='.')
        {
            data+=c;
        }
        else
        {
            //当前c是符号，所以先把之前存储的数字串打印出来
            if(data.size())
            {
                //如果不是第一次打印，则先打印空格
                if(!bFirstPrint)
                    cout<<" ";
                //如果数字串前面有多余的+号，则去掉该+号，否则有一个测试点过不了
                if(data[0]=='+')
                    data.erase(data.begin());
                //打印数字串
                cout<<data;
                //设置非第一打印
                bFirstPrint = false;
                //清除数字串
                data.clear();
            }

            //如果当前c是四则运算符号
            if(c=='+'||c=='-'||c=='*'||c=='/')
            {
                do
                {
                    //如果符号堆栈为空，退出循环
                    if(S1.empty())
                        break;
                    //当前符号优先级大于栈顶符号优先级，退出循环
                    //在堆栈内，左括号的优先级是最低的符号
                    else if(S1.top()=='('||
                            (c=='*'||c=='/') && (S1.top()=='+'||S1.top()=='-'))
                        break;
                    else
                    {
                        //优先级小于等于栈顶运算符时，将栈顶运算符弹出并输出；
                        //再比较新的栈顶运算符
                        if(!bFirstPrint)
                            cout<<" ";
                        cout<<S1.top();
                        bFirstPrint = false;
                        S1.pop();
                    }
                }while(!S1.empty());
                //把当前符号加到符号堆栈中
                S1.push(c);
            }
            //如果当前符号是左括号，则添加到符号堆栈中
            else if(c=='(')
                S1.push(c);
            //如果当前符号是右括号，则将栈顶的运算符弹出并输出，直到遇到左括号(出栈，不输出)
            else if(c==')')
            {
                while(true)
                {
                    //如果是左括号，则弹出左括号，但不打印
                    if(S1.top()=='(')
                    {
                        S1.pop();
                        break;
                    }
                    //栈顶的运算符弹出并输出
                    if(!bFirstPrint)
                        cout<<" ";
                    //打印栈顶
                    cout<<S1.top();
                    //弹出栈顶
                    S1.pop();
                    bFirstPrint = false;
                }
            }
        }
    }

    //如果当前数字串不为空，则输出数字串
    if(data.size())
    {
        //如果不是第一次打印，则先打印空格
        if(!bFirstPrint)
            cout<<" ";
        //如果数字串前面有多余的+号，则去掉该+号，否则有一个测试点过不了
        if(data[0]=='+')
            data.erase(data.begin());
        //打印数字串
        cout<<data;
        //设置非第一打印
        bFirstPrint = false;
        //清除数字串
        data.clear();
    }
    //如果堆栈里还有内容，全部弹出打印
    while(!S1.empty())
    {
        if(!bFirstPrint)
            cout<<" ";
        //打印栈顶
        cout<<S1.top();
        //弹出栈顶
        S1.pop();
        bFirstPrint = false;
    }
    cout<<endl;
    return 0;
}
