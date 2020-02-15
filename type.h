#ifndef _TYPE_H_
#define _TYPE_H_

#include<stdio.h>
#include<stdlib.h>
#include"vector.h"

typedef enum {
    variable, 
    function, 
    container, 
    map, 
    stream
} flavor_e;

typedef struct _type_t {
    flavor_e flavor;
    struct _type_t **children; //vector of types
    int data;
} type_t;
typedef type_t* rule_t [2];

void
mk_type(type_t *t, flavor_e f, int data, type_t **children);

int
substitute(type_t *t, int vno, type_t *sub);

int 
unify(vector_t *rules);

void
show_type(char **ret, type_t *t);


#endif // _TYPE_H_

