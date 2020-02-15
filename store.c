#include<stdio.h>
#include "store.h"
#include "type.h"

int
add(store_t *store, type_t *type, char *loc) {
  // push
  pair_t *pair = malloc(sizeof(pair_t));
  pair->type = type;
  pair->loc = loc;
  vec_push(store, pair);
  return 0;
}

void
get(store_t *store, type_t *type) {
  pair_t *curr;
  type_t *rule[2];
  vector_t rules;
  vec_mk(&rules, sizeof(rule_t));
  for (int i = 0; i < store->used; i++) {
    vec_get(store, i, curr);
    rule[0] = curr->type;
    rule[1] = type;
    vec_push(&rules, rule);
    if (unify(&rules)) {
      char *str;
      show_type(&str, curr->type);
      printf("%s at %s\n", str,  curr->loc);
    }
  }
}

void
store_mk(store_t *s) {
  vec_mk(s, sizeof(pair_t*));
}
