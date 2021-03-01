#ifndef KEYVALUEPAIR_H_
#define KEYVALUEPAIR_H_
#include "Defs.h"

typedef struct KeyValuePair_s* KeyValuePair;

KeyValuePair createKeyValuePair(Element k, Element v, CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey);
status destroyKeyValuePair(KeyValuePair k);
status displayValue(KeyValuePair k);
status displayKey(KeyValuePair k);
Element getValue(KeyValuePair k);
Element getKey(KeyValuePair k);
Element copyPair(Element elem);
status PrintPair(Element elem);
status freePair(KeyValuePair elem);
bool isEqualKey(KeyValuePair, Element key);

#endif /* KEYVALUEPAIR_H_ */
