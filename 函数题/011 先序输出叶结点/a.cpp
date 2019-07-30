void PreorderPrintLeaves( BinTree BT )
{
    if(BT==NULL)
        return;
    //注意题干：首先必须是前序遍历，其次它只要输出叶结点值
    if(BT->Left==NULL && BT->Right==NULL)
    {
        printf(" %c", BT->Data);
        return;
    }

    PreorderPrintLeaves(BT->Left);
    PreorderPrintLeaves(BT->Right);
}