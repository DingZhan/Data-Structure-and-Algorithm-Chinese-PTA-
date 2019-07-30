//从链表中查找元素X
Position Find( List L, ElementType X )
{
    //遍历链表
    while(L)
    {
        if(L->Data==X)
            return L;
        L = L->Next;
    }
    return ERROR;
}

//在链表L中，P位置前插入新结点
List Insert( List L, ElementType X, Position P )
{
    //pre是链表中结点P的前一个结点
    List head = L, pre=ERROR, node;
    //如果当前链表为空
    if(head==NULL)
    {
        //链表为空，而P非空，则有错误
        if(P)
        {
//            printf("Wrong Position for Insertion\n");
            return ERROR;
        }
        //创建链表头结点
        head = (List)malloc(sizeof(struct LNode));
        head->Next = P;
        head->Data = X;
        //返回新链表头
        return head;
    }
    //当前链表非空，遍历链表
    while(L)
    {
        //找到P结点
        if(L == P)
        {
            //创建新结点
            node = (List)malloc(sizeof(struct LNode));
            //把新结点的下一个结点指向P
            node->Next = P;
            node->Data = X;
            //如果L结点的前一个结点为空，则说明当前L结点就是链表头结点，所以更新头结点
            if(pre==ERROR)
                head = node;
            else //将前一个结点的下一个结点设置为新结点
                pre->Next = node;
            return head;
        }
        pre = L;
        L = L->Next;
    }
    //遍历整个链表没有找到P，如果P为NULL，则在链表尾部添加新结点
    if(P==NULL)
    {
        node = (List)malloc(sizeof(struct LNode));
        node->Next = P;
        node->Data = X;
        pre->Next = node;
        return head;
    }
    else //遍历整个链表没有找到P，并且P非空，所以有错
        printf("Wrong Position for Insertion\n");
    return ERROR;
}

//从链表中删除P结点，返回新链表头
List Delete( List L, Position P )
{
    //设置pre为待删除结点P的前一个结点
    List head = L, pre = ERROR;
    while(L)
    {
        //找到了P
        if(L==P)
        {
            //如果待删除结点的前一个结点非空，则将pre的next指向P的next
            if(pre!=ERROR)
                pre->Next = P->Next;
            else //待删除结点的前一个结点为空，则说明P就是链表头结点，因此更新头
                head = P->Next;
            return head;
        }
        //设置pre
        pre = L;
        L = L->Next;
    }
    //最后也没找到P
    printf("Wrong Position for Deletion\n");
    return ERROR;
}
