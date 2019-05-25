int GetHeight( BinTree BT )
{
    if(!BT)
      return 0;
    int h1 = GetHeight(BT->Left);
    int h2 = GetHeight(BT->Right);
    if(h1<h2)
        return h2+1;
    else
        return h1+1;
}