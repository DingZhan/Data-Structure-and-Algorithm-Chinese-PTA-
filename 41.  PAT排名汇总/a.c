#include <stdio.h>
#include <stdlib.h>

//最后一个测试点始终过不了，目前还不知道怎么回事，一直报答案错误
//找到了，打印准考证号需要%013lld，这是最后一个测试点的关键

//300*100 = 30000，总考生人数
#define MAX_S 30002

#define MAX_N 101

//定义考生的结构体
typedef struct Student_
{
    long long ID;   //准考证号
    int score;    //成绩
    int location; //考点号
}Student;

//所有学生的数组
Student students[MAX_S];

//快速排序的比较函数
int Compare(const void *a, const void *b)
{
    Student *aa = (Student*)a;
    Student *bb = (Student*)b;
    //成绩高的排在前面
    if(aa->score>bb->score)
        return -1;
    else if(aa->score<bb->score) //成绩低的排在后面
        return 1;
    else //成绩相等
    {
        //比较准考证号, 小的号码排在前面
        //不能写成return aa->ID-bb->ID，有溢出风险
        if(aa->ID<bb->ID)
            return -1;
        else if(aa->ID>bb->ID)
            return 1;
        else
            return 0;
    }
}

int main()
{
    int N, K, i, j, t, rank, location;
    int lastScore;
    //考点当前排名
    int locationRanks[MAX_N];
    //考点当前人数
    int locationCount[MAX_N]={0};
    //考点排行榜上上一位考生的人数
    int locationLastScores[MAX_N];

    //读入考点数
    scanf("%d", &N);
    //读入每个考点信息
    for(i=0, t=0; i<N; ++i)
    {
        //读入该考点的考生人数
        scanf("%d", &K);
        //读入该考点每个考生的ID和成绩
        for(j=0; j<K; ++j)
        {
            scanf("%lld%d", &(students[t].ID), &(students[t].score));
            //设置该考试的考点
            students[t].location = i;
            //累加考生人数
            ++t;
        }
    }


    //对学生按成绩和ID进行排序
    qsort(students, t, sizeof(Student), Compare);

    //打印总考生人数
    printf("%d\n", t);
    //总排名变量，初始为1
    rank=1;
    //总排名中上一个考生的成绩，这里初始值设置大于100即可
    lastScore = 101;
    //对每个考点的排名和考生成绩进行初始化
    for(i=0; i<N; ++i)
    {
        //每个考点的排名榜起始排名都为1
        locationRanks[i] = 1;
        //每个考点排名榜上一个学生的成绩，这里初始值设置大于100即可
        locationLastScores[i] = 101;
    }
    //打印所有学生的排名
    for(i=0; i<t; ++i)
    {
        //如果该生的成绩和上一个同学的成绩不一样，则更新排名为i+1
        if(lastScore!=students[i].score)
            rank = i+1;
        //得到该生的考点
        location = students[i].location;
        //将该考点考生人数累加1
        ++locationCount[location];
        //如果该生成绩和该考点排名榜上一个学生成绩不一样，则更新该考点的排名榜
        if(locationLastScores[location]!=students[i].score)
            locationRanks[location] = locationCount[location];
        //打印ID、总排名、考场号以及在该考场的排名
        //013lld是最后一个测试点加的
        printf("%013lld %d %d %d\n", students[i].ID, rank, students[i].location+1, locationRanks[location]);
        //更新上一个学生的成绩
        lastScore = students[i].score;
        //更新该考点上一个学生的成绩
        locationLastScores[location]=students[i].score;
    }
    return 0;
}