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

#define ABSOLUTE_MIN	0
#define ABSOLUTE_MAX	1
#define ABSOLUTE_LAST   8
#define ABSOLUTE_WEIGHT 2
#define ABSOLUTE_ACTIVE 4


#define DIRECT_TOPREV	0
#define DIRECT_TONEXT	1


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
    LINKL *IncertListItem(LINKL *item,LINKL *prev,LINKL *next);
    LINKL *CompareWeightFinding(LINK *item,LINKL *entry,int absolute,int direction);
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
    DLL_EXPORT LINKL *_IncertListItem(LINKL *item,LINKL *prev,LINKL *next);
    DLL_EXPORT LINKL *_CompareWeightFinding(LINK *item,LINKL *entry,int absolute,int direction);
    DLL_EXPORT int _DeleteLinkWList(LINK *it);
    DLL_EXPORT int _DeleteLinksList(LINKL *first);

#ifdef __cplusplus
}
#endif

#endif
