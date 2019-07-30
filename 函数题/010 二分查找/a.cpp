//二分查找，需要定义游标:begin, end, middle
Position BinarySearch( List L, ElementType X )
{
    //由于存储数据是从1开始，所以begin设置为1
    int begin = 1;
    //end是最后一个位置的下标
    int end = L->Last;
    //设置middle初始值
    int middle = (begin+end)/2;
    //当begin>end时候搜索才结束
    while(begin<=end)
    {
        //找到
        if(L->Data[middle]==X)
            return middle;
        //如果当前中间值比X要小，所以begin移动到middle+1，+1不能少
        if(L->Data[middle]<X)
        {
            begin = middle+1;
        }
        else //如果当前中间值比X要大，所以end移动到middle-1，-1不能少
        {
            end = middle - 1;
        }
        //更新middle
        middle = (begin+end)/2;
    }
    //没找到
    return NotFound;
}