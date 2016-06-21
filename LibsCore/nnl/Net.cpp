/*
 * File:   Net.cpp
 * Author: Anton
 *
 * Created on 22 мая 2014 г., 14:34
 *
 * ТУДУ
 * 1.Создать динамический стек замкнутый сам на себя,
 * увеличивающий свой потенциал в зависимости от разнообразия входных данных
 * увеличивающися при избытке и уменьшающийся при диффеците данных
 *
 * Проверить работоспособность _ConnectLayer на подключении слоя с меньшим кол-вом нейронов к злою с большем кол-вом
 * Проверка на память ищеться по комментам, но делается в последнюю очередь,
 * но до первого запуска, сначала соль, а уж потом мы сможем заморозить весь город.
 */

#ifdef NEURO_LIB_WTHREAD
#include <windows.h>	//Нужна для нейронных потоков в winapi
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "LogSystem.h"
#include "FreedomCase.h"

#include "DataFileTypes.h"
#include "Link.h"
#include "Neuron.h"
#include "Layer.h"
#include "States.h"
#include "Net.h"

/*
Функция создает каркас сети выбранным методом с типом связей большее к меньшему
возвращает основной движущий слой либо NULL при ошибке, которой не бывает в рамках данной функции)
параметры:
vectorcompass-направление в котором следует распространять сеть
MaxFOfMainLay-максимальное количество нейронов на движущем слое
MaxFOfEndLay-максимальное количество нейронов на конечном слое
DefConnectLayMet-метод соединения слоев по умолчанию
func-своя функция соединения слоев (имеет бОльший приоритет чем метод соединения слоев по умолчанию)
 */
DLL_EXPORT NLAYER *_UseManyToOneConnect(char vectorcompass, int MaxFOfMainLay, int MaxFOfEndLay, char DefConnectLayMet, int (*func)(NLAYER *from, NLAYER *to)) {
    NLAYER *mainlay = NULL, *templay = NULL;
    int undercount = MaxFOfMainLay;

    mainlay = templay = _CreateLayerWNeuroCount(undercount, 0);
    _SetLayerActivateChance(templay, 0);
    undercount--;

    switch (vectorcompass) {
    case COMPAS_ENDDOWN: {
        while (undercount > MaxFOfEndLay) {
            //Каркас делается вглубь... Почему не в лево, не вправо?
            templay->down = _CreateLayerWNeuroCount(undercount, 0);
            _SetLayerActivateChance(templay->down, 100 - (undercount / MaxFOfMainLay * 100));
            if (func)_ConnectLayer(templay, templay->down, 0, func);
            else _ConnectLayer(templay, templay->down, DefConnectLayMet, NULL);
            templay = templay->down;
            undercount--;
        }
        break;
    }
    case COMPAS_ENDRIGHT: {
        while (undercount > MaxFOfEndLay) {
            //Каркас делается вглубь... Почему не в лево, не вправо?
            templay->next = _CreateLayerWNeuroCount(undercount, 0);
            _SetLayerActivateChance(templay->next, 100 - (undercount / MaxFOfMainLay * 100));
            if (func)_ConnectLayer(templay, templay->next, 0, func);
            else _ConnectLayer(templay, templay->next, DefConnectLayMet, NULL);
            templay = templay->next;
            undercount--;
        }
        break;
    }
    case COMPAS_ENDUP: {
        while (undercount > MaxFOfEndLay) {
            //Каркас делается вглубь... Почему не в лево, не вправо?
            templay->up = _CreateLayerWNeuroCount(undercount, 0);
            _SetLayerActivateChance(templay->up, 100 - (undercount / MaxFOfMainLay * 100));
            if (func)_ConnectLayer(templay, templay->up, 0, func);
            else _ConnectLayer(templay, templay->up, DefConnectLayMet, NULL);
            templay = templay->up;
            undercount--;
        }
        break;
    }
    case COMPAS_ENDLEFT: {
        while (undercount > MaxFOfEndLay) {
            //Каркас делается вглубь... Почему не в лево, не вправо?
            templay->prev = _CreateLayerWNeuroCount(undercount, 0);
            _SetLayerActivateChance(templay->prev, 100 - (undercount / MaxFOfMainLay * 100));
            if (func)_ConnectLayer(templay, templay->prev, 0, func);
            else _ConnectLayer(templay, templay->prev, DefConnectLayMet, NULL);
            templay = templay->prev;
            undercount--;
        }
        break;
    }
    default: {
        while (undercount > MaxFOfEndLay) {
            //Каркас делается вглубь... Почему не в лево, не вправо?
            templay->down = _CreateLayerWNeuroCount(undercount, 0);
            _SetLayerActivateChance(templay->down, 100 - (undercount / MaxFOfMainLay * 100));
            if (func)_ConnectLayer(templay, templay->down, 0, func);
            else _ConnectLayer(templay, templay->down, DefConnectLayMet, NULL);
            templay = templay->down;
            undercount--;
        }
        break;
    }
    }
    return mainlay;
}

