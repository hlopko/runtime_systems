#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <assert.h>

#define __error__( what )                           \
    {                                               \
        fprintf(stderr, "ERROR (%s:%d) : ",         \
                __FILE__, __LINE__);                \
        what;                                       \
        fflush(stderr);                             \
        abort();                                    \
    }

#define error0( msg ) __error__( fprintf (stderr, msg )  )
#define error1( msg, a1 ) __error__( fprintf (stderr, msg, a1 ) )
#define error2( msg, a1, a2 ) __error__( { fprintf (stderr, msg, a1, a2 ); } )

typedef enum { POINTER_INDEXED, BYTE_INDEXED } obj_kind;

#define obj_header        \
    obj_kind kind;        \
    int  size;            \
    struct obj *class;    \

typedef struct obj {
    obj_header;
    union {
        struct obj *fields[0];
        char        bytes[0];
    } data;
} obj;

#define obj_size( obj ) \
    ( (obj) == NULL ? 0 : (obj)->size )

#define obj_field_get( obj, index ) \
    ( (obj) == NULL ? NULL : (obj)->data.fields[index] )

#define obj_field_set( obj, index, value ) \
    ( (obj)->data.fields[index] = value )

#define obj_bytes( obj ) \
    ( (obj) == NULL ? NULL : (obj)->data.bytes )



typedef obj* (*obj_func0)(obj* this) ;
typedef obj* (*obj_func1)(obj* this, obj* a1) ;
typedef obj* (*obj_func2)(obj* this, obj* a1, obj* a2) ;
/* ... */


typedef struct method {
    obj_header;
    obj *selector;
    union {
        obj_func0 f0;
        obj_func1 f1;
        obj_func2 f2;
        /* ... */
    } code;
} method;

typedef struct class {
    obj_header;
    obj *name;
    struct class *superclass;
    obj    *methods;
} class;

/*
   Allocates a new object of given class, object kind
   (pointer-indexed of byte-indexed) and size.
   for pointer-indexed objects size means number of
   fields. For byte-indexed objects size means length
   of byte array
*/

obj* new_obj(class *cls, obj_kind kind, int size) {
    int size_in_words = 0;
    obj* o;

    if (kind == POINTER_INDEXED) {
        size_in_words += size;
    } else {
        size_in_words += (((size + 1) | 0x03) - 1) >> 2;
    }
    o = (obj*) malloc(sizeof ( o ) + size_in_words * 4);
    /* nil it out */
    bzero( (void*) o, sizeof ( o ) + size_in_words * 4 );
    o->size = size;
    o->class = (obj*)cls;
    return o;
}

obj* new_string(class *cls, char *bytes) {
    obj* o = new_obj( cls, BYTE_INDEXED, strlen ( bytes ) );
    strcpy( obj_bytes ( o ) , bytes );
    return o;
}

/*
   Instantiates a class object with given metaclass,
   name and superclass.
*/
class* new_class(class *metaclass, char* name, class *superclass) {
    class* c = (class*) malloc ( sizeof ( class ) );
    c->size = (sizeof ( class ) - sizeof ( obj ) ) / sizeof ( obj* );
    c->class = (obj*)metaclass;
    c->name = new_string(NULL/* TODO */,  name);
    c->superclass = superclass;
    c->methods = NULL;
    return c;
}

/*
   Defines a method with given selector in given class. obj_func0
   should point to a method's machine code.
*/
method* def_method(class *cls, char *selector, int n_args, obj_func0 f) {
    int i;
    method* m = (method*) malloc ( sizeof ( method ) );
    m->size = (sizeof ( method ) - sizeof ( obj ) ) / sizeof ( obj* );
    m->class = NULL/* TODO */;
    m->selector = new_string(NULL/* TODO */,  selector);
    switch (n_args) {
    case 0:
        m->code.f0 = (obj_func0)f;
        break;
    case 1:
        m->code.f1 = (obj_func1)f;
        break;
    case 2:
        m->code.f2 = (obj_func2)f;
        break;
    default:
        error1("Only method with less than 2 args are supported (%d given)\n",
               n_args);
        break;
    }
    if (cls->methods == NULL) cls->methods = new_obj(NULL/* TODO */, POINTER_INDEXED, 2);
    while ( 1 ) {
        for (i = 0 ; i < obj_size( cls->methods ) ; i++) {
            if (obj_field_get(cls->methods, i) == NULL) {
                obj_field_set(cls->methods, i, (obj*) m);
                return m;
            }
        }
        obj *methods_new = new_obj(NULL/* TODO */, POINTER_INDEXED, obj_size(cls->methods)*2);
        for (i = 0 ; i < obj_size ( cls->methods ) ; i++)
            obj_field_set(methods_new, i, obj_field_get(cls->methods, i));
        cls->methods = methods_new;
    }
}

method* lookup ( class *search, char* selector) {
    class* cls = search;
    int i;
    while ( cls ) {
        for ( i = 0; i < obj_size ( cls->methods ) ; i++ ) {
            if (obj_field_get(cls->methods, i) != NULL) {
                method* m = (method*)obj_field_get(cls->methods, i);
                if (strcmp(selector, obj_bytes(m->selector)) == 0)
                    return m;
            }
        }
        cls = cls->superclass;
    }
    return NULL;
}

obj* send0 ( obj* rec, char *selector ) {
    method* m = lookup ( (class*)rec->class, selector );
    if (m == NULL) error1("No method found (%s)\n", selector);
    return m->code.f0(rec);
}

static obj* expected;

obj* A__foo(obj* this) {
    return expected;
}

obj* B__foo(obj* this) {
    return NULL;
}

#define SEND0_ILC( rec, selector )                                      \
    ({                                                                  \
        static class* cached_class = NULL;                              \
        static obj_func0 cached_f = NULL;                               \
        if ((class*)rec->class != cached_class) {                       \
            method* m = lookup ( (class*)rec->class, selector );        \
            if (m == NULL) error1("No method found (%s)\n", selector);  \
            cached_f = m->code.f0;                                      \
            cached_class = (class*)rec->class;                          \
        }                                                               \
        cached_f(rec);                                                  \
    })

#define SEND0 SEND0_ILC


int main ( int argc, char **argv ) {
    int i;

    printf("USING ILC\n");

    expected    = new_obj(NULL, POINTER_INDEXED, 0);

    class  *A   = new_class(NULL, "A", NULL);
    method *m   = def_method(A, "foo", 0, &A__foo);
    obj    *a   = new_obj(A, POINTER_INDEXED, 0);

    class  *B   = new_class(NULL, "B", A);
            m   = def_method(B, "foo", 0, &B__foo);
    obj    *b   = new_obj(B, POINTER_INDEXED, 0);

    obj* a_foo = SEND0 ( a , "foo" );
    assert(a_foo == expected);

    obj* b_foo = SEND0 ( b , "foo" );
    assert(b_foo == NULL);

    for (i = 0; i < (1000 * 1000 * 100); i++) {
        obj *r = SEND0 ( a, "foo" );
        assert (r == expected);
    }

    return 0;
}

/*
   Homeworks:
   1) Change the code above to use VMTs instead of
      method dictionaries.
   2) Implement a multiple inheritance.
   3) Extend ILC to use polymorphic inline cache
      iff ILC fails. Measure its impact on performance.
*/
