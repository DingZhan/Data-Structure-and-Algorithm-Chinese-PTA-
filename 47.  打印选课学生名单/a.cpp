#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

//主体原则：先对学生按名字字典序进行一次统一的排序，然后把学生装到其所选的课程桶里面

//学生结构体
struct Student
{
    //名字
    char name[5];
    //学生所选的所有课程，K小于2500，所以这里可以用short表示课程号
    std::vector<short> ClassIDs;
};

//学生结构体按名字字典序进行排序
bool Compare(const Student& a, const Student &b)
{
    return strcmp(a.name, b.name)<0;
}

int main()
{
    int N, K, i, n, j, k;
    //所有学生的结构体数组
    std::vector<Student> students;
    //课程桶，桶里面装的是学生按名字排序后的学号序号
    std::vector<std::vector<unsigned short> > classBuckets;
    //读入学生总数和课程总数
    cin>>N>>K;
    //动态分配数组
    students.resize(N);
    //课程编号从1开始至K，所以多分配一个桶
    classBuckets.resize(K+1);
    //读入所有学生信息
    for(i=0;i<N; ++i)
    {
        //读入名字和所选课程总数
        cin>>students[i].name>>n;
        //对该学生所选课程动态分配数组
        students[i].ClassIDs.resize(n);
        //读入该生的所有选课课号
        for(j=0; j<n; ++j)
            cin>>students[i].ClassIDs[j];
    }

    //对所有学生按名字进行一次统一的排序，这个避免了后续多次排序
    sort(students.begin(), students.end(), Compare);

    //将排序后的学生编号装到K个桶里面
    for(i=0; i<N; ++i)
    {
        for(j=0; j<students[i].ClassIDs.size(); ++j)
        {
            k = students[i].ClassIDs[j];
            //将学生编号i加入到选课课程的桶里面
            classBuckets[k].push_back(i);
        }
    }

    //遍历所有桶从1至K
    for(i=1; i<classBuckets.size(); ++i)
    {
//        if(classBuckets[i].empty())
//            continue;
        //打印桶号和桶里学生编号总个数
        cout<<i<<" "<<classBuckets[i].size()<<"\n";
        for(j=0; j<classBuckets[i].size(); ++j)
        {
            k = classBuckets[i][j];
            //打印学生名字，因为之前先按名字排序过，所以这里名字的顺序一定是字典序的
            cout<<students[k].name<<"\n";
        }
    }

    return 0;
}