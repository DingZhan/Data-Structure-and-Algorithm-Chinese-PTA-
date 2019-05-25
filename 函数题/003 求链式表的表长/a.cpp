int Length( List L )
{
    int len = 0;
    while(L)
    {
        ++len;
        L  = L->Next;
    }
    return len;
}