#include "MultiValueHashTable.h"
#include "LinkedList.h"


typedef struct multiValueHashTable_s
{
	hashTable hash;

	CopyFunction ck;
	FreeFunction fk;
	PrintFunction pk;
	CopyFunction cv;
	FreeFunction fv;
	PrintFunction pv;
	EqualFunction ek;
	EqualFunction ev;
	LinkedList vals_to_free;

}multiValueHashTable_s;

bool compare_lists(LinkedList lista, LinkedList listb){
    return lista == listb;
}

multiValueHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue,
                                              FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey,
                                              EqualFunction equalVal, TransformIntoNumberFunction transformIntoNumber, int hashNumber)
{
	if(copyKey == NULL || freeKey == NULL || printKey == NULL ||equalKey == NULL){return NULL;}
	if (copyValue == NULL || freeValue == NULL || printValue == NULL){return NULL;}
	if(transformIntoNumber == NULL || hashNumber < 0){return NULL;}

	multiValueHashTable newMultiHash = (multiValueHashTable)malloc(sizeof(struct multiValueHashTable_s));
	if (newMultiHash == NULL){return NULL;}

	newMultiHash->hash = createHashTable(copyKey, freeKey, printKey, copyValue, freeValue, printValue, equalKey, transformIntoNumber, hashNumber);
	newMultiHash->ck = copyKey;
	newMultiHash->cv = copyValue;
	newMultiHash->ek = equalKey;
	newMultiHash->ev = equalVal;
	newMultiHash->fk = freeKey;
	newMultiHash->fv = freeValue;
	newMultiHash->pk = printKey;
	newMultiHash->pv = printValue;
	newMultiHash->vals_to_free = createLinkedList(shallow_copy, (FreeFunction) destroyList,
                                                  (EqualFunction) compare_lists, (PrintFunction) displayList);

	return newMultiHash;
}
status destroyMultiValueHashTable(multiValueHashTable mvht)
{

    destroyHashTable(mvht->hash);
    destroyList(mvht->vals_to_free);
	free(mvht);
	return success;
}

status addToMultiValueHashTable(multiValueHashTable mvht, Element key,Element value)
{
	LinkedList valuesOfKey = lookupInHashTable(mvht->hash , key);
	if(valuesOfKey == NULL)
	{
        valuesOfKey = createLinkedList(mvht->cv, mvht->fv, mvht->ev, mvht->pv);
		addToHashTable(mvht->hash, key, valuesOfKey);
		appendNode(mvht->vals_to_free, valuesOfKey);

	}
	status st = appendNode(valuesOfKey, value);

	return st;

}
Element lookupInMultiValueHashTable(multiValueHashTable mvht, Element key)
{
	return lookupInHashTable(mvht->hash , key);
}

status removeFromMultiValueHashTable(multiValueHashTable mvht, Element key ,Element value)
{
	Element valuesOfKey = lookupInHashTable(mvht->hash , key);
	if (valuesOfKey == NULL){return failure;}
	status st = deleteNode(valuesOfKey, value);
	if (0 == getLengthList(valuesOfKey)){
        st = removeFromHashTable(mvht->hash, key);
	}
	return st;
}
void displayMultiValueHashElementsByKey(multiValueHashTable mvht,  Element key)
{
	Element valuesOfKey = lookupInHashTable(mvht->hash , key);
	if(valuesOfKey == NULL){return;}

	mvht->pk(key);
	mvht->pv(valuesOfKey);
}
