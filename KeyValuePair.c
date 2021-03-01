#include "KeyValuePair.h"


typedef struct KeyValuePair_s
{
	Element key;
	Element value;

	CopyFunction copyKey;
	FreeFunction freeKey;
	PrintFunction printKey;
	CopyFunction copyValue;
	FreeFunction freeValue;
	PrintFunction printValue;
	EqualFunction equalKey;
} KeyValuePair_s;


KeyValuePair createKeyValuePair(Element k, Element v, CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey)
{
	if(copyKey == NULL || freeKey == NULL || printKey == NULL ||equalKey == NULL){return NULL;}
	if (copyValue == NULL || freeValue == NULL || printValue == NULL){return NULL;}
	if (k==NULL || v== NULL){return NULL;}

	KeyValuePair newPair = (KeyValuePair)malloc(sizeof(struct KeyValuePair_s));
	if (newPair == NULL){return NULL;}

	newPair->copyKey = copyKey;
	newPair->freeKey = freeKey;
	newPair->printKey = printKey;
	newPair->equalKey = equalKey;

	newPair->copyValue = copyValue;
	newPair->freeValue = freeValue;
	newPair->printValue = printValue;

	newPair->key = newPair->copyKey(k);
	newPair->value = newPair->copyValue(v);

	return newPair;

}
status destroyKeyValuePair(KeyValuePair k)
{
	if (k == NULL){return empty_argument;}
	k->freeKey(k->key);
	k->freeValue(k->value);
	free(k);
	return  success;

}
status displayValue(KeyValuePair k)
{
	if (k == NULL){return empty_argument;}
	k->printValue(k->value);
	return success;
}
status displayKey(KeyValuePair k)
{
	if (k == NULL){return empty_argument;}
	k->printKey(k->key);
	return success;
}
Element getValue(KeyValuePair k)
{
	if (k == NULL){return NULL;}
	return k->value;
}
Element getKey(KeyValuePair k)
{
	if (k == NULL){return NULL;}
	return k->key;
}

bool isEqualKey(KeyValuePair k , Element key)
{
	if (k == NULL || key == NULL){return false;}
	if (true == k->equalKey(k->key, key)){return true;}
	return false;


}
Element copyPair(Element elem)
{
	if (elem == NULL){return NULL;}
	KeyValuePair origPair = (KeyValuePair)elem;
	KeyValuePair newPair = (KeyValuePair)malloc(sizeof(struct KeyValuePair_s));
	if (newPair == NULL){return NULL;}

	newPair->key = origPair->copyKey(origPair->key);
	newPair->value = origPair->copyValue(origPair->value);
	newPair->copyValue = origPair->copyValue;
	newPair->copyKey = origPair->copyKey;
	newPair->freeKey = origPair->freeKey;
	newPair->freeValue = origPair->freeValue;
	newPair->printKey = origPair->printKey;
	newPair->printValue = origPair->printValue;
	newPair->equalKey = origPair->equalKey;

	return newPair;
}
status freePair(KeyValuePair origPair)
{
	if (origPair == NULL){return failure;}

	origPair->freeKey(origPair->key);
	origPair->freeValue(origPair->value);
	free(origPair);
    return success;

}

status PrintPair(Element elem)
{
	KeyValuePair pair = (KeyValuePair)elem;
	pair->printKey(pair);
	pair->printValue(pair);
    return success;
}



