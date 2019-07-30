
//将X插入到二叉搜索树中 
BinTree Insert( BinTree BST, ElementType X )
{
	//如果树为空，所以创建根节点 
    if(BST==NULL)
    {
        Position node = (Position)malloc(sizeof(struct TNode));
        node->Left = node->Right = NULL;
        node->Data = X;
        //返回新创建的根节点  
        return node;
    }
	//遍历二叉树，
	//1)如果X小于当前节点的值，则往当前节点的左子树走，如果当前节点左子树为空，则创建新左子树结点 
	//2)如果X大于当前节点的值，则往当前节点的右子树走，如果当前节点右子树为空，则创建新右子树结点 
    BinTree pre = BST;
    while(1)
    {
    	//如果X大于当前节点的值,则往当前节点的右子树走
        if(X>pre->Data)
        {
        	//如果当前节点右子树为空，则创建新右子树结点
            if(pre->Right==NULL)
            {
                Position node = (Position)malloc(sizeof(struct TNode));
                node->Left = node->Right = NULL;
                node->Data = X;
                pre->Right = node;
                break;
            }
            else //否则，继续往右子树遍历 
                pre = pre->Right;
        }
        else//X小于当前节点的值,则往当前节点的左子树走
        {
        	//如果当前节点左子树为空，则创建新左子树结点  
            if(pre->Left==NULL)
            {
                Position node = (Position)malloc(sizeof(struct TNode));
                node->Left = node->Right = NULL;
                node->Data = X;
                pre->Left = node;
                break;
            }
            else //否则，继续往左子树遍历 
                pre = pre->Left;
        }
    }
    //返回根结点 
    return BST;
}

//将X从二叉搜索树中删除
BinTree Delete( BinTree BST, ElementType X )
{
	//定义一个当前需要被删除结点的父结点pre 
    Position node = BST, pre=NULL;
    //遍历搜索二叉树 ，查找X
    while(node)
    {
    	//找到需要被删除的结点node 
        if(node->Data ==X)
        {
            //如果node是根结点（父结点pre为NULL）
            if(pre==NULL)
            {
            	//如果根节点有左子树 
                if(node->Left)
                {
                    //找到根结点左儿子的最右结点，也就是左子树的最大值的结点 
					//因为马上要将原树的根节点的右子树加到该结点的右边 
                    pre = BST->Left;
                    while(pre->Right)
                        pre = pre->Right;
                    //原树的根节点的右子树加到该结点的右边 
                    pre->Right = BST->Right;
                	//把根结点的左儿子作为新的树根 
                    BST = node->Left;
                }
                else //原根节点没有左子树，则把右结点设置为新树树根(不care是否为NULL了 )
                {
                    BST = node->Right;
                }                    
            }
            else //如果待删除的结点不是根结点（父结点pre不为NULL）
            {
                //如果待删除的结点有左子树 
                if(node->Left)
                {
                	//用该左子树结点替换待删除的结点
                    if(pre->Left==node)
                        pre->Left = node->Left;
                    else
                        pre->Right = node->Left;
                    
                    //找到删除结点的左儿子的最右结点，也就是左子树的最大值的结点 
					//因为马上要将待删除结点的右子树加到该结点的右边 
                    pre = node->Left;
                    while(pre->Right)
                        pre = pre->Right;
                    pre->Right = node->Right;
                }
                else //待删除的结点没有左子树 
                {
                	//用右子树结点替换待删除的结点（不care是否为NULL） 
                    if(pre->Left==node)
                        pre->Left = node->Right;
                    else
                        pre->Right = node->Right;
                }
            }
            //别忘记释放待删除结点的动态内存 
            free(node);
            //返回新树根结点（也有可能是旧树根) 
            return BST;
        }
        //设置父节点 
        pre = node;
        //X大于当前结点值，因此往右子树搜索 
        if(X>node->Data)
            node = node->Right;
        else //X小于当前结点值，因此往左子树搜索 
            node = node->Left;
    }
    printf("Not Found\n");
    //返回旧树根，不要写成NULL 
    return BST;
}

//从二叉搜索树搜索X结点 
Position Find( BinTree BST, ElementType X )
{
	//从树根开始 
    Position node = BST;
    //开始遍历 
    while(node)
    {
    	//找到该结点 
        if(node->Data ==X)
            return node;
        //如果X大于当前结点的值，则往当前结点的右子树搜索 
        else if(X>node->Data)
            node = node->Right;
        //如果X小于当前结点的值，则往当前结点的左子树搜索 
        else
            node = node->Left;
    }
    return NULL;
}

//找到二叉搜索树的最小值，即：最左结点 
Position FindMin( BinTree BST )
{
	//必须有保护，否则对于空树可能会有段错误 
	if(!BST)
		return NULL;
	//最左结点 
    while(BST->Left)
        BST = BST->Left;
    return BST;
}

//找到二叉搜索树的最大值，即：最右结点 
Position FindMax( BinTree BST )
{
	//必须有保护，否则对于空树可能会有段错误 
	if(!BST)
		return NULL;
	//最右结点 
    while(BST->Right)
        BST = BST->Right;
    return BST;
}
