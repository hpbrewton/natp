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

void
mk_type(type_t *t, flavor_e f, int data, type_t **children) {
    t->flavor = f;
    t->data = data,
    t->children = children;
}

int
substitute(type_t *t, int vno, type_t *sub) {
    type_t **kids = t->children;
    switch (t->flavor) {
    case function: 
    case map:
    case container:
    if (substitute(kids[1], vno, sub)) {
        kids[1] = sub;
    }
    case stream:
    if (substitute(kids[0], vno, sub)) {
        kids[0] = sub;
    }
    return 0;
    break;
    case variable:
    return (t->data == vno);
    }
}

int 
unify(vector_t *rules) {
    while (!vec_empty(rules)) {
        type_t *rule[2];
        vec_pop(rules, &rule);
        if ((rule[0]->flavor == rule[1]->flavor) && (rule[0]->data == rule[1]->data)) {
            continue;
        } else if (rule[0]->flavor == variable){
            for (int i = 0; i < vec_len(rules); i++) {
                type_t **curr_rule;
                vec_get(rules, i, &curr_rule);
                substitute(curr_rule[0], rule[0]->data, rule[1]);
                substitute(curr_rule[1], rule[0]->data, rule[1]);
            }
        } else if (rule[1]->flavor == variable) {
            for (int i = 0; i < vec_len(rules); i++) {
                type_t **curr_rule;
                vec_get(rules, i, &curr_rule);
                substitute(curr_rule[0], rule[1]->data, rule[0]);
                substitute(curr_rule[1], rule[1]->data, rule[0]);
            }
        } else if (rule[0]->flavor == rule[1]->flavor && rule[0]->flavor != variable) {
            type_t **new_rules = malloc(sizeof(type_t*)*4);
            new_rules[0] = (rule[0]->children)[0];
            new_rules[1] = (rule[1]->children)[0];
            new_rules[2] = (rule[0]->children)[1];
            new_rules[3] = (rule[1]->children)[1];
            vec_push(rules, new_rules);
            vec_push(rules, &new_rules[2]);
        } else {
            return -1;
        }
    }
    return 0;
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
        asprintf(ret, "(%s -> %s)", l, r);
        break;
    case map:
        ;
        show_type(&l, (t->children)[0]);
        show_type(&r, (t->children)[1]);
        asprintf(ret, "([%s]%s)", l, r);
        break;
    case container:
        ;
        show_type(&l, (t->children)[0]);
        show_type(&r, (t->children)[1]);
        asprintf(ret, "(%s %s)", l, r);
        break;
    case stream:
        ;
        show_type(&l, (t->children)[0]);
        asprintf(ret, "(stream %s)", l);
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
    type_t g;
    type_t h; 
    type_t i; 
    mk_type(&h, variable, 3, NULL);
    mk_type(&i, variable, 4, NULL);
    type_t j;
    type_t *eh[] = {&h, &i};
    mk_type(&j, function, 1, eh);

    mk_type(&a, variable, 1, NULL);
    mk_type(&b, variable, 2, NULL);
    type_t *bptr = &b;
    mk_type(&c, stream, 1, &bptr);
    type_t *ch[] = {&b, &c};
    mk_type(&f, function, 1, ch);
    type_t *dh[] = {&f, &c};
    mk_type(&g, function, 1, dh);
    type_t *rule[2] = {&f, &g};
    char *fstr, *gstr;
    show_type(&fstr, &f);
    show_type(&gstr, &g);
    vector_t v;
    vec_mk(&v, sizeof(rule));
    vec_push(&v, &rule);
    int unifies = unify(&v);
    printf("%s %sunifies with %s\n", fstr, (unifies ? "" : "doesn't "), gstr);
}

