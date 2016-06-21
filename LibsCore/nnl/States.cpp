#include <stdio.h>
#include <stdlib.h>

#include "DataFileTypes.h"


#include "States.h"

DLL_EXPORT STLib state;

DLL_EXPORT void AddNeuronsCount(int count) {
    state.counts.neurocount = state.counts.neurocount + count;
}

DLL_EXPORT void AddLincsCount(int count) {
    state.counts.linkcount = state.counts.linkcount + count;
}

DLL_EXPORT void AddLinclistsCount(int count) {
    state.counts.linklistcount = state.counts.linklistcount + count;
}

DLL_EXPORT void AddLayersCount(int count) {
    state.counts.layercount = state.counts.layercount + count;
}

DLL_EXPORT STLib *GetStateVariable() {
    return &state;
}
