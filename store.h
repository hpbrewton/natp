#ifndef _STORE_H_
#define _STORE_H_
#include "type.h"

typedef int uuid;
typedef struct _pair_t {
  type_t *type;
  char *loc;
} pair_t;

typedef vector_t store_t;

int
add(store_t *store, type_t *type, char *loc);

void
get(store_t *store, type_t *type);

void
store_mk(store_t *s);

#endif // _STORE_H_
