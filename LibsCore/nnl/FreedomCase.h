/*
 * File:   FreedomCase.h
 * Author: iceritual
 *
 * Created on 6 июня 2015 г., 11:39
 */

#ifndef FREEDOMCASE_H
#define FREEDOMCASE_H

#include "libexport.h"

enum FIDL_types {
    FIDL_THREADS = 0,
    FIDL_LINKS = 1,
    FIDL_NEURONS,
    FIDL_LAYERS,
    FIDL_GSTACK
};

typedef struct _file_ids_item {
    long FreedoomID; //Свободное место в файле
    void *memberlfidl; //Принадлежность к группе сверху
} FID;

typedef struct _file_ids_list {
    FID data; //Само содержимое ячейки из списка
    void *memberbfidl; //Принадлежность к базовой группе
    _file_ids_list *next, *prev;
} FIDL;

typedef struct base_file_ids_list {
    FIDL *r_fidl, *e_fidl; //r_* = root_*type*;e_* = end_*type*
    char type; //Тип списка
    base_file_ids_list *next, *prev;
} BFIDL;

class DLL_EXPORT FreedomCase {
public:
    FreedomCase();
    FreedomCase(LogSystem *logs);
    virtual ~FreedomCase();
    FIDL *CreateFDL(long IDOffSet, char type);
    FIDL *DeleteFDL(FIDL *cur);
    FIDL *FindFDLByAnyParams(long IDOffSet, char type);
    FIDL *DeleteFDLByParm(long IDOffSet, char type);
    BFIDL *DeleteFDLList(BFIDL *cur);
    BFIDL *DeleteFDLListByType(char type);
private:
    FIDL *NewFDL(BFIDL *parent);
    LogSystem *log;

};

#ifdef __cplusplus
extern "C" {
#endif

DLL_EXPORT FIDL *_CreateFDL(long IDOffSet, char type);
DLL_EXPORT FIDL *_DeleteFDL(FIDL *cur);
DLL_EXPORT FIDL *_FindFDLByAnyParams(long IDOffSet, char type);
DLL_EXPORT FIDL *_DeleteFDLByParm(long IDOffSet, char type);
DLL_EXPORT BFIDL *_DeleteFDLList(BFIDL *cur);
DLL_EXPORT BFIDL *_DeleteFDLListByType(char type);

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!11111111111111!!!!!!!!!!!!!!!!!!!!!!!!!1111111!!!!!!!11
//Сделать сохранение и загрузку свободных ID, не сложнее метода SimulateComa().
//!!!!!!!!!!111111111!11!!11!1111111!!!!11!!11!1111111!111!11!!11111111!!1!!11!11!
extern BFIDL *ultrastack;

#ifdef __cplusplus
}
#endif

#endif /* FREEDOMCASE_H */

