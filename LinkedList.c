#include "LinkedList.h"

typedef struct t_Node
{
	Element val;
	Node next;
}t_Node;

typedef struct t_LinkedList
{
	Node head;
	Node tail;
	int lstSize;
	CopyFunction copyFunc;
	FreeFunction freeFunc;
	EqualFunction equalFunc;
	PrintFunction printFunc;
}t_LinkedList;

LinkedList createLinkedList(CopyFunction cf, FreeFunction ff, EqualFunction eq, PrintFunction pf)
{
	if(cf == NULL || ff == NULL || eq == NULL || pf == NULL){return NULL;}

	LinkedList newLinked = (LinkedList)malloc(sizeof(struct t_LinkedList));
	if(newLinked==NULL){return NULL;}

	newLinked->head = NULL;
	newLinked->tail = NULL;
	newLinked->lstSize = 0;

	newLinked->copyFunc = cf;
	newLinked->freeFunc = ff;
	newLinked->equalFunc = eq;
	newLinked->printFunc = pf;

	return newLinked;

}
void destroyNode(LinkedList lst, Node n)
{
	if(lst == NULL || n == NULL ) {return;}
	lst->freeFunc(n->val);
	free(n);
}

void destroyList(LinkedList lst)
{
	if(lst == NULL) {return;}

	while (lst->head != NULL)
	{
		Node tmp = lst->head->next;
		destroyNode(lst, lst->head);
		lst->head = tmp;
		lst->lstSize--;
	}

	if (lst->lstSize ==0)
	{
		free(lst);
	}
}

status appendNode(LinkedList lst,Element elem)
{
	if(lst == NULL || elem == NULL ){return failure;}

	Node newNode = (Node)malloc(sizeof(struct t_Node));
	if(newNode == NULL){return failure;}

	newNode->val= lst->copyFunc(elem);
	newNode->next=NULL;

	if (lst->lstSize == 0)
	{
		lst->head = newNode;
		lst->tail = newNode;
	}

	else if (lst->lstSize == 1)
	{
		lst->tail = newNode;
		lst->head->next = newNode;
	}

	else
	{
		lst->tail->next = newNode;
		lst->tail = newNode;
	}
	lst->lstSize++;
    return success;
}

status deleteNode(LinkedList lst,Element elem)
{
	if(lst == NULL || elem == NULL){return failure;}

	Node tmp=lst->head;
	if (true == lst->equalFunc(tmp->val, elem)) // if the wanted elem is the first
	{
		lst->head = lst->head->next; //update the head
		destroyNode(lst, tmp);
		lst->lstSize--;
		return success;
	}

	while (tmp->next != NULL)
	{
		if (true == lst->equalFunc(tmp->next->val, elem))
		{
			Node tmp2=tmp->next; // tmp2 ment to delete the pointer from the node we
								 // want to del to the next node
			tmp->next=tmp->next->next;
			tmp2->next=NULL;
			destroyNode(lst, tmp2);
			tmp2=NULL;
			
			if(tmp->next==NULL)
			{
				lst->tail = tmp;
			}

			lst->lstSize--;
			return success;
		}

		else
		{
			tmp=tmp->next;
		}
	}
	return failure;
}

void displayList(LinkedList lst)
{
	if(lst == NULL){return;}
	Node tmp = lst->head;
	while (tmp != NULL)
	{
		lst->printFunc(tmp->val);
		if (tmp->next == NULL){break;}
		else
		{
			tmp = tmp->next;
		}
	}
}


Element getDataByIndex(LinkedList lst, int index)
{
	if(lst == NULL){return NULL;}
	if(index >= lst->lstSize){return NULL;}

	Node tmp = lst->head;

	for (int i = 0; i < index; ++i){
	    tmp = tmp->next;
	}

	return tmp->val;
}

int getLengthList(LinkedList lst)
{
	return lst->lstSize;
}
Element searchByKeyInList(LinkedList lst,Element elem)
{
	if(lst == NULL){return NULL;}

	Node tmp = lst->head;

	while (tmp != NULL)
	{
		if (true == lst->equalFunc(tmp->val,elem))
		{
			return tmp->val;
		}
		else
		{
			tmp = tmp->next;
		}
	}
	return NULL;
}

Node getHead(LinkedList lst){
    if (NULL == lst) { return NULL;}
    return lst->head;
}

Node getNext(Node node){
    if (NULL == node) {return NULL;}
    return node->next;
}
Element getVal(Node node){
    if (NULL == node) { return NULL;}
    return node->val;
}


