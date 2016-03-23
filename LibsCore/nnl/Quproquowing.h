/*
 * File:   Quproquowing.h
 * Author: iceritual
 *
 * Created on 8 июля 2015 г., 15:13
 */

#ifndef QUPROQUOWING_H
#define QUPROQUOWING_H

#include "libexport.h"

typedef struct _BB_nlib_bl {
    NLAYER *DataLay;
    STLib *stat;
    LSD *lst;
    FILE *linkfh, *neurofh, *layerfh, *threadfh, *fredoomeggsfh;
    wchar_t *layerFN, *neuroFN, *linkFN, *threadFN, *fredoomeggsFN;
} BBNB;

enum Quoping_magick {
    ONCEFIDL_LAYERS = 13,
    ONCEFIDL_NEURONS = 12,
    ONCEFIDL_LINKS = 15,
};

DLL_EXPORT class Quproquowing {
public:
    Quproquowing();
    Quproquowing(BBNB *GetdBB);
    virtual ~Quproquowing();

    void OpenBaseBlock(wchar_t *wpath, char UseLog);

    int WriteFreedomCase();
    int ReadFreedomCase();


    int ShtampPointers(long linkOS, LAR *around, LINKL *lnk);
    int TransmutateAndWriteLink(LINKL *cur, NEURON *carrier);
    int TransmutateAndWriteLinks(LINKL *first, NEURON *carrier);

    //    DLL_EXPORT int _AtomizeLINKLfeatsLICX(LINKL *cur, BBNB *wco, LICX *cLINK);
    //    DLL_EXPORT long _TransmutateAndWriteLList(LINKL *first, NEURON *carrier, BBNB *wco);


    int AtomizeNEURONfeatsNC(NEURON *n, NLAYER *lay, NC *card);
    long TransmutateAndWriteNeurons(NEURON *first, NEURON *end, NLAYER *lay);
    long SaveLayerWONeurons(NLAYER *lay, LayAround *quadro);
    int UpdatePointers(long Offset, LayAround *quadro);
    int MultiSaveLayers(NLAYER *FromLAY, NLAYER *curlay, int deep);

    int SaveNet(NLAYER *center, int deep);


    //    DLL_EXPORT LINKL *_UnTransmutateAndReadLinks(BBNB *wco, long first, NEURON *carrier, bool InList);
    LINKL *ReadAndUnTransmutateLinks(long in, long out, NEURON *carrier, int *err);
    NEURON *UnBuryOnceNeuron(long NeuronFP, int *err);
    NEURON *UnTransmutateAndReadNeurons(long NeuronFP, NLAYER *carrier, int *err);
    NLAYER *LoadLayerWONeurons(long LayerID, LayAround *quadro, int *err);
    NLAYER *MultiLoadLayers(NLAYER *FromLOS, long LayerOS, int deep, int *err);

    NLAYER *LoadNet(int deep, int *err);

    void CloseBaseBlock();

private:
    BBNB *BigBlock;
    long AddLICXblk();

};


#ifdef __cplusplus
extern "C" {
#endif
    DLL_EXPORT BBNB *_OpenBaseBlock(wchar_t *wpath, char UseLog);

    DLL_EXPORT int _WriteFreedomCase(BBNB *wco);
    DLL_EXPORT int _ReadFreedomCase(BBNB *wco);

    DLL_EXPORT long _AddLICXblk(BBNB *wco);
    DLL_EXPORT int _ShtampPointers(long linkOS, LAR *around, LINKL *lnk, BBNB *wco);
    DLL_EXPORT int _TransmutateAndWriteLink(LINKL *cur, NEURON *carrier, BBNB *wco);
    DLL_EXPORT int _TransmutateAndWriteLinks(LINKL *first, NEURON *carrier, BBNB *wco);

    //    DLL_EXPORT int _AtomizeLINKLfeatsLICX(LINKL *cur, BBNB *wco, LICX *cLINK);
    //    DLL_EXPORT long _TransmutateAndWriteLList(LINKL *first, NEURON *carrier, BBNB *wco);


    DLL_EXPORT int _AtomizeNEURONfeatsNC(NEURON *n, NLAYER *lay, NC *card, BBNB *wco);
    DLL_EXPORT long _TransmutateAndWriteNeurons(NEURON *first, NEURON *end, NLAYER *lay, BBNB *wco);
    DLL_EXPORT long _SaveLayerWONeurons(NLAYER *lay, LayAround *quadro, BBNB *wco);
    DLL_EXPORT int _UpdatePointers(long Offset, LayAround *quadro, BBNB *wco);
    DLL_EXPORT int _MultiSaveLayers(NLAYER *FromLAY, NLAYER *curlay, BBNB *wco, int deep);

    DLL_EXPORT int _SaveNet(NLAYER *center, int deep, BBNB *wco);


    //    DLL_EXPORT LINKL *_UnTransmutateAndReadLinks(BBNB *wco, long first, NEURON *carrier, bool InList);
    DLL_EXPORT LINKL * _ReadAndUnTransmutateLinks(BBNB *wco, long in, long out, NEURON *carrier, int *err);
    DLL_EXPORT NEURON *_UnBuryOnceNeuron(BBNB *wco, long NeuronFP, int *err);
    DLL_EXPORT NEURON *_UnTransmutateAndReadNeurons(BBNB *wco, long NeuronFP, NLAYER *carrier, int *err);
    DLL_EXPORT NLAYER *_LoadLayerWONeurons(BBNB *wco, long LayerID, LayAround *quadro, int *err);
    DLL_EXPORT NLAYER *_MultiLoadLayers(BBNB *wco, NLAYER *FromLOS, long LayerOS, int deep, int *err);

    DLL_EXPORT NLAYER *_LoadNet(BBNB *wco, int deep, int *err);

    DLL_EXPORT void _CloseBaseBlock(BBNB *BB);


#ifdef __cplusplus
}
#endif

/*
 * К выполнению:
 * ^1.Проверить использование по наличию имеющихся компонентов свободного стека внедрить около ftell-а
 * +2.Сделать сохранение нейронов слоя
 * +3.Сделать сохранение слоёв
 * 4.Раскидать параметр int *err
 * 5.Обернуть в приплюсы.
 */

#endif /* QUPROQUOWING_H */

