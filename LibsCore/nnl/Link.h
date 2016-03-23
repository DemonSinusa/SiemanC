#ifndef LINK_H
#define LINK_H
#include "libexport.h"

typedef struct _link {
    ntype weight; //Вес связи
    int activated; //Уровень возбуждения
    void *from, *to; //это указатель на список "от" к "до"
} LINK;

typedef struct _link_list {
    LINK *link; //Указатель на связь
    char state; //Флаг статуса готов\не готов
    //int count;
    void *Neuron; //Указатель на нейрон к которому принадлежит этот список
    long IDOffset; //Смещение в файле -1 если не сохранялся или находиться в оперативе
    struct _link_list *next, *prev;
} LINKL;

class DLL_EXPORT LinksBase {
public:
    LinksBase();
    LinksBase(LogSystem *logs);

    ~LinksBase() {
    };

    int SetLinkWeight(LINK *it, ntype weight);
    LINK *CreateLink(ntype weight);
    void FreeLink(LINK *it);
    LINK *SetLinkToList(LINK *it, LINKL *from, LINKL *to);
    LINKL *CreateLinkListItem(LINKL *prev);
    LINKL *FreeLinkListItem(LINKL *it);
    LINKL *GetEndListItem(LINKL *first);
    int DeleteLinkWList(LINK *it);
    int DeleteLinksList(LINKL *first);
private:
    LogSystem *log;
};

#ifdef __cplusplus
extern "C" {
#endif

    DLL_EXPORT int _SetLinkWeight(LINK *it, ntype weight);
    DLL_EXPORT LINK *_CreateLink(ntype weight);
    DLL_EXPORT void _FreeLink(LINK *it);
    DLL_EXPORT LINK *_SetLinkToList(LINK *it, LINKL *from, LINKL *to);
    DLL_EXPORT LINKL *_CreateLinkListItem(LINKL *prev);
    DLL_EXPORT LINKL *_FreeLinkListItem(LINKL *it);
    DLL_EXPORT LINKL *_GetEndListItem(LINKL *first);
    DLL_EXPORT int _DeleteLinkWList(LINK *it);
    DLL_EXPORT int _DeleteLinksList(LINKL *first);

#ifdef __cplusplus
}
#endif

#endif