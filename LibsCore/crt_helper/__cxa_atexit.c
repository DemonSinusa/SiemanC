#include <swilib.h>

typedef struct
{
    void (*func)(void*);
    void *object;
    void *next;
}__cxa_atexit_struct;




