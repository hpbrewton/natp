#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vector.h"

void debug_int(vector_t *v);

void
vec_mk(vector_t *vec, int part) {
  vec->used = 0;
  vec->unused = 16;
  vec->part = part;
  vec->data = malloc(part*(vec->unused));
}

void
vec_trunc(vector_t *vec) {
  void *copy = malloc(vec->part*vec->used);
  strncpy(copy, vec->data, vec->used*vec->part);
  vec->unused = 0;
  free(vec->data);
  vec->data = copy;
}

void
vec_grow(vector_t *vec) {
  int new_size = 2*(vec->used+vec->unused);
  void *dst = malloc(new_size*vec->part);
  printf("%d %d\n", vec->used, vec->part);
  dst = memcpy(dst, vec->data, (vec->used)*(vec->part));
  vec->unused = new_size-(vec->used);
  free(vec->data);
  vec->data = dst;
  debug_int(vec);
}

void
vec_push_void(vector_t *vec, void *data) {
  if (0 == vec->unused)
    vec_grow(vec);
  memcpy(&vec->data[vec->used*vec->part], data, vec->part);
  ++vec->used;
  --vec->unused;
}

int
vec_pop_void(vector_t *vec, void *data){
  if (0 == vec->used)
    return -1;
  memcpy(data, &vec->data[vec->used*vec->part], vec->part);
  --vec->used;
  ++vec->unused;
  return 0;
}

void
debug_int(vector_t *vec) {
  printf("[");
  for (int i = 0; i < vec->used; i++) {
    printf("%d", ((int*) vec->data)[i]);
    if (i+1 < vec->used)
      printf(", ");
  }
  printf("], bytes unused: %d\n", vec->unused);
}


int
main() {
  vector_t v;
  vec_mk(&v, sizeof(int));
  int seven = 7;
  vec_push(&v, &seven);
  vec_push(&v, &seven);
  vec_push(&v, &seven);  vec_push(&v, &seven);
  debug_int(&v);
}
