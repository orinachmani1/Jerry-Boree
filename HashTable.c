#include "HashTable.h"
#include "KeyValuePair.h"
#include "LinkedList.h"

struct hashTable_s
{
	LinkedList* ls;

	TransformIntoNumberFunction sumAscii;
	CopyFunction ck;
	FreeFunction fk;
	PrintFunction pk;
	CopyFunction cv;
	FreeFunction fv;
	PrintFunction pv;
	EqualFunction ek;
	int hashNum;

} ;


hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
                          CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue,
                          EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber)
{
	if(copyKey == NULL || freeKey == NULL || printKey == NULL ||equalKey == NULL){return NULL;}
	if (copyValue == NULL || freeValue == NULL || printValue == NULL){return NULL;}
	if(transformIntoNumber == NULL || hashNumber < 0){return NULL;}

	hashTable newHash = (hashTable)malloc(sizeof(struct hashTable_s));
	if (newHash == NULL){return NULL;}

	newHash->ls=malloc(sizeof(LinkedList)*hashNumber);

	for (int i = 0; i < hashNumber ; i++)
	{
		newHash->ls[i] = createLinkedList(copyPair, (FreeFunction) destroyKeyValuePair, (EqualFunction) isEqualKey, PrintPair);
	}

	newHash->ck = copyKey;
	newHash->cv = copyValue;
	newHash->ek = equalKey;
	newHash->fk = freeKey;
	newHash->fv = freeValue;
	newHash->pk = printKey;
	newHash->pv = printValue;
	newHash->sumAscii = transformIntoNumber;
	newHash->hashNum = hashNumber;

	return newHash;
}

status destroyHashTable(hashTable h)
{
	for (int i = 0; i < h->hashNum; i++)
	{
		destroyList(h->ls[i]);
	}
	free(h->ls);
	free(h);
	return success;
}

status addToHashTable(hashTable h, Element key,Element value)
{
    if (NULL != lookupInHashTable(h, key)) {return failure;}
    KeyValuePair newKvp = createKeyValuePair(key, value, h->ck, h->fk ,h->pk, h->cv, h->fv, h->pv, h->ek);
	int asciiVal = h->sumAscii(key);
	int place = asciiVal % h->hashNum;
	appendNode(h->ls[place], newKvp); //chane void to status
	destroyKeyValuePair(newKvp);
	return success;

}

Element lookupInHashTable(hashTable h, Element key)
{
	int asciiVal = h->sumAscii(key);
	int place = asciiVal % h->hashNum;
	return getValue(searchByKeyInList(h->ls[place], key));
}

status removeFromHashTable(hashTable h, Element key)
{
	int asciiVal = h->sumAscii(key);
	int place = asciiVal % h->hashNum;
	deleteNode(h->ls[place], key);
	return success;
}
status displayHashElements(hashTable h)
{
	for(int i = 0; i < h->hashNum; i++)
	{
		displayList(h->ls[i]);
	}
	return success;
}
