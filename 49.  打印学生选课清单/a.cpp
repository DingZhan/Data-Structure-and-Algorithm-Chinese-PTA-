#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;


int main()
{
    int N, K, i, n, j, classID;
    string name;
    //用一个map记录选课学生的所有选课课程号
    map<string, std::vector<short> > nameMapClassIDs;
    //迭代器
    map<string, std::vector<short> >::iterator it;
    //读入学生总数和课程总数
    cin>>N>>K;
    //读入每门课的选课信息
    for(i=0;i<K; ++i)
    {
        //读入课程号和该课程选课总人数
        cin>>classID>>n;
        //读入所有选课学生的名字
        for(j=0; j<n; ++j)
        {
            //读入名字
            cin>>name;
            //把名字所选课程号加入到map
            nameMapClassIDs[name].push_back(classID);
        }
    }

    //用vector记录N个名字
    vector<string> names;
    names.resize(N);
    for(i=0; i<N; ++i)
        cin>>names[i];

    for(i=0; i<N; ++i)
    {
        //找到该生在map中的迭代器位置
        it = nameMapClassIDs.find(names[i]);
        //如果该学生一门课都没选，即没有记录，没有这句会有段错误
        if(it==nameMapClassIDs.end())
        {
            cout<<names[i]<<" 0\n";
            continue;
        }
        //对该生所选课程按课程号进行排序
        sort(it->second.begin(), it->second.end());
        //打印名字和选课总数
        cout<<names[i]<<" "<<it->second.size();
        //打印所有选课号
        for(j=0; j<it->second.size(); ++j)
            cout<<" "<<it->second[j];
        cout<<"\n";
    }

    return 0;
}
