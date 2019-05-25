List Reverse( List L )
{
	PtrToNode head, next,pre;
	head = L;
	pre = NULL;
	while(head)
	{
		next = head->Next;
		head->Next = pre;
		pre = head;
		head = next;
	}
	return pre;
}