//创建空的链表，链表头不存储数据
List MakeEmpty()
{
    List head = (List)malloc(sizeof(struct LNode));
    head->Next = NULL;
    return head;
}

//从链表中找出X的位置
Position Find( List L, ElementType X )
{
    //链表头不存储数据，所以从表头下一个位置开始搜索
    PtrToLNode node = L->Next;
    while(node)
    {
        if(node->Data==X)
            return node;
        node = node->Next;
    }
    //没找到
    return ERROR;
}

//在链表L中P位置前插入新结点
bool Insert( List L, ElementType X, Position P )
{
    //node是待插入新结点的前一个结点，即当前P结点的前一个结点
    PtrToLNode node = L;
    while(node->Next)
    {
        //找到了待插入结点的位置：node的后面，P的前面
        if(node->Next==P)
            break;
        node = node->Next;
    }
    //没找到P结点
    if(node->Next!=P)
    {
        printf("Wrong Position for Insertion\n");
        return false;
    }
    PtrToLNode newNode = (PtrToLNode)malloc(sizeof(struct LNode));
    //把P结点放到新结点的后面
    newNode->Next = P;
    newNode->Data = X;
    //把新结点放到node结点的后面
    node->Next = newNode;
    return true;
}

//删除P结点
bool Delete( List L, Position P )
{
    Position node = L;
    while(node->Next)
    {
        //找到P的前一个结点
        if(node->Next==P)
        {
            node->Next = P->Next;
            //一定要释放P结点的动态内存
            free(P);
            return true;
        }
        node = node->Next;
    }
    //没找到P结点
    printf("Wrong Position for Deletion\n");
    return false;
}