#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//解法：快速排序

#define MAX_N 100001

//定义考生的结构体
typedef struct Student_
{
    int ID;         //学号
    char name[9];    //姓名
    short score;    //成绩
}Student;

//所有学生的数组
Student students[MAX_N];

//快速排序的比较函数:学号升序
int CompareByID(const void *a, const void *b)
{
    Student *aa = (Student*)a;
    Student *bb = (Student*)b;
    return aa->ID - bb->ID;
}

//快速排序的比较函数:姓名升序，同名时按学号升序
int CompareByName(const void *a, const void *b)
{
    Student *aa = (Student*)a;
    Student *bb = (Student*)b;
    int ret = strcmp(aa->name, bb->name);
    if(ret!=0)
        return ret;
    return aa->ID - bb->ID;
}

//快速排序的比较函数:成绩升序，同成绩时按学号升序
int CompareByScore(const void *a, const void *b)
{
    Student *aa = (Student*)a;
    Student *bb = (Student*)b;
    int ret = aa->score-bb->score;
    if(ret!=0)
        return ret;
    return aa->ID - bb->ID;
}

int main()
{
    int N, i, C;
    scanf("%d%d", &N, &C);
    for(i=0; i<N; ++i)
    {
        scanf("%d%s%d", &students[i].ID, &students[i].name, &students[i].score);
    }
    if(C==1)
        qsort(students, N, sizeof(Student), CompareByID);
    else if(C==2)
        qsort(students, N, sizeof(Student), CompareByName);
    else
        qsort(students, N, sizeof(Student), CompareByScore);
    for(i=0; i<N; ++i)
    {
        printf("%06d %s %d\n", students[i].ID, students[i].name, students[i].score);
    }
    return 0;
}
