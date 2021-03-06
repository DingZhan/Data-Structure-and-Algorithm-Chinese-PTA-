#include <iostream>
using namespace std;

//指数绝对值最大1000，所以预留2000多个元素
#define MAX_N 2003

struct Item
{
    int c; //系数, coefficient
    int f; //指数, factor
};

int main()
{
    //多项式项
    Item items[MAX_N];
    int i=0, n, c, f;
    //是否是打印的第一项
    bool bFirstPrint=true;
    while(cin>>c>>f)
    {
        items[i].c = c;
        items[i].f = f;
        ++i;
        if(f<0)
            break;
    }
    //记录n
    n = i;

    //对每一项取导数
    for(i=0; i<n; ++i)
    {
        //如果取导后新系数不为0
        if(items[i].c*items[i].f)
        {
            //这个判断一定要放在新系数不为0里面，否则有错
            if(!bFirstPrint)
                cout<<" ";
            //打印新系数和新指数
            cout<<items[i].c*items[i].f<<" "<<items[i].f-1;
            //第一次打印标记为false
            bFirstPrint = false;
        }
    }
    //如果目前为止还没有打印，则说明上述多项式只有常数项，因此要打印个0 0
    if(bFirstPrint)
        cout<<"0 0";
    cout<<endl;
    return 0;
}
