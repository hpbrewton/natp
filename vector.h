#ifndef _VECTOR_H_
#define _VECTOR_H_

typedef struct _vector_t {
  int used;
  int unused;
  int part;
  void *data;
} vector_t;

void
vec_mk(vector_t *vec, int part);

void
vec_trunc(vector_t *vec);

void
vec_grow(vector_t *vec);

int 
vec_get_void(vector_t *vec, int index, void *data);

void
vec_push_void(vector_t *vec, void *data);

int
vec_pop_void(vector_t *vec, void *data);

#define vec_get(obj, index, data) (vec_get_void(obj, index, (void *) data))
#define vec_pop(obj, data) (vec_pop_void(obj, (void *) data))
#define vec_push(obj, data) (vec_push_void(obj, (void *) data))
#define vec_empty(obj) (obj->used == 0)
#define vec_len(obj) (obj->used)

#endif // _VECTOR_H_
