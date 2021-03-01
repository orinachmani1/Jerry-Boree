#ifndef DEFS_H_
#define DEFS_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum{success, empty_argument, fail_value, fail_mem, failure}status;
typedef enum{ false , true }bool ;

typedef void * Element;

typedef Element(*CopyFunction) (Element);
typedef status(*FreeFunction) (Element);
typedef status(*PrintFunction) (Element);
typedef int(*TransformIntoNumberFunction) (Element);
typedef bool(*EqualFunction) (Element, Element);

char* copy_key(char* key);
status free_key(char* key);
status print_key(char* key);
status free_shallow(Element key);
bool equal_keys(char* keyA, char* keyB);
Element shallow_copy(Element input);

#endif /* DEFS_H_ */
