#include <iostream>
#include <map>
#include <string>
using namespace std;

int main()
{
    std::map<long long, std::string> IDPass;
    std::map<long long, std::string>::iterator it;
    long long id;
    int N, i;
    char type;
    std::string pass;
    cin>>N;
    for(i=0; i<N; ++i)
    {
        cin>>type>>id>>pass;
        if(type=='L')
        {
            it = IDPass.find(id);
            if(it==IDPass.end())
            {
                cout<<"ERROR: Not Exist\n";
            }
            else
            {
                if(it->second!=pass)
                    cout<<"ERROR: Wrong PW\n";
                else
                    cout<<"Login: OK\n";
            }
        }
        else
        {
            it = IDPass.find(id);
            if(it==IDPass.end())
            {
                IDPass[id] = pass;
                cout<<"New: OK\n";
            }
            else
                cout<<"ERROR: Exist\n";
        }
    }

    return 0;
}
