
Stack CreateStack( int MaxSize )
{
    Stack s = (Stack)malloc(sizeof(struct SNode));
    s->MaxSize = MaxSize;
    s->Data = (ElementType*)malloc(sizeof(ElementType)*(MaxSize));
    s->Top1 = -1;
    s->Top2 = MaxSize;
    return s;
}

bool Push( Stack S, ElementType X, int Tag )
{
    if(S->Top1>=S->Top2-1)
    {
        printf("Stack Full\n");
        return false;
    }
    if(Tag==1)
        S->Data[++S->Top1] = X;
    else
        S->Data[--(S->Top2)] = X;
    return true;
}

ElementType Pop( Stack S, int Tag )
{
    ElementType v;
    if(Tag==1)
    {
        if(S->Top1==-1)
        {
            printf("Stack %d Empty\n", Tag);
            return ERROR ;
        }
        return S->Data[S->Top1--];
    }
    else
    {
        if(S->Top2==S->MaxSize)
        {
            printf("Stack %d Empty\n", Tag);
            return ERROR;
        }
        return S->Data[S->Top2++];
    }
}