/*
Функция создает каркас сети выбранным методом с типом связей меньшее к большему
возвращает основной движущий слой либо NULL при ошибке, которой не бывает в рамках данной функции)
параметры:
vectorcompass-направление в котором следует распространять сеть
MaxFOfMainLay-максимальное количество нейронов на движущем слое
MaxFOfEndLay-максимальное количество нейронов на конечном слое
DefConnectLayMet-метод соединения слоев по умолчанию
func-своя функция соединения слоев //(имеет бОльший приоритет чем метод соединения слоев по умолчанию)
 */
DLL_EXPORT NLAYER *_UseOneToManyConnect(char vectorcompass, int MaxFOfMainLay, int MaxFOfEndLay, char DefConnectLayMet, int (*func)(NLAYER *from, NLAYER *to)) {
    NLAYER *mainlay = NULL, *templay = NULL;
    int cunt = MaxFOfMainLay;

    mainlay = templay = _CreateLayerWNeuroCount(cunt, 0);
    _SetLayerActivateChance(templay, 0);
    cunt++;

    switch (vectorcompass) {
    case COMPAS_ENDDOWN: {
        while (cunt < MaxFOfEndLay) {
            templay->down = _CreateLayerWNeuroCount(cunt, 0);
            _SetLayerActivateChance(templay->down, 100);
            if (func)_ConnectLayer(templay, templay->down, 0, func);
            else _ConnectLayer(templay, templay->down, DefConnectLayMet, NULL);
            templay = templay->down;
            cunt++;
        }
        break;
    }
    case COMPAS_ENDRIGHT: {
        while (cunt < MaxFOfEndLay) {
            templay->next = _CreateLayerWNeuroCount(cunt, 0);
            _SetLayerActivateChance(templay->next, 100);
            if (func)_ConnectLayer(templay, templay->next, 0, func);
            else _ConnectLayer(templay, templay->next, DefConnectLayMet, NULL);
            templay = templay->next;
            cunt++;
        }
        break;
    }
    case COMPAS_ENDUP: {
        while (cunt < MaxFOfEndLay) {
            templay->up = _CreateLayerWNeuroCount(cunt, 0);
            _SetLayerActivateChance(templay->up, 100);
            if (func)_ConnectLayer(templay, templay->up, 0, func);
            else _ConnectLayer(templay, templay->up, DefConnectLayMet, NULL);
            templay = templay->up;
            cunt++;
        }
        break;
    }
    case COMPAS_ENDLEFT: {
        while (cunt < MaxFOfEndLay) {
            templay->prev = _CreateLayerWNeuroCount(cunt, 0);
            _SetLayerActivateChance(templay->prev, 100);
            if (func)_ConnectLayer(templay, templay->prev, 0, func);
            else _ConnectLayer(templay, templay->prev, DefConnectLayMet, NULL);
            templay = templay->prev;
            cunt++;
        }
        break;
    }
    default: {
        while (cunt < MaxFOfEndLay) {
            templay->down = _CreateLayerWNeuroCount(cunt, 0);
            _SetLayerActivateChance(templay->down, 100);
            if (func)_ConnectLayer(templay, templay->down, 0, func);
            else _ConnectLayer(templay, templay->down, DefConnectLayMet, NULL);
            templay = templay->down;
            cunt++;
        }
        break;
    }
    }

    return mainlay;
}

