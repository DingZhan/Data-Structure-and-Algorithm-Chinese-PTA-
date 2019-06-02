#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main()
{
    int N, M, i, j, k, t, n, studentID;
    //ÿ�����ֲ��������ѧ����Ϣ
    std::vector<std::vector<int> > clubStudents;
    //<ѧ��, ����ľ��ֲ�s> ��ֵ��
    std::map<int, std::vector<int> > studentMapClubIDs;
    //map�ĵ�����
    std::map<int, std::vector<int> >::iterator iter;

    //����ѧ�����;��ֲ���Ŀ
    cin>>N>>M;
    //resize����M�����ֲ�
    clubStudents.resize(M);
    for(i=0; i<M; ++i)
    {
        //�����i�����ֲ���ѧ����Ŀ
        cin>>n;
        //������ֲ�ѧ��id
        for(j=0; j<n; ++j)
        {
            cin>>studentID;
            //�Ѹ�ѧ�����뵽��ǰ���ֲ�
            clubStudents[i].push_back(studentID);
            //�Ѹþ��ֲ�id���뵽��ѧ���μӵľ��ֲ�
            studentMapClubIDs[studentID].push_back(i);
        }
    }

    //�ϲ����ֲ�
    std::vector<int> clubSeedIDs;
    std::vector<bool> bClubVisits, bStudentVisits;
    int clubID;
    int maxStudents=0, numStudents;
    //��ʼ�����ֲ����ʱ�־�����ֲ����Ǵ�0��ʼ
    bClubVisits.resize(M, false);
    //��ʼ��ѧ�����ʱ�־����Ϊѧ��ѧ���Ǵ�1��ʼ����������Ҫ�����һ��
    bStudentVisits.resize(N+1, false);
    //����ÿ�����ֲ�
    for(i=0; i<M; ++i)
    {
        //�����ǰ���ֲ��Ѿ������ʹ��ˣ������
        if(bClubVisits[i])
            continue;
        //���þ��ֲ����ʱ�־
        bClubVisits[i] = true;
        //�Ѹþ��ֲ�id���뵽����ջ��
        clubSeedIDs.push_back(i);
        //���õ�ǰ����Ȧ����Ϊ0
        numStudents = 0;
        //�����ֲ�����ջ�ǿ�
        while(!clubSeedIDs.empty())
        {
            //����һ�����Ӿ��ֲ�id
            clubID = clubSeedIDs.back();
            clubSeedIDs.pop_back();
            //�����þ��ֲ�������ѧ��
            for(j=0; j<clubStudents[clubID].size(); ++j)
            {
                studentID = clubStudents[clubID][j];
                //�����ѧ���Ѿ������ʹ��ˣ������
                if(bStudentVisits[studentID])
                    continue;
                //����ѧ�����ʱ��
                bStudentVisits[studentID] = true;
                //����Ȧ������1
                ++numStudents;
                //�ҳ���ѧ����������о��ֲ�
                iter = studentMapClubIDs.find(studentID);
                //���ʸ�ѧ����������о��ֲ�
                for(k=0; k<iter->second.size(); ++k)
                {
                    t = iter->second[k];
                    //����þ��ֲ��Ѿ������ʹ��������
                    if(bClubVisits[t])
                        continue;
                    //���þ��ֲ����ʱ��
                    bClubVisits[t] = true;
                    //�Ѹþ��ֲ����뵽���ֲ�����ջ
                    clubSeedIDs.push_back(t);
                }
            }
        }
        //�����ǰ����Ȧ����������֪�����������ˢ���������
        if(numStudents>maxStudents)
            maxStudents = numStudents;
    }
    cout<<maxStudents<<endl;
    return 0;
}
