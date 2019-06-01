#include <iostream>
#include <list>
using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    std::list<int> datas;
    std::list<int>::iterator desIter;
    int count=0, v, K;
    cin>>K;
    while(true)
    {
        cin>>v;
        if(v<0)
            break;
        datas.push_back(v);

        ++count;
        if(count==K)
            desIter = datas.begin();
        else if(count>K)
            ++desIter;
    }
    if(count>=K)
        cout<<*desIter<<endl;
    else
        cout<<"NULL\n";
    return 0;
}
