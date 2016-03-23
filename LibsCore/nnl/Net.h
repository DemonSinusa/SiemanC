/*
 * File:   Net.h
 * Author: Anton
 *
 * Created on 22 мая 2014 г., 14:34
 */

#ifndef NET_H
#define NET_H

#include "libexport.h"


#define COMPAS_ENDDOWN      0
#define COMPAS_ENDRIGHT     1
#define COMPAS_ENDUP        2
#define COMPAS_ENDLEFT      3

#define CARDMETHOD_SIMPLE   0
#define CARDMETHOD_GODEVE   1

DLL_EXPORT class Net {
public:
    LinksBase *LinkFuncs;
    NeuronsBase *NeuronFuncs;
    LayersBase *LayerFuncs;
    Net();
    ~Net();
    NLAYER *CreateFrameworkNet(char vectorcompass, int MaxFOfMainLay, int MaxFOfEndLay, char DefConnectLayMet, int (*func)(NLAYER *from, NLAYER *to));
    NLAYER *UseManyToOneConnect(char vectorcompass, int MaxFOfMainLay, int MaxFOfEndLay, char DefConnectLayMet, int (*func)(NLAYER *from, NLAYER *to));
    NLAYER *UseOneToManyConnect(char vectorcompass, int MaxFOfMainLay, int MaxFOfEndLay, char DefConnectLayMet, int (*func)(NLAYER *from, NLAYER *to));
    NLAYER *GetDeeperLayer(NLAYER *mainlay, char vectorcompass);
private:
    LogSystem *log;

};

#ifdef __cplusplus
extern "C" {
#endif

    DLL_EXPORT NLAYER *_UseManyToOneConnect(char vectorcompass, int MaxFOfMainLay, int MaxFOfEndLay, char DefConnectLayMet, int (*func)(NLAYER *from, NLAYER *to));
    DLL_EXPORT NLAYER *_UseOneToManyConnect(char vectorcompass, int MaxFOfMainLay, int MaxFOfEndLay, char DefConnectLayMet, int (*func)(NLAYER *from, NLAYER *to));

    DLL_EXPORT NLAYER *_CreateFrameworkNet(char vectorcompass, int MaxFOfMainLay, int MaxFOfEndLay, char DefConnectLayMet, int (*func)(NLAYER *from, NLAYER *to));
    DLL_EXPORT NLAYER *_GetDeeperLayer(NLAYER *mainlay, char vectorcompass);

#ifdef __cplusplus
}
#endif

#endif /* NET_H */

