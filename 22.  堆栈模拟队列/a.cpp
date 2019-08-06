#include <iostream>
#include <stack>

using namespace std;

int main()
{
    int N1, N2, n, data;
    char op;
    //把S1当作队列的入口，即队列尾部位置；把S2当作队列的出口，即队列前部位置
    stack<int> S1, S2;
    //读入两个堆栈的长度限制
    cin>>N1>>N2;
    //堆栈实际可使用的长度为最小值
    n = min(N1, N2);
    //读入命令
    while(true)
    {
        //读入命令操作符
        cin>>op;
        //入队命令
        if(op=='A')
        {
            //读入数据
            cin>>data;
            //如果队列尾部位置的空间还未满，则直接添加到队列尾部所在的堆栈
            if(S1.size()<n)
                S1.push(data);
            else
            {
                //S1已满，如果此时S2非空，则不能添加新数据；因为S2是队列的front，
                //在S2非空的情况下，S1的数据是不能转置到S1的
                if(!S2.empty())
                    cout<<"ERROR:Full\n";
                else
                {
                    //S2为空，所以可以先将S1内容全部转置到S2，然后把新数据添加到S1
                    while(!S1.empty())
                    {
                        //S1内容转置到S2中
                        S2.push(S1.top());
                        S1.pop();
                    }
                    //把data添加到队列尾部
                    S1.push(data);
                }
            }
        }
        //出队命令
        else if(op=='D')
        {
            //如果S2非空，即队列前部有数据，则打印并出队
            if(!S2.empty())
            {
                //打印前部数据
                cout<<S2.top()<<endl;
                //出队
                S2.pop();
            }
            else
            {
                //队列前部为空，则需要将队列尾部数据倒置到队列前部
                //此时如果S1也为空，即队列尾部也为空，则整个队列为空
                if(S1.empty())
                    cout<<"ERROR:Empty\n";
                else
                {
                    //将队列尾部数据倒置到队列前部
                    while(!S1.empty())
                    {
                        S2.push(S1.top());
                        S1.pop();
                    }
                    //打印队列前部数据
                    cout<<S2.top()<<endl;
                    //出队
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
