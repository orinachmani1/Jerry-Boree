#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Defs.h"
#include "KeyValuePair.h"

typedef struct t_LinkedList* LinkedList;
typedef struct t_Node* Node;

LinkedList createLinkedList(CopyFunction cf, FreeFunction ff, EqualFunction eq, PrintFunction pf);
void destroyList(LinkedList lst);
status appendNode(LinkedList lst,Element elem);
status deleteNode(LinkedList lst,Element elem);
void displayList(LinkedList lst);
Element getDataByIndex(LinkedList lst, int index);
int getLengthList(LinkedList lst);
Element searchByKeyInList(LinkedList lst,Element elem);
Node getHead(LinkedList lst);
Node getNext(Node node);
Element getVal(Node node);





#endif /* LINKEDLIST_H_ */
