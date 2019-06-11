#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <iomanip>

//使用STL的set集合容器解决这个问题
using namespace std;

int main()
{
    //使用非同步I/O
    std::ios::sync_with_stdio(false);
    int N, M, i, j, id1, id2;
    string str, lineStr;
    //单词集合，不用vector，因为一篇文章中可能多次出现同一个单词
    std::set<string> strSets;
    //每篇文章的所有有效单词集合
    std::vector<std::set<string> > strSetss;

    //输入文件数
    cin>>N;
    //读入N篇文章
    for(i=0; i<N; ++i)
    {
        //清空字符串集合
        strSets.clear();
        //读入本篇文章，一行行读
        while(true)
        {
            //一行行读
            getline(cin, lineStr);
            //如果碰到文章结束符，则退出循环
            if(lineStr=="#")
                break;
            //当前扫描的字符串重置为空
            str="";
            //扫描整行文本
            for(j=0; j<lineStr.size(); ++j)
            {
                //如果碰到非字符，则将之前已扫描的字符加入字符集和
                if(!isalpha(lineStr[j]))
                {
                    //如果当前已扫描的字符长度>=3(有效长度)
                    if(str.size()>=3)
                    {
                        //如果字符长度>10,则末尾截断
                        if(str.size()>10)
                            str.erase(str.begin()+10, str.end());
                        //将该字符串插入文本字符串集合
                        strSets.insert(str);
                    }
                    //记得重置当前扫描的单词为空
                    str="";
                }
                else//将当前字符添加到当前扫描的字符串，记得添加之前转小写
                    str.push_back(tolower(lineStr[j]));
            }
            //一行扫描结束后，有可能当前扫描的字符串非空，所以需要再处理一下
            if(str.size()>=3)
            {
                if(str.size()>10)
                    str.erase(str.begin()+10, str.end());
                strSets.insert(str);
            }
        }
        //debug
//    std::set<string>::iterator strSetIter;
 //       for(strSetIter=strSets.begin(); strSetIter!=strSets.end(); ++strSetIter)
 //           cout<<*strSetIter<<"*\n";
        //将本篇文章中的有效单词集合添加到集合的vector容器中
        strSetss.push_back(strSets);
    }
    //读入查询总数
    cin>>M;
    //读入每条查询记录
    for(i=0; i<M; ++i)
    {
        //读入文章1和文章2的编号
        cin>>id1>>id2;
        //得到文章1的单词集合
        std::set<string>& strs1 = strSetss[id1-1];
        //得到文章2的单词集合
        std::set<string>& strs2 = strSetss[id2-1];
        std::vector<string> result;
        //用集合函数获得两个集合的交集
        set_intersection(strs1.begin(), strs1.end(),
                              strs2.begin(), strs2.end(), back_inserter(result));
        //1位小数打印交集比率
        cout<<std::fixed<<setprecision(1)<<\
            result.size()*100.0/(strs1.size()+strs2.size()-result.size())<<"%\n";
    }
    return 0;
}
