#ifndef MULTIVALUEHASHTABLE_H_
#define MULTIVALUEHASHTABLE_H_
#include "Defs.h"
#include "HashTable.h"
typedef struct multiValueHashTable_s* multiValueHashTable;

multiValueHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue,
                                              FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey,
                                              EqualFunction equalVal, TransformIntoNumberFunction transformIntoNumber, int hashNumber);
status destroyMultiValueHashTable(multiValueHashTable mvht);
status addToMultiValueHashTable(multiValueHashTable mvht, Element key,Element value);
Element lookupInMultiValueHashTable(multiValueHashTable mvht, Element key);
status removeFromMultiValueHashTable(multiValueHashTable mvht, Element key ,Element value);
void displayMultiValueHashElementsByKey(multiValueHashTable mvht, Element key);


#endif /* MULTIVALUEHASHTABLE_H_ */