/*
Функция создает каркас сети с автоматическим расчетом метода соединения слоев в зависимости от указаных параметров
и возвращает основной движущий слой либо NULL при ошибке, которой не бывает в рамках данной функции)
лучше использовать эту функцию для создания каркаса если не знаете, что делаете.
параметры:
vectorcompass-направление в котором следует распространять сеть
MaxFOfMainLay-максимальное количество нейронов на движущем слое
MaxFOfEndLay-максимальное количество нейронов на конечном слое
DefConnectLayMet-метод соединения слоев по умолчанию
func-своя функция соединения слоев //(имеет бОльший приоритет чем метод соединения слоев по умолчанию)
 */
DLL_EXPORT NLAYER *_CreateFrameworkNet(char vectorcompass, int MaxFOfMainLay, int MaxFOfEndLay, char DefConnectLayMet, int (*func)(NLAYER *from, NLAYER *to)) {
    bool manytosome;
    MaxFOfMainLay > MaxFOfEndLay ? manytosome = true : manytosome = false;
    if (manytosome) return _UseManyToOneConnect(vectorcompass, MaxFOfMainLay, MaxFOfEndLay, DefConnectLayMet, func);
    else return _UseOneToManyConnect(vectorcompass, MaxFOfEndLay, MaxFOfMainLay, DefConnectLayMet, func);
}

/*
Функция похожа на избыточную, но иногда может пригодиться, возвращает последний подключенный слой
со смещением по вектору vectorcompass
параметры:
mainlay-основной слой от которого отталкиваться
vectorcompass- направление в котором следует идти до конца и вернуть конечный слой(подробности в дефайнах)
 */
DLL_EXPORT NLAYER *_GetDeeperLayer(NLAYER *mainlay, char vectorcompass) {
    NLAYER *templay = mainlay;
    if (mainlay) {
        switch (vectorcompass) {
        case COMPAS_ENDDOWN: {
            while (templay->down) {
                templay = templay->down;
            }
            break;
        }
        case COMPAS_ENDRIGHT: {
            while (templay->next) {
                templay = templay->next;
            }
            break;
        }
        case COMPAS_ENDUP: {
            while (templay->up) {
                templay = templay->up;
            }
            break;
        }
        case COMPAS_ENDLEFT: {
            while (templay->prev) {
                templay = templay->prev;
            }
            break;
        }
        default: {
            while (templay->down) {
                templay = templay->down;
            }
            break;
        }
        }
        return templay;
    } else return NULL;
}

//==================================Работа ведется выше...покачто....

NLAYER *_SimpleMethod(NLAYER *from, int count, int countend, char compas) {
    int countstop = count;
    int retval = 0;
    NLAYER *curlay = from, *nextlay = 0;
    while (countend > countstop) {
        if (countstop % 2 == 0) {
            countstop = countstop / 2;
            nextlay = _CreateLayerWNeuroCount(countstop, 0);
            retval = _ConnectLayer(curlay, nextlay, 6, NULL);
            if (retval)retval = retval; //Ошибко
        } else {
            countstop = countstop - 1;
            nextlay = _CreateLayerWNeuroCount(countstop - 1, 0);
            retval = _ConnectLayer(curlay, nextlay, 5, NULL);
            if (retval)retval = retval; //Ошибко
        }
        switch (compas) {
        case COMPAS_ENDDOWN: {
            curlay->down = nextlay;
            break;
        }
        case COMPAS_ENDRIGHT: {
            curlay->next = nextlay;
            break;
        }
        case COMPAS_ENDUP: {
            curlay->up = nextlay;
            break;
        }
        case COMPAS_ENDLEFT: {
            curlay->prev = nextlay;
            break;
        }
        }
        curlay = nextlay;
    }
    return curlay;
}

