/*
 * File:   DataFileTypes.h
 * Author: 123
 *
 * Created on 1 Март 2014 г., 18:58
 */

#ifndef DATAFILETYPES_H
#define DATAFILETYPES_H


#define ntype int

//#define ntype int   //(void *)int="Указатель на область памяти )"
#ifdef WIN32
#define TRUE_SLASH L"\\"
#else
#define TRUE_SLASH L"/"
#endif


#define STATE_NOT_READY 0
#define STATE_READY  1
#define STATE_EXCITED   2


#define _PREFIX_LINKLIST 0xA000FF01

typedef struct _linclist_card {
    long listnext, listprev; //Позиция в файле предидущей и последующей структуры LICX
} LICL;

typedef struct _linklist_blk {
    LICL inlist, outlist;
} LAR; //Указатели на списки связи

typedef struct _linc_cardX {
    LAR around; //Указатели на списки связи
    //    LICL inlst, outlst; //Указатели на списки связи
    long OSneurofrom, OSneuroto; //Указатели на прицепленность к нейронам
    ntype weight; //Накопительный вес связи
    int activated; //Количество использований связи до активации нейрона
    void *memorypoint;
} LICX;

#define _PREFIX_NEURON  0xA000FF02

typedef struct _neuron_card {
    long neuronnext, neuronprev;
    ntype val, retval;
    int postost;
    char state, chance;
    short incount, outcount;
    long LListin, LListout;
    long OSlayer;
    void *memorypoint;
} NC;

#define _PREFIX_LAYER  0xA000FF03

typedef struct _lay_around {
    long downcard, upcard;
    long nextcard, prevcard;
} LA;

typedef struct _logic_card {
    LA around;
    long neurofirst;
    int neurocount, neurocount_activ;
    char state, type, chance;
    void *memorypoint;
} LC;

typedef struct _thread_neuro_block {
    long LayerOS;
    long NeuroOS;
    char shance;
} NBT;

//Протестить приведение из char type to int type и наоборот

typedef struct _freedoom_case_base_block {
    int itemscount, type;
    long entrypoint;
} FCBB;

void *_MallocZeroBytes(unsigned int size);

#ifdef __linux__

#define __stdcall

int _wCrossUnlink(const wchar_t* filename);
FILE *_wCrossFopen(const wchar_t* filename, const wchar_t* mode);
int _wCrossAccess(const wchar_t* filename, int mode); //Аналог int access() только для пухлых символик

#else
//Венда, домохозяюшка и классная наложница ;)

#endif

#endif /* DATAFILETYPES_H */

