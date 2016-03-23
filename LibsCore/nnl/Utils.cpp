/*
 * File:   Utils.cpp
 * Author: Anton
 *
 * Created on 18 мая 2014 г., 14:22
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#include "LogSystem.h"
#include "FreedomCase.h"

#include "DataFileTypes.h"
#include "States.h"
#include "Link.h"
#include "Neuron.h"
#include "Layer.h"

#include "Utils.h"

DLL_EXPORT void _ConvertLINKtoLICX(LINK *carrier, LICX *qblk) {
    if (!carrier || (!qblk))return;
    qblk->activated = carrier->activated;
    qblk->weight = carrier->weight;
}

DLL_EXPORT void _ConvertLICXtoLINK(LICX *qblk, LINK *carrier) {
    if (!qblk || (!carrier))return;
    carrier->activated = qblk->activated;
    carrier->weight = qblk->weight;
}

DLL_EXPORT void _ConvertInfoToLCard(NLAYER *from, LC *card) {
    memset(card, 0, sizeof (LC));
    card->state = from->state;
    card->chance = from->chance;
    card->type = from->type;
    card->neurocount = from->neurocount;
    card->neurocount_activ = from->neurocount_activ;
}

DLL_EXPORT void _ConvertInfoToLay(NLAYER *to, LC *card) {
    to->state = card->state;
    to->chance = card->chance;
    to->type = card->type;
    to->neurocount = card->neurocount;
    to->neurocount_activ = card->neurocount_activ;
}

DLL_EXPORT void _ConvertInfoToNeuronCard(NEURON *from, NC *card) {
    memset(card, 0, sizeof (NC));
    card->val = from->val;
    card->retval = from->retval;
    card->postost = from->postost;
    card->incount = from->incount;
    card->outcount = from->outcount;
    card->state = from->state;
    card->chance = from->chance;
    card->OSlayer = -1;
    card->neuronprev = -1;
    card->neuronnext = -1;
    card->LListin = from->in ? from->in->IDOffset : -1;
    card->LListout = from->out ? from->out->IDOffset : -1;
}

DLL_EXPORT void _ConvertInfoToNeuron(NEURON *to, NC *card) {
    to->val = card->val;
    to->retval = card->retval;
    to->postost = card->postost;
    to->incount = card->incount;
    to->outcount = card->outcount;
    to->state = card->state;
    to->chance = card->chance;
}

DLL_EXPORT void _NullLayAround(LayAround *la) {
    la->downlay = -1;
    la->uplay = -1;
    la->nextlay = -1;
    la->prevlay = -1;
    la->NeuroFirst = -1;
}

DLL_EXPORT long _BuryOnceNeuron(NEURON *it, FILE *fh) {
    /*
     * Записывает одиночный нейрон в конец с присваиванием его ID или перезаписывает.
     */
    if ((!it) || (!fh))return -1;
    NEURON *curn = it;
    NC ncard;

    _ConvertInfoToNeuronCard(curn, &ncard);

    if (it->IDOffset == -1) {
	fseek(fh, 0, SEEK_END);
	it->IDOffset = ftell(fh);
	if (fwrite(&ncard, sizeof (NC), 1, fh) != 1)
	    it->IDOffset = -1;
    } else {
	fseek(fh, it->IDOffset, SEEK_SET);
	fwrite(&ncard, sizeof (NC), 1, fh);

    }

    return it->IDOffset;
}

DLL_EXPORT int _BuryListBlock(FILE *fh, long ListOffset, LICX *link) {
    if (ListOffset == (-1))return -1;

    if (!fseek(fh, ListOffset, SEEK_SET)) {
	if (fwrite(link, sizeof (LICX), 1, fh) == 1)
	    return 0;
	else return -2;
    } else return -1;
}

DLL_EXPORT int _BuryListLink(FILE *fh, long LinkOffset, LICL *link) {
    if (LinkOffset == (-1))return -1;

    if (!fseek(fh, LinkOffset, SEEK_SET)) {
	if (fwrite(link, sizeof (LICL), 1, fh) == 1)
	    return 0;
	else return -2;
    } else return -1;
}

DLL_EXPORT int _BuryNeuronBlock(FILE *fh, long NeuroOffset, NC *neuro) {
    if (NeuroOffset == (-1))return -1;

    fseek(fh, NeuroOffset, SEEK_SET);
    fwrite(neuro, sizeof (NC), 1, fh);

    return 0;
}

DLL_EXPORT int _BuryLayerBlock(FILE *fh, long LayerOffset, LC *lcard) {
    if (LayerOffset == (-1))return -1;

    fseek(fh, LayerOffset, SEEK_SET);
    fwrite(lcard, sizeof (LC), 1, fh);

    return 0;
}

Utils::Utils() {
}

Utils::~Utils() {
}


