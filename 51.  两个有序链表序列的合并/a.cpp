#include <iostream>
#include <list>

using namespace std;

int main()
{
	//用STL的list模拟链表，实际上，对于本题用vector也可以，因为程序中并没有链表插入、删除操作
    std::list<int> S1, S2;
	//定义两个链表的两个迭代器，用来访问链表
    std::list<int>::iterator it1, it2;
    int v;
	//创建链表1
    while(cin>>v)
    {
        if(v==-1)
            break;
        S1.push_back(v);
    }
	//创建链表2
    while(cin>>v)
    {
        if(v==-1)
            break;
        S2.push_back(v);
    }
	//bEmpty表示没打印过任何内容，初始为true，表示没有打印过任何结点
    bool bEmpty=true;
	//用两个迭代器顺序访问两个链表，两个迭代器的步进速度不是同步的
    for(it1=S1.begin(), it2=S2.begin(); it1!=S1.end()&&it2!=S2.end(); )
    {
		//如果不是第一次打印，则先打印个空格
        if(!bEmpty)
            cout<<" ";
		//迭代器1指向的值小于迭代器2指向的值，所以打印小的值，同时步进迭代器1
        if(*it1<*it2)
        {
            cout<<*it1;
            ++it1;
        }
		//迭代器1当前值大于迭代器2指向的值，所以打印小的值，同时步进迭代器2
        else if(*it1>*it2)
        {
            cout<<*it2;
            ++it2;
        }
        else //两个值一样，所以都要打印，并且同步前进
        {
            cout<<*it1;
            cout<<" "<<*it2;
            ++it1;
            ++it2;
        }
		//设置成非第一次打印
        bEmpty = false;
    }
	//如果迭代器1还没有访问到链表末尾，则打印所有剩余结点
    while(it1!=S1.end())
    {
        if(!bEmpty)
            cout<<" ";
        cout<<*it1;
        ++it1;
        bEmpty = false;
    }
	//如果迭代器2还没有访问到链表末尾，则打印所有剩余结点
    while(it2!=S2.end())
    {
        if(!bEmpty)
            cout<<" ";
        cout<<*it2;
        ++it2;
        bEmpty = false;
    }

	//如果没有打印过任何结点，则打印NULL
    if(bEmpty)
        cout<<"NULL";
    cout<<"\n";
    return 0;
}
