#ifndef LAYER_H
#define LAYER_H

#include "libexport.h"

//TODO

/*
 * +1.Причесать код, расставить логи
 * !2.Справиться с восприятием осознания сохранения... если это вообще возможно...
 * !3.Прикопать в коде удаление которому минимум надобности и максимум
 * 3.Проверить, отладить, заработать.
 */

typedef struct _layer_around {
    long uplay, downlay;
    long nextlay, prevlay;
    long NeuroFirst;
} LayAround;

typedef struct _n_layer {
    NEURON *first, *end;
    int neurocount, neurocount_activ;
    char state, type, chance;
    long IDOffset; //Смещение в файле -1 если не сохранялся или находиться в оперативе
    LayAround *quadro;
    void (*ActivateFunc)(struct _n_layer *layer, NEURON *first, NEURON *end); //Функция активации
    struct _n_layer *down, *up;
    struct _n_layer *next, *prev;
} NLAYER;

typedef struct _data_injector_ { //Сразу так бы
    int count, blksz;
    char flags;
    NEURON *first, *end;
} DIOMAN;

class DLL_EXPORT LayersBase {
public:

    LayersBase();
    LayersBase(LogSystem *logs);

    ~LayersBase() {
    };

    void SetLayerActivateChance(NLAYER *lay, char chance);
    NLAYER *CreateCenterLayer(NEURON *first);
    NLAYER *CreateLayerWNeuroCount(int count, ntype *memblock);
    int AddUperLayer(NLAYER *uplay, NLAYER *center);
    int AddDownLayer(NLAYER *downlay, NLAYER *center);
    int AddPrevLayer(NLAYER *prevlay, NLAYER *center);
    int AddNextLayer(NLAYER *nextlay, NLAYER *center);
    int AddNeuroListToLayer(NLAYER *lay, NEURON *first, NEURON *end);
    NLAYER *CreateHiLoHiLayer(NLAYER *down, NLAYER *up, NEURON *first);
    NLAYER *CreateParallelLayer(NLAYER *prev, NLAYER *next, NEURON *first);
    void DeleteLayer(NLAYER *it);
    void MoveDataFromLayer(NLAYER *from, NLAYER *to);
    int ConnectLayer(NLAYER *first, NLAYER *second, char method, int (*func)(NLAYER *, NLAYER *));
    int ConnectLayerToNeuron(NLAYER *first, NEURON *it, char method);
    NEURON *GetNeuronByID(NLAYER *cur, long IDOffSet);


    void ActivateLayer(NLAYER *lay);
    int SetDataToLayer(ntype *mass, int n, NLAYER *lay);
    int SetIntDataToLayer(int *mass, int n, NLAYER *lay);
    int SetShortDataToLayer(short *mass, int n, NLAYER *lay);
    int SetByteDataToLayer(unsigned char *mass, int n, NLAYER *lay);

    DIOMAN *DataInjectStart(int szoftobox, int szofdata, void *data);
    bool DataInjectNext(DIOMAN *InJack, int szofdata, void *data);
    ntype *GetNtypeMassFromDIJ(DIOMAN *InJack);
    void DataInjectEnd(DIOMAN *InJack);

private:
    LogSystem *log;

};

#ifdef __cplusplus
extern "C" {
#endif

//Если все пути сводяться к 0 в пересечении нужно клонировать этот слой в параллель методом философского камня ;)
//... много времени спустя рукава.
//-Естъ такой методъ!.
DLL_EXPORT void _SetLayerActivateChance(NLAYER *lay, char chance);
DLL_EXPORT NLAYER *_CreateCenterLayer(NEURON *first);
DLL_EXPORT NLAYER *_CreateLayerWNeuroCount(int count, ntype *memblock);
DLL_EXPORT int _AddUperLayer(NLAYER *uplay, NLAYER *center);
DLL_EXPORT int _AddDownLayer(NLAYER *downlay, NLAYER *center);
DLL_EXPORT int _AddPrevLayer(NLAYER *prevlay, NLAYER *center);
DLL_EXPORT int _AddNextLayer(NLAYER *nextlay, NLAYER *center);
DLL_EXPORT int _AddNeuroListToLayer(NLAYER *lay, NEURON *first, NEURON *end);
DLL_EXPORT NLAYER *_CreateHiLoHiLayer(NLAYER *down, NLAYER *up, NEURON *first);
DLL_EXPORT NLAYER *_CreateParallelLayer(NLAYER *prev, NLAYER *next, NEURON *first);
DLL_EXPORT void _DeleteLayer(NLAYER *it);
DLL_EXPORT void _MoveDataFromLayer(NLAYER *from, NLAYER *to);
DLL_EXPORT int _ConnectLayer(NLAYER *first, NLAYER *second, int method, int (*func)(NLAYER *, NLAYER *));
DLL_EXPORT int _ConnectLayerToNeuron(NLAYER *first, NEURON *it, int method);
DLL_EXPORT NEURON *_GetNeuronByID(NLAYER *cur, long IDOffSet);

DLL_EXPORT void _ActivateLayer(NLAYER *lay);
//DLL_EXPORT NLAYER *_GetRetVals(NLAYER *to,NLAYER *actedlay,int mcount,ntype *request);
//---Баловство в стиле впиховывать невпихуемое----------------
DLL_EXPORT DIOMAN *_DataInjectStart(int szoftobox, int szofdata, void *data);
DLL_EXPORT bool _DataInjectNext(DIOMAN *InJack, int szofdata, void *data);
DLL_EXPORT ntype *_GetNtypeMassFromDIJ(DIOMAN *InJack); //Используйте free(ntype) гдепопало.
DLL_EXPORT void _DataInjectEnd(DIOMAN *InJack);
//---------------Rj-...знаЧит Это кому-нибудъ нужно...---------------------
DLL_EXPORT int _SetDataToLayer(ntype *mass, int n, NLAYER *lay);
DLL_EXPORT int _SetIntDataToLayer(int *mass, int n, NLAYER *lay);
DLL_EXPORT int _SetShortDataToLayer(short *mass, int n, NLAYER *lay);
DLL_EXPORT int _SetByteDataToLayer(unsigned char *mass, int n, NLAYER *lay);

#ifdef __cplusplus
}
#endif

#endif
