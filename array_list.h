#ifndef SAPI_TTS_ARRAY_LIST_H
#define SAPI_TTS_ARRAY_LIST_H

#include "./defs.h"
#include <stdlib.h>

#define LIST_TYPE u16
typedef LIST_TYPE LIST_T;

struct List {
    LIST_T *data;
    usize dataLength;
    usize length;
};

void list_init(struct List *list);

void list_resize(struct List *list, usize newElementLength);

void list_put(struct List *list, LIST_T a);

LIST_T list_get(struct List *list, usize index);

void list_release(struct List *list);

// note: after taking the data, the list cannot be used anymore, and
// can be viewed as "released",
// thus, `list_release(...)` shouldn't be called, instead call `free(...)` on the taken data
LIST_T *list_take_data(struct List *list);

usize list_length(struct List *list);

#endif //SAPI_TTS_ARRAY_LIST_H
