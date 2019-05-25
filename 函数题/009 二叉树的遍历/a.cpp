void InorderTraversal( BinTree BT )
{
    if(!BT)
        return;
    InorderTraversal(BT->Left);
    printf(" %c", BT->Data);
    InorderTraversal(BT->Right);
}
void PreorderTraversal( BinTree BT )
{
    if(!BT)
        return;
    printf(" %c", BT->Data);
    PreorderTraversal(BT->Left);
    PreorderTraversal(BT->Right);
}
void PostorderTraversal( BinTree BT )
{
    if(!BT)
        return;
    PostorderTraversal(BT->Left);
    PostorderTraversal(BT->Right);
    printf(" %c", BT->Data);
}
void LevelorderTraversal( BinTree BT )
{
    //不使用std::queue，学会用数组模拟队列
    Position queue[1000];
    Position seed;
    //数组模拟队列
    int front=0, back=0;
    if(!BT)
        return;
    queue[back++] = BT;
    while(front<back)
    {
        //从队列前部弹出一个结点
        seed = queue[front++];
        printf(" %c", seed->Data);
        //把该结点的左右儿子加入队列
        if(seed->Left)
            queue[back++] = seed->Left;
        if(seed->Right)
            queue[back++] = seed->Right;
    }
}