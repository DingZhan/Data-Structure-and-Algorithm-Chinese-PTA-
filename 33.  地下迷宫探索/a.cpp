#include <iostream>
#include <stack>

using namespace std;

//题目中有提示说是用DFS结果不唯一，所以直接考虑这是DFS能解决的问题
//只是需要对DFS做修改

/*补充测试用例，中间节点3需要被2次访问
6 6 1
1 2
2 3
3 4
4 5
3 6
1 5
*/
#define MAX_N 1002
#define MAX_M 3002

//用邻接矩阵表示图
bool graph[MAX_N][MAX_N];

//用DFS深度优先搜索方法解决亮灯问题
//亮灯问题不是欧拉回路或者欧拉路径问题，因为欧拉回路或路径要求访问所有边，而亮灯不需要访问所有边

//pos是当前访问的顶点，N是总顶点个数，visits是顶点数组访问标记位，path是来的路径也是回去的路径
//bFirstPrint主要用来控制是否先打印空格
void DFS(int pos, int N, bool visits[], stack<int> &path, bool bFirstPrint)
{
    int i;

    //如果已经在路上了
    //则检测当前深度访问的点是否和上一个打印的点之间有路，如果没有路就从路径堆栈中弹出顶点
    //直到有顶点和当前顶点之间有边，见上述测试用例(从顶点5访问到顶点6)
    if(path.size())
    {
        bool bFirstPop=true;
        while(true)
        {
            //如果当前深度访问的点和上一个打印的点之间没有路
            if(!graph[pos][path.top()])
            {
                //如果需要弹出，则一个顶点不要重复打印
                if(!bFirstPop)
                    cout<<" "<<path.top();
                //弹出顶点
                path.pop();
                //后续需要弹出的顶点需要打印
                bFirstPop = false;
            }
            else
                break;
        }
        //如果之前从路径中弹出过顶点，则还要多弹出一个顶点
        //有些拗口，见上述测试用例(从顶点5访问到顶点6)
        if(!bFirstPop)
            cout<<" "<<path.top();
    }

    //如果不是第一次打印，则先打印一个空格再打印当前顶点
    if(!bFirstPrint)
        cout<<" ";
    //打印当前顶点
    cout<<pos;
    //把当前顶点加到路径堆栈中，为了后续从原路返回
    path.push(pos);

    //DFS深度遍历顶点数组，找到没有被访问过的顶点
    for(i=1; i<=N; ++i)
    {
        //如果顶点i没被访问过，并且它和顶点pos之间有边相连
        if(!visits[i] && graph[pos][i])
        {
            //设置访问标记位
            visits[i] = true;
            //DFS递归访问
            DFS(i, N, visits, path, false);
//            visits[i] = false;
        }
    }
}

int main()
{
    int i, N, M, S, a, b, seed;
    //顶点访问标记,初始化为false
    bool visits[MAX_N]={false};
    //记录返回路径
    stack<int> path;

    //读入顶点数、边数、起始点索引
    cin>>N>>M>>S;
    //读入M条边信息，构建邻接矩阵图
    for(i=0; i<M; ++i)
    {
        //读入边的两个顶点
        cin>>a>>b;
        graph[a][b] = graph[b][a] = true;
    }

    //设置起点访问标记
    visits[S] = true;
    //开始深度优先搜索，最后一个参数设置为true，表示第一次打印，主要为了控制空格的输入
    DFS(S, N, visits, path, true);

    //搜索结束
    //避免重复打印最后一个顶点
    if(path.size())
        path.pop();
    //原路返回并打印
    while(!path.empty())
    {
        cout<<" ";
        cout<<path.top();
        path.pop();
    }
    //检测是否还有顶点没被访问过，如果有则说明图非连通，打印一个0
    for(i=1; i<=N; ++i)
    {
        if(!visits[i])
        {
            cout<<" 0";
            break;
        }
    }
    cout<<endl;
    return 0;
}
