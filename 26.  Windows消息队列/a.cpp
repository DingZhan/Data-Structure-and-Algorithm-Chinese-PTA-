#include <iostream>
#include <queue> //优先队列头文件

using namespace std;

//定义消息结构体
struct MSG
{
    //消息名
    char name[11];
    //消息优先级
    int level;
    //消息id，先来的消息id值更小
    int id;
    //消息结构比较函数
    friend bool operator <(const MSG &a, const MSG &b)
    {
        //level越大，优先级低
        if(a.level>b.level)
            return true;
        else if(a.level<b.level)
            return false;
        else
        {
            //level相同的情况下，id越小，优先级越高
            return a.id>b.id;
        }
    }

};


int main()
{
    int N, i, id=0;
    string op;
    MSG msg;
    //优先队列
    priority_queue<MSG> Q;
    //输入总消息数
    cin>>N;
    //读入所有消息
    for(i=0; i<N; ++i)
    {
        //先读入一个操作符
        cin>>op;
        //如果是添加消息
        if(op=="PUT")
        {
            //读取消息名和消息优先级
            cin>>msg.name>>msg.level;
            //设置该消息的id
            msg.id = id++;
            //添加到优先队列
            Q.push(msg);
        }
        else //读取一个消息
        {
            //如果优先队列为空
            if(Q.empty())
                cout<<"EMPTY QUEUE!\n";
            else
            {
                //获得优先队列首元素
                msg = Q.top();
                //弹出首元素
                Q.pop();
                cout<<msg.name<<endl;
            }
        }
    }
    return 0;
}
