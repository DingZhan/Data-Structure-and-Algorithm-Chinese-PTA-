ElementType FindKth( List L, int K )
{
    while(L)
    {
        K--;
        if(K==0)
            return L->Data;
        L = L->Next;
    }
    return ERROR;
}