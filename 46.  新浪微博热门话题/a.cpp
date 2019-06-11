#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstdlib>
#include <cstring>


//使用STL的map映射容器解决这个问题
using namespace std;

int main()
{
    //使用非同步I/O
    std::ios::sync_with_stdio(false);
    int N, i, j, k, maxRef=0, sameRefNum=0;
    //话题会存在str里面
    string str, lineStr;
    bool bSharpStart=false;
    //所有<话题, 引用次数>的映射容器
    map<string, int> strMapCounts;
    //定义两个map的迭代器
    map<string, int>::iterator it, it2;
    //每一行里可能同一个话题会出现多次，所以需要一个方法去除重复话题
    //这里使用set集合避免一行里同一话题多次修改map
    set<string> sameLineSet;

    //得到一行输入，这里是为了方便的吃掉第一行最后一个回车键
    getline(cin, lineStr);
    //获得微博总数目
    N = atoi(lineStr.c_str());
    //读入N条微博
    for(i=0; i<N; ++i)
    {
        //得到一行微博
        getline(cin, lineStr);
        //重置#出现标记为false
        bSharpStart = false;
        //扫描之前将set集合重置为空
        sameLineSet.clear();
        //扫描当前一行微博
        for(j=0; j<lineStr.size(); ++j)
        {
            //如果#符号没有出现过
            if(!bSharpStart)
            {
                //这里出现了#符号，标记为true
                if(lineStr[j]=='#')
                    bSharpStart = true;
                //继续下一循环
                continue;
            }
            //下面代码都是#符号出现了情况
            //如果当前符号又是#字符，则说明这是第二个#符号，需要添加本话题了
            if(lineStr[j]=='#')
            {
                //重置#符号没有出现过
                bSharpStart=false;
                //如果两个#之间的话题内容非空
                if(str.size())
                {
                    //吃掉话题末尾可能的最后一个空格
                    if(str[str.size()-1]==' ')
                        str.erase(str.end()-1);
                    //如果这个话题在本行中已经出现过，则继续下一轮扫描
                    if(sameLineSet.find(str)!=sameLineSet.end())
                    {
                        //记得一定要将话题清空
                        str.clear();
                        continue;
                    }
                    //debug
                    //cout<<str<<"\n";
                    //把该话题加入到本行set集合中
                    sameLineSet.insert(str);
                    //在映射容器中查找该话题
                    it = strMapCounts.find(str);
                    //如果迭代器指向容器末尾，则该话题第一次出现，所以要添加该话题，同时设置引用次数为1
                    if(it==strMapCounts.end())
                        strMapCounts[str]=1;
                    else //该话题已经在容器中出现过，所以只需要累加一次引用
                        ++it->second;
                    //记得清空该话题
                    str.clear();
                }
            }
            else //如果当前符号不是第二个#字符
            {
                //如果当前符号是字母或者数字
                if(isalpha(lineStr[j])||isdigit(lineStr[j]))
                {
                    //如果话题为空，则把第一个字母变成大写添加到话题
                    if(str.empty())
                        str.push_back(toupper(lineStr[j]));
                    else//否则把字母变成小写添加到话题
                        str.push_back(tolower(lineStr[j]));
                }
                else//如果当前字符是其他类型字符
                {
                    //如果话题已经非空，则需要额外添加一个空格到话题末尾
                    if(str.size())
                    {
                        //需要避免两个连续空格的情况
                        if(str[str.size()-1]!=' ')
                            str.push_back(' ');
                    }
                }

            }
        }
    }

    //开始扫描这个映射容器，maxRef表示最多引用的话题次数
    //it2用来记录最大次数的迭代器
    //需要说明的是map容器的key默认是按字典顺序遍历的，所以满足”如果这样的话题不唯一，则输出按字母序最小的话题“
    for(it=strMapCounts.begin(); it!=strMapCounts.end(); ++it)
    {
        //如果当前话题的引用次数超过最大次数
        if(it->second>maxRef)
        {
            //设置最大次数
            maxRef = it->second;
            //记录该迭代器位置
            it2 = it;
            //设置相同引用次数的话题重复个数为0
            sameRefNum = 0;
        }
        else if(it->second==maxRef) //如果引用次数相同，则累加sameRefNum
            ++sameRefNum;
    }
    //打印最终结果
    cout<<it2->first<<"\n"<<it2->second<<"\n";
    if(sameRefNum)
        cout<<"And "<<sameRefNum<<" more ...\n";

    return 0;
}
