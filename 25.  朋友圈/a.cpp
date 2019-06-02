#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main()
{
    int N, M, i, j, k, t, n, studentID;
    //每个俱乐部里的所有学生信息
    std::vector<std::vector<int> > clubStudents;
    //<学生, 加入的俱乐部s> 键值对
    std::map<int, std::vector<int> > studentMapClubIDs;
    //map的迭代器
    std::map<int, std::vector<int> >::iterator iter;

    //输入学生数和俱乐部数目
    cin>>N>>M;
    //resize分配M个俱乐部
    clubStudents.resize(M);
    for(i=0; i<M; ++i)
    {
        //读入第i个俱乐部的学生数目
        cin>>n;
        //读入俱乐部学生id
        for(j=0; j<n; ++j)
        {
            cin>>studentID;
            //把该学生加入到当前俱乐部
            clubStudents[i].push_back(studentID);
            //把该俱乐部id加入到该学生参加的俱乐部
            studentMapClubIDs[studentID].push_back(i);
        }
    }

    //合并俱乐部
    std::vector<int> clubSeedIDs;
    std::vector<bool> bClubVisits, bStudentVisits;
    int clubID;
    int maxStudents=0, numStudents;
    //初始化俱乐部访问标志，俱乐部号是从0开始
    bClubVisits.resize(M, false);
    //初始化学生访问标志，因为学生学号是从1开始，所以这里要多分配一个
    bStudentVisits.resize(N+1, false);
    //访问每个俱乐部
    for(i=0; i<M; ++i)
    {
        //如果当前俱乐部已经被访问过了，则忽略
        if(bClubVisits[i])
            continue;
        //设置俱乐部访问标志
        bClubVisits[i] = true;
        //把该俱乐部id加入到种子栈中
        clubSeedIDs.push_back(i);
        //重置当前朋友圈人数为0
        numStudents = 0;
        //当俱乐部种子栈非空
        while(!clubSeedIDs.empty())
        {
            //弹出一个种子俱乐部id
            clubID = clubSeedIDs.back();
            clubSeedIDs.pop_back();
            //遍历该俱乐部下所有学生
            for(j=0; j<clubStudents[clubID].size(); ++j)
            {
                studentID = clubStudents[clubID][j];
                //如果该学生已经被访问过了，则忽略
                if(bStudentVisits[studentID])
                    continue;
                //设置学生访问标记
                bStudentVisits[studentID] = true;
                //朋友圈人数加1
                ++numStudents;
                //找出该学生加入的所有俱乐部
                iter = studentMapClubIDs.find(studentID);
                //访问该学生加入的所有俱乐部
                for(k=0; k<iter->second.size(); ++k)
                {
                    t = iter->second[k];
                    //如果该俱乐部已经被访问过，则忽略
                    if(bClubVisits[t])
                        continue;
                    //设置俱乐部访问标记
                    bClubVisits[t] = true;
                    //把该俱乐部加入到俱乐部种子栈
                    clubSeedIDs.push_back(t);
                }
            }
        }
        //如果当前朋友圈人数超过已知的最大人数，刷新最大人数
        if(numStudents>maxStudents)
            maxStudents = numStudents;
    }
    cout<<maxStudents<<endl;
    return 0;
}
