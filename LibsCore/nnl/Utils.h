/*
 * File:   Utils.h
 * Author: Anton
 *
 * Created on 18 мая 2014 г., 14:22
 */

#ifndef UTILS_H
#define	UTILS_H

#include "libexport.h"

class DLL_EXPORT Utils {
public:
    Utils();
    virtual ~Utils();

};

DLL_EXPORT void _ConvertLINKtoLICX(LINK *carrier, LICX *qblk);
DLL_EXPORT void _ConvertLICXtoLINK(LICX *qblk, LINK *carrier);
DLL_EXPORT void _ConvertInfoToLCard(NLAYER *from, LC *card);
DLL_EXPORT void _ConvertInfoToLay(NLAYER *to, LC *card);
DLL_EXPORT void _ConvertInfoToNeuronCard(NEURON *from, NC *card);
DLL_EXPORT void _ConvertInfoToNeuron(NEURON *to, NC *card);
DLL_EXPORT void _NullLayAround(LayAround *la);
DLL_EXPORT long _BuryOnceNeuron(NEURON *it, FILE *fh);
DLL_EXPORT int _BuryListBlock(FILE *fh, long ListOffset, LICX *link);
DLL_EXPORT int _BuryListLink(FILE *fh, long LinkOffset, LICL *link);
DLL_EXPORT int _BuryNeuronBlock(FILE *fh, long NeuroOffset, NC *neuro);
DLL_EXPORT int _BuryLayerBlock(FILE *fh, long LayerOffset, LC *lcard);

#endif	/* UTILS_H */

