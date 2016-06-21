#ifndef STATES_H
#define STATES_H
#include "libexport.h"

typedef struct _statistics_vars {
    int neurocount;
    int linkcount;
    int linklistcount;
    int layercount;
} StateVar;

typedef struct _warns_info {
    int warn_code;
    void *objectpointer;
    _warns_info *next, *prev;
} WI;

typedef struct _wi_base {
    WI *first, *cur, *end;
} WiBase;

typedef struct _statistics_lib {
    StateVar counts;
    WiBase warnlists;
} STLib;

#ifdef __cplusplus
extern "C" {
#endif

DLL_EXPORT STLib *GetStateVariable();
DLL_EXPORT void AddNeuronsCount(int count);
DLL_EXPORT void AddLincsCount(int count);
DLL_EXPORT void AddLinclistsCount(int count);
DLL_EXPORT void AddLayersCount(int count);

#ifdef __cplusplus
}
#endif

#endif
