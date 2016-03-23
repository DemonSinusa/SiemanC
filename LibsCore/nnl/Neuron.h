#ifndef NEURON_H
#define NEURON_H

#include "libexport.h"

//TODO

/*
 * +1.При создании нейрона выставлять шанс и обнулять счетчики задействованных связей
 * +2.При активировании сбрасывать счетчики
 * 3.Постараться сделать все правильно по возможности не используя потоки(в активации нейронов, но не злоёв)
 * !4.Сделать функцию возврата Антианалогичную функции активации
 * 5. Обдумать обстоятельства при которых одинокому нейрону следует разделиться и как все уравнять, если необходимо.
 */

typedef struct _neuron {
    ntype val, retval; //Конкретные значения нейрона активированное\возвращаемое
    char state, chance; //Флаг статуса готов\не готов,Шанс при котором выстреливать
    LINKL *in, *out; //Указатели на входящий и исходящие списки связи
    short incount, outcount; //Счетчики количества связей вход/исход
    short incount_excited, outcount_excited; //Счетчики задействованных синапсов/аксонов
    void *Layer; //Указатель на слой к которому принадлежит нейрон
    void (*ActivateFunc)(struct _neuron *neuron, LINKL *in, LINKL *out); //Функция активации
    void (*ReturnFunc)(struct _neuron *neuron, LINKL *in, LINKL *out); //Функция возврата
    int postost; //Остаток разделенного импульса
    long IDOffset; //Смещение в файле -1 если не сохранялся или находиться в оперативе
    struct _neuron *prev, *next;
} NEURON;

typedef struct _cb_thread { //CallBackThread winapi
    void *ThreadH; //Хендл потока
    unsigned long ThreadId, ThreadTime; //ID и Аптайм потока
    char shance; //Не используется но работает и сейвится.
    NEURON *neuron;
    void *listpointer; //Переменная хранит в себе указатель на ячейку списка FIDL_THREADS
} CBT;

class DLL_EXPORT NeuronsBase {
public:

    NeuronsBase();
    NeuronsBase(LogSystem *logs);
    ~NeuronsBase();

    //---------------------------------------

    void SimulateComa();
    void OutOfComa();

    CBT *NewCBT(NEURON *n);
    void FreeCBT(CBT *cbt);
    //-----------------------------------------


    void SetDefaultFunctions(NEURON *n);
    NEURON *CreateNeuron(ntype val);
    NEURON *FreeNeuron(NEURON *n);
    int DeleteNeuron(NEURON *n);
    int AddNeuronToList(NEURON *it, NEURON *listitem); //Функция добавляет нейрон к списку после элемента listitem
    LINK *ConnectNeuron(NEURON *from, NEURON *to, ntype weight);
    LINK *GetConnection(NEURON *from, NEURON *to);
    NEURON *GetNeuronByConnectIndex(NEURON *from, int index, bool InLink);
    NEURON *GetNeuronByConnectWeight(NEURON *from, ntype index, bool InLink);
    int ActivateNeuron(NEURON *n);
    int DeleteNeuroList(NEURON *first);

private:
    bool ThreadFlag;
    LogSystem *log;
};

#ifdef __cplusplus
extern "C" {
#endif
    //---------------------------------------

    DLL_EXPORT void _ZalipNULL();
    DLL_EXPORT void _NeZaliPay();

    DLL_EXPORT CBT *_NewCBT(NEURON *n);
    DLL_EXPORT void _FreeCBT(CBT *cbt);
    //-----------------------------------------

    DLL_EXPORT void _SetDefaultFunctions(NEURON *n);
    DLL_EXPORT NEURON *_CreateNeuron(ntype val);
    DLL_EXPORT NEURON *_FreeNeuron(NEURON *n);
    DLL_EXPORT int _DeleteNeuron(NEURON *n);
    DLL_EXPORT int _AddNeuronToList(NEURON *it, NEURON *listitem); //Функция добавляет нейрон к списку после элемента listitem
    DLL_EXPORT LINK *_ConnectNeuron(NEURON *from, NEURON *to, ntype weight);
    DLL_EXPORT LINK *_GetConnection(NEURON *from, NEURON *to);
    DLL_EXPORT NEURON *_GetNeuronByConnectIndex(NEURON *from, int index, bool InLink);
    DLL_EXPORT NEURON *_GetNeuronByConnectWeight(NEURON *from, ntype index, bool InLink);
    DLL_EXPORT int _ActivateNeuron(NEURON *n);
    DLL_EXPORT int _DeleteNeuroList(NEURON *first);

#ifdef __cplusplus
}
#endif

#endif