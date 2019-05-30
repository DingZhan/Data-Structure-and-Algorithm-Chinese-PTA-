#include <iostream>
#include <list>

using namespace std;

int main()
{
    std::list<int> S1, S2;
    std::list<int>::iterator it1, it2;
    int v;
    while(cin>>v)
    {
        if(v==-1)
            break;
        S1.push_back(v);
    }
    while(cin>>v)
    {
        if(v==-1)
            break;
        S2.push_back(v);
    }
    bool bEmpty=true;
    for(it1=S1.begin(), it2=S2.begin(); it1!=S1.end()&&it2!=S2.end(); )
    {
        if(*it1<*it2)
            ++it1;
        else if(*it1>*it2)
            ++it2;
        else
        {
            if(!bEmpty)
                cout<<" ";
			//总感觉有bug，因为如果两个链表里都有完全重复的两个结点 S1(a->a) S2(a->a)，那么到底要输出几个a?
            cout<<*it1;
            bEmpty = false;
            ++it1;
            ++it2;
        }
    }
    if(bEmpty)
        cout<<"NULL";
    cout<<"\n";
    return 0;
}
