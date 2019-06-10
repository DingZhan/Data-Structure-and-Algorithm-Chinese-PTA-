#include <iostream>
#include <map>
#include <string>

using namespace std;

//超时方法，用map
int main()
{
    std::ios::sync_with_stdio(false);
    int N, K, M, i, mile;
    string id;
    map<string, unsigned int> IDMapMiles;
    map<string, unsigned int>::iterator it;
    cin>>N>>K;
    for(i=0; i<N; ++i)
    {
        cin>>id>>mile;
        it = IDMapMiles.find(id);
        if(mile<K)
            mile = K;
        if(it==IDMapMiles.end())
            IDMapMiles.insert(std::make_pair(id, mile));
        else
            it->second+=mile;
    }
    cin>>M;
    for(i=0; i<M; ++i)
    {
        cin>>id;
        it = IDMapMiles.find(id);
        if(it==IDMapMiles.end())
            cout<<"No Info\n";
        else
        {
            cout<<it->second<<"\n";
        }
    }
}
