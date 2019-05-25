#include <iostream>
using namespace std;

#define MAX_N 501

//定义一个无效距离，即一个足够大的距离
#define MAX_LEN 10000000
struct Item
{
    unsigned int minDis;
    unsigned int minPrice;
    Item()
    {
        minDis = MAX_LEN;
    }
};

//任意两个结点之间的距离、费用矩阵，即无向图
//距离矩阵中每个距离都初始设置为无效的距离
Item mat[MAX_N][MAX_N];


int main()
{
    int i, j, k, N, M, S, D, a, b, len, price;
    //输入矩阵
    cin>>N>>M>>S>>D;
    for(i=0; i<M; ++i)
    {
        cin>>a>>b>>len>>price;
        mat[a][b].minDis = len;
        mat[a][b].minPrice = price;
        //对称矩阵
        mat[b][a] = mat[a][b];
    }

    //Floyd算法，中间结点k一定要放在最外层循环
    for(k=0; k<N; ++k)
    {
        //矩阵行号
        for(i=0; i<N; ++i)
        {
            if(i==k)
                continue;
            //矩阵列号
            for(j=0; j<N; ++j)
            {
                if(j==i||j==k)
                    continue;
                //如果mat[i][j]>mat[i][k]+mat[k][j],则更新mat[i][j]距离
                if(mat[i][j].minDis>mat[i][k].minDis+mat[k][j].minDis)
                {
                    mat[i][j].minDis = mat[i][k].minDis + mat[k][j].minDis;
                    mat[i][j].minPrice = mat[i][k].minPrice + mat[k][j].minPrice;
                    //同时更新对称元素，if是否不需要加？
               //     if(mat[j][i].minDis > mat[i][j].minDis)
               //         mat[j][i] = mat[i][j];
                }
                //距离相等的情况下，收费越少越好
                else if(mat[i][j].minDis==mat[i][k].minDis+mat[k][j].minDis &&
                        mat[i][j].minPrice>mat[i][k].minPrice+mat[k][j].minPrice
                        )
                {
                    mat[i][j].minPrice=mat[i][k].minPrice+mat[k][j].minPrice;
                 //   if(mat[j][i].minDis > mat[i][j].minDis||
                 //      mat[j][i].minDis==mat[i][j].minDis)
                //        mat[j][i] = mat[i][j];
                }
            }
        }
    }

    cout<<mat[S][D].minDis<<" "<<mat[S][D].minPrice<<endl;
    return 0;
}