//Забыл уже что это.... уж не глаз ли я описал... тот самый.... аш стремновато что то....

NLAYER *_EveMethod(NLAYER *from, int count, int countend, char compas) {
    int countstop = count;
    int retval = 0;
    NLAYER *curlay = from, *nextlay = 0;
    while (countend > countstop) {
        if (countstop % 2 == 0) {
            countstop = countstop / 2;
            nextlay = _CreateLayerWNeuroCount(countstop, 0);
            retval = _ConnectLayer(curlay, nextlay, 4, NULL);
            if (retval)retval = retval; //Ошибко
        } else {
            countstop = countstop - 1;
            nextlay = _CreateLayerWNeuroCount(countstop - 1, 0);
            retval = _ConnectLayer(curlay, nextlay, 4, NULL);
            if (retval)retval = retval; //Ошибко
        }
        switch (compas) {
        case COMPAS_ENDDOWN: {
            curlay->down = nextlay;
            break;
        }
        case COMPAS_ENDRIGHT: {
            curlay->next = nextlay;
            break;
        }
        case COMPAS_ENDUP: {
            curlay->up = nextlay;
            break;
        }
        case COMPAS_ENDLEFT: {
            curlay->prev = nextlay;
            break;
        }
        }
        curlay = nextlay;
    }
    return curlay;
}

NLAYER *_CreateNeuroCard(int incount, int outcount, int method, NLAYER *finish) {
    NLAYER *firstlay = 0, *endlay = 0;
    int nin = 0, nout = 0;
    if (incount < outcount)return 0;

    nin = incount;
    nout = outcount;
    firstlay = _CreateLayerWNeuroCount(nin, 0);

    switch (method) {
    case CARDMETHOD_SIMPLE: {
        endlay = _SimpleMethod(firstlay, nin, nout, COMPAS_ENDRIGHT);
        break;
    }
    case CARDMETHOD_GODEVE: {
        endlay = _EveMethod(firstlay, nin, nout, COMPAS_ENDDOWN);
        break;
    }
    }

    if (finish) {
        _MoveDataFromLayer(endlay, finish);
    }
    return firstlay;
}

Net::Net() {
    LinkFuncs = new LinksBase();
    NeuronFuncs = new NeuronsBase();
    LayerFuncs = new LayersBase();
}

Net::~Net() {
    delete LinkFuncs;
    delete NeuronFuncs;
    delete LayerFuncs;
}

NLAYER *Net::CreateFrameworkNet(char vectorcompass, int MaxFOfMainLay, int MaxFOfEndLay, char DefConnectLayMet, int (*func)(NLAYER *from, NLAYER *to)) {
    const wchar_t *descr = L"NLAYER *CreateFrameworkNet(char vectorcompass,int MaxFOfMainLay,int MaxFOfEndLay,char DefConnectLayMet,int (*func)(NLAYER *from, NLAYER *to))\r\n";
    NLAYER *retv = 0;
    retv = _CreateFrameworkNet(vectorcompass, MaxFOfMainLay, MaxFOfEndLay, DefConnectLayMet, func);
    if (log) {
        if (!retv)
            log->AddInfo(DI_LOG_LEVEL_ERROR, descr, L"vectorcompass:%d,MaxFOfMainLay:%d,MaxFOfEndLay:%d,DefConnectLayMet:%d,UserFunct:0x%X04,return:*void...", vectorcompass, MaxFOfMainLay, MaxFOfEndLay, DefConnectLayMet, func);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, descr, L"vectorcompass:%d,MaxFOfMainLay:%d,MaxFOfEndLay:%d,DefConnectLayMet:%d,UserFunct:0x%X04,return:0x%X04", vectorcompass, MaxFOfMainLay, MaxFOfEndLay, DefConnectLayMet, func, retv);
    }
    return retv;
}

