
List MakeEmpty()
{
	List L = (List)malloc(sizeof(struct LNode));
	L->Last=-1;
	return L;
}

Position Find( List L, ElementType X )
{
	int i;
	for(i=0; i<=L->Last; ++i)
	{
		if(L->Data[i]==X)
			return i;
	}
	return ERROR;
}

bool Insert( List L, ElementType X, Position P )
{
	if(L->Last==MAXSIZE-1)
	{
		printf("FULL");
		return false;
	}
	if(P>L->Last+1||P<0)
	{
		printf("ILLEGAL POSITION");
		return false;
	}
	int i;
	for(i=L->Last; i>=P; --i)
	{
		L->Data[i+1]=L->Data[i];
	}
	L->Data[P] = X;
	++L->Last;
	return true;
}

bool Delete( List L, Position P )
{
	if(L->Last<0||P>L->Last||P<0)
	{
		printf("POSITION %d EMPTY", P);
		return false;
	}
	
	int i;
	for(i=P; i<L->Last; ++i)
	{
		L->Data[i]=L->Data[i+1];
	}
	--L->Last;
	return true;
}