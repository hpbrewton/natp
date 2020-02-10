#include<stdio.h>

typedef enum {
    function, 
    variable, 
    container, 
    map, 
    stream
} flavor_e;

typedef struct _type_t {
    flavor_e flavor;
    struct _type_t **children; //vector of types
    int data;
} type_t;

void
mk_type(type_t *t, flavor_e f, int data, type_t **children) {
    t->flavor = f;
    t->data = data,
    t->children = children;
}

void
substitute(type_t *t, int vno, type_t *sub) {
    type_t **kids = t->children;
    switch (f) {
    case function: 
    case map:
    substitute(kids[1], vno, sub);
    case container:
    sub
    }
}

int 
arity(flavor_e f) {
    switch(f) {
    case function: return 2; break;
    case map: return 2; break;
    case container: return 1; break;
    case stream: return 1; break;
    case variable: return 0; break;
    }
}

void
show_type(char **ret, type_t *t) {
    char *l;
    char *r;

    switch(t->flavor) {
    case function: 
        ;
        show_type(&l, (t->children)[0]);
        show_type(&r, (t->children)[1]);
        asprintf(ret, "%s -> %s", l, r);
        break;
    case map:
        ;
        show_type(&l, (t->children)[0]);
        show_type(&r, (t->children)[1]);
        asprintf(ret, "[%s]%s", l, r);
        break;
    case container:
        ;
        show_type(&l, (t->children)[0]);
        asprintf(ret, "%d[%s]", t->data, l);
        break;
    case stream:
        ;
        show_type(&l, (t->children)[0]);
        asprintf(ret, "stream %s", l);
        break;
    case variable:
        asprintf(ret, "v%d", t->data);
    }
}

int 
main(int argc, char *argv[]) 
{
    type_t a;
    type_t b; 
    type_t c;
    type_t f;
    mk_type(&a, variable, 1, NULL);
    mk_type(&b, variable, 2, NULL);
    type_t *bptr = &b;
    mk_type(&c, stream, 1, &bptr);
    type_t *ch[] = {&a, &c};
    mk_type(&f, function, 1, ch);
    char *str;
    show_type(&str, &f);
    printf("%s\n", str);
}