NLAYER *Net::UseManyToOneConnect(char vectorcompass, int MaxFOfMainLay, int MaxFOfEndLay, char DefConnectLayMet, int (*func)(NLAYER *from, NLAYER *to)) {
    const wchar_t *descr = L"NLAYER *UseManyToOneConnect(char vectorcompass,int MaxFOfMainLay,int MaxFOfEndLay,char DefConnectLayMet,int (*func)(NLAYER *from, NLAYER *to))\r\n";
    NLAYER *retv = 0;
    retv = _UseManyToOneConnect(vectorcompass, MaxFOfMainLay, MaxFOfEndLay, DefConnectLayMet, func);
    if (log) {
        if (!retv)
            log->AddInfo(DI_LOG_LEVEL_ERROR, descr, L"vectorcompass:%d,MaxFOfMainLay:%d,MaxFOfEndLay:%d,DefConnectLayMet:%d,UserFunct:0x%X04,return:*void...", vectorcompass, MaxFOfMainLay, MaxFOfEndLay, DefConnectLayMet, func);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, descr, L"vectorcompass:%d,MaxFOfMainLay:%d,MaxFOfEndLay:%d,DefConnectLayMet:%d,UserFunct:0x%X04,return:0x%X04", vectorcompass, MaxFOfMainLay, MaxFOfEndLay, DefConnectLayMet, func, retv);
    }
    return retv;
}

NLAYER *Net::UseOneToManyConnect(char vectorcompass, int MaxFOfMainLay, int MaxFOfEndLay, char DefConnectLayMet, int (*func)(NLAYER *from, NLAYER *to)) {
    const wchar_t *descr = L"NLAYER *UseOneToManyConnect(char vectorcompass,int MaxFOfMainLay,int MaxFOfEndLay,char DefConnectLayMet,int (*func)(NLAYER *from, NLAYER *to))\r\n";
    NLAYER *retv = 0;
    retv = _UseOneToManyConnect(vectorcompass, MaxFOfMainLay, MaxFOfEndLay, DefConnectLayMet, func);
    if (log) {
        if (!retv)
            log->AddInfo(DI_LOG_LEVEL_ERROR, descr, L"vectorcompass:%d,MaxFOfMainLay:%d,MaxFOfEndLay:%d,DefConnectLayMet:%d,UserFunct:0x%X04,return:*void...", vectorcompass, MaxFOfMainLay, MaxFOfEndLay, DefConnectLayMet, func);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, descr, L"vectorcompass:%d,MaxFOfMainLay:%d,MaxFOfEndLay:%d,DefConnectLayMet:%d,UserFunct:0x%X04,return:0x%X04", vectorcompass, MaxFOfMainLay, MaxFOfEndLay, DefConnectLayMet, func, retv);
    }
    return retv;
}

NLAYER *Net::GetDeeperLayer(NLAYER *mainlay, char vectorcompass) {
    const wchar_t *descr = L"NLAYER *GetDeeperLayer(NLAYER *mainlay,char vectorcompass)\r\n";
    NLAYER *retv = 0;
    retv = _GetDeeperLayer(mainlay, vectorcompass);
    if (log) {
        if (!retv)
            log->AddInfo(DI_LOG_LEVEL_ERROR, descr, L"mainlay:0x%X03,vectorcompass:%d,return:*void...", mainlay, vectorcompass);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, descr, L"mainlay:0x%X03,vectorcompass:%d,return:0x%X04", mainlay, vectorcompass, retv);
    }
    return retv;
}
