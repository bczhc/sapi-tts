#include "array_list.h"

void list_init(struct List *list) {
    for (int i = 0; i < sizeof(struct List); ++i) {
        ((u8 *) list)[i] = 0;
    }
    list->length = 0;
    list->dataLength = 10;
    list->data = malloc(list->dataLength * sizeof(LIST_T));
}

void list_resize(struct List *list, usize newElementLength) {
    list->dataLength = newElementLength;
    list->data = realloc(list->data, list->dataLength * sizeof(LIST_T));
}

void list_put(struct List *list, LIST_T a) {
    if (list->length + 1 > list->dataLength) {
        // enlarge memory
        list_resize(list, list->dataLength * 2);
    }
    list->data[list->length] = a;
    list->length += 1;
}

LIST_T list_get(struct List *list, usize index) {
    return list->data[index];
}

void list_release(struct List *list) {
    free(list->data);
}

LIST_T *list_take_data(struct List *list) {
    LIST_T *data = list->data;
    list->data = NULL;
    return data;
}

usize list_length(struct List *list) {
    return list->length;
}
