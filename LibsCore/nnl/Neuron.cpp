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


//Где то здесь закрался фич, что значение переданное
//в виде параметпра не полностью наполлняется смыслом.

//CBTL *CBTLroot = NULL, *CBTLend = NULL;
bool ThreadFlag = true;

//void RaspFunc(NEURON *neuron,LINKL *in,LINKL *out);

DLL_EXPORT void OptimiZActivateNeuronFunc(NEURON *n, LINKL *in, LINKL *out){
	LINKL *inlist = in, *outlist = out, *tlist = NULL,*curpozl=NULL;
    LINK *curlink = 0;
    NEURON *nto = 0;
    NLAYER *remlay = 0;
    ntype incurval = 0, devizor = 1;


    while(inlist){
		curlink=inlist->link;
		incurval+=curlink->weight/n->incount;

	curpozl=inlist->next;

	if(curlink->activated>0){
		curlink->activated=0;
		n->incount_excited--;
	}

		if(curlink->weight>=in->link->weight){
			tlist=_GetEndListItem(in);
			if(inlist->next)
				inlist->next->prev=inlist->prev;
			if(inlist->prev)
				inlist->prev->next=inlist->next;
			inlist->prev=tlist;
			tlist->next=inlist;
		}else{
			if(inlist->next)
				inlist->next->prev=inlist->prev;
			if(inlist->prev)
				inlist->prev->next=inlist->next;
			inlist->next=n->in;
			n->in=n->in->prev=inlist;
		}


		inlist=curpozl;
    }


    	if(n->val){
		n->val/2+incurval/2;	//Запопаламлин
	}else n->val=incurval;

	if (n->outcount>0 && n->incount > 0)
	devizor = (n->incount + 1) / n->outcount;	//Ва сколько будет изменяться вес каждой связи, ориг.поставщик n->val

	if(!outlist){			//Некуда дальше идти
		if (n->ReturnFunc) //И есть функция возврата
	    n->ReturnFunc(n, n->in, n->out);
	}else while(outlist){
		curlink = outlist->link;
	    nto = (NEURON *)((LINKL *)curlink->to)->Neuron;
	    if (curlink->activated == 0)nto->incount_excited++;
	    //-----Всем рассказать насколько Я крут
		//----------------Меняем флаг активных связей у нейрона последователя
	    curlink->weight = curlink->weight / 2 + (n->val * devizor) / 2;
	    //Даже связь выстрелевшего Нейрона остается что-то весить.. Или нет?
	    curlink->activated++;

	    //Рекуринама хорошанама
	    if ((nto->incount_excited / nto->incount * 100) >= nto->chance) {
	    		//Если шанс набрался...
		if (!nto->Layer) {
				//И слоя неть...
		    if (nto->ActivateFunc)
			nto->ActivateFunc(nto, nto->in, nto->out);
		} else {
				//И есть слой
		    remlay = (NLAYER *) nto->Layer;
		    remlay->neurocount_activ++; //Возбуждение как и шанс нарастает...
		    if (((remlay->neurocount_activ / remlay->neurocount * 100) >= remlay->chance)&&remlay->ActivateFunc)
			remlay->ActivateFunc(remlay, remlay->first, remlay->end);
		}
	    }

	    outlist=outlist->next;
	}

	/*
     * Хорошая идея- использовать эту библиотеку как карказ для сайта -соц сетей.
     * Кнопка-"рассказать" только создает указатель на олригинальный пост, без копирования текста,
     * И при изменении оригинала, все рассказанное,перерассказанное, оставленное без изменений
     * или и добавления коммента хватает оттуда
     * либо оригинал ссылается на втуда как апдейт принимать который за основной
     * или начать отстаивать свой пост решают разрабы и кул}{хацкерbl
     * а следят за этим все рассказавшие или перерассказавшие, если рассказавшие подтягиваются
     * в холиуэаринг и т.д. То есть решает когда и на что спустить всех собак в любом случае автор!!!
     * Но лучше эту идею не реализовывать, а то дело примет RGB-Abort from copylefter or copywronger...
     * Как у нас говориться -"За *** и уже там zabortwom.РФ"
     * А так же наполнить его всяким конътентом и прочим гуамном радилулзинга
     */

}

//Принцип-собрать по всем исходящим
//Найти оптимальное между своим и общим
//Раздать по входящим c флагom на возврат значения
//И запустить функцию возврата во входящем если шанс норм

DLL_EXPORT void OptimiZReturnNeuronFunc(NEURON *n, LINKL *in, LINKL *out){
	LINKL *inlist = in, *outlist = out;
    LINK *curlink = NULL;
    NEURON *nto = NULL, *nfrom = NULL;
    ntype outcurval = 0,delta=0;

    /*
    Это еще одна вариация.....
    1.Значение предидущего возврата заменять\СовмещатЬ с полученой частью.*
    Это даст ~статичный выхлоп для равных вхлопов после полной прогонки по набору из значений.
    ...Самооптимизация или тип того..Ответы и так были точны и интересны,
    а теперь еще с каждым запросом они становяться точнее без ущерба к ресурсоемкости.
    */

    while(outlist){
		    curlink = outlist->link;
			nto = (NEURON *) ((LINKL *) curlink->to)->Neuron;
			n->outcount_excited--;
			//Получаем размер шага, умножаем на количество таких шагов.
			outcurval+=(nto->retval/nto->in->link->weight)*(curlink->weight/nto->in->link->weight);
		    outlist=outlist->next;
    }

    if(n->retval)			//Бывалый Нейрон
    	n->retval = n->retval / 2 + outcurval / 2;		//*Стабилизатор
	else if(n->outcount>0)	//Не замыкающий, связаный Нейрон
		n->retval=outcurval;
	else n->retval=n->val;	//Замыкающий Нейрон


	while(inlist){
		curlink = inlist->link;
		nfrom = (NEURON *) ((LINKL *) curlink->from)->Neuron;
		nfrom->incount_excited++;
	//Если пора возвращать
	//Что это за натурально порн... Износилован за недодОдодачу...
	if (((nfrom->incount_excited / nfrom->incount * 100) >= nfrom->chance)&&nfrom->ReturnFunc)
			//И есть функция возврата
		nfrom->ReturnFunc(nfrom, nfrom->in, nfrom->out);

		inlist=inlist->next;
	}

}

/*
DLL_EXPORT void TrueReturnNeuronFunc(NEURON *n, LINKL *in, LINKL *out) {
    LINKL *inlist = in, *outlist = out;
    LINK *curlink = NULL;
    NEURON *nto = NULL, *nfrom = NULL;
    //    NLAYER *remlay=0;
    ntype outcurval = 0;
    //    int counter=n->incount+1;   //-----Считаем сам нейрон как входящую связь
    while (outlist) {
	curlink = outlist->link;
	nto = (NEURON *) ((LINKL *) curlink->to)->Neuron;
	n->outcount_excited--;
	outcurval += nto->retval / n->outcount;
	outlist = outlist->next;
    }

    if (n->retval)
	n->retval = n->retval / 2 + outcurval / 2;
    else if (n->outcount > 0)
	n->retval = outcurval;
    else n->retval = n->val;

    */
    /*
    Принцип распростронения.
    1.Найти минимальный = Ь
    2.Значение от возврата / Ь = Д и совмещение\замена на тот с чем.
    3.Пройти остальные меряя в Этот/Ь*Д...

    Это еще одна вариация.....
    1.Значение предидущего возврата заменять\совмещать с полученой частью.
    Это даст ~статичный выхлоп для равных вхлопов после полной прогонки по набору из значений.
    ...Самооптимизация или тип того..Ответы и так были точны и интересны,
    а теперь еще с каждым запросом они становяться точнее без ущерба к ресурсоемкости.
    */
/*
    while (inlist) {
	curlink = inlist->link;
	nfrom = (NEURON *) ((LINKL *) curlink->from)->Neuron;
	nfrom->incount_excited++;
	//Если пора возвращать
	//Что это за натурально порн... Износилован за недодОдодачу...
	if ((nfrom->incount_excited / nfrom->incount * 100) >= nfrom->chance) {
	    if (nfrom->ReturnFunc) //И есть функция возврата
		nfrom->ReturnFunc(nfrom, nfrom->in, nfrom->out);
	}
	inlist = inlist->next;
    }
}
*/
//Функция должна работать как надо,
//можно сказать, что это среднепсихологическая функция :)

DLL_EXPORT void DefActivateFunc(NEURON *neuron, LINKL *in, LINKL *out) {
    int linkcount = neuron->incount, linkcountout = neuron->outcount;
    int ost = 0;
    LINKL *inmode = in, *outmode = out;
    ntype weight = 0, halfweight = 0, temp = 0;
    while (inmode) {
	if (inmode->state == STATE_READY) {
	    inmode->link->weight = inmode->link->weight * inmode->link->activated / linkcount;
	    weight += inmode->link->weight;
	    inmode->link->activated = 0;
	}
	inmode = inmode->next;
    }

    if (!linkcountout)linkcountout = 1; //Раз больше некому, то мне
    if (!linkcount)linkcount = 1; //Раз больше негде то везде.

    halfweight = (neuron->val + weight) / linkcount; //Вес среднего распространения.
    if (neuron->val >= 0) //Значение нейрона всегда стремиться к 0
	neuron->val -= halfweight;
    else neuron->val += halfweight;

    temp = halfweight / linkcountout; //Мы делили апельсин,много нас а он 1
    ost = (int) (halfweight - linkcountout * temp); //Что осталось подберем
    neuron->postost += ost; //И к излишькам занесем
    while (outmode) { //Не нравиться мне это...
	if (outmode->state == STATE_READY) {
	    outmode->link->weight += temp;
	    outmode->link->activated++;
	}
	outmode = outmode->next;
    }

}

//Функцию разврата надо подправить, она должна изменять retval
//По нему находиться так сказать успешность действий
/*
DLL_EXPORT void DefReturnFunc(NEURON *neuron, LINKL *in, LINKL *out) {
    int linkcount = neuron->incount, linkcountout = neuron->outcount;
    int ost = 0;
    LINKL *inmode = in, *outmode = out;
    ntype weight = 0, halfweight = 0, temp = 0;

    while (outmode) {
	if (outmode->state == STATE_READY) {
	    outmode->link->weight = outmode->link->weight * outmode->link->activated / linkcountout;
	    weight += outmode->link->weight;
	}
	outmode = outmode->next;
    }

    if (!linkcountout)linkcountout = 1;
    if (!linkcount)linkcount = 1;

    halfweight = (neuron->retval + weight) / linkcountout; //Вес среднего распространения.
    if (neuron->retval >= 0) //Значение нейрона всегда стремиться к 0
	neuron->retval -= halfweight;
    else neuron->retval += halfweight;

    temp = halfweight / linkcount; //Мы раздали апельсины,много их а я 1...
    ost = (int) (halfweight - linkcount * temp); //Целиком ли могут влезть?
    neuron->postost -= ost; //Хотя,излишьки, тоже есть...

    while (inmode) { //Не нравиться мне это...
	if (inmode->state == STATE_READY) {
	    inmode->link->weight += temp;
	    inmode->link->activated++;
	}
	inmode = inmode->next;
    }
}
*/

//Нейрон активируется только после того как накопит заявленное количество активных сигналов

void TrueActivateNeuronT(void *cb) {
    CBT *cbt = (CBT *) cb;
    NEURON *n = cbt->neuron;
    if (n) {
	if (n->ActivateFunc)
	    n->ActivateFunc(n, n->in, n->out);
	if (!n->out) //И если некуда дальше идти,
	    if (n->ReturnFunc) //И есть функция возврата
		n->ReturnFunc(n, n->in, n->out);
    }

    _FreeCBT(cbt);
}

DLL_EXPORT void _ZalipNULL() {
    FIDL *temp = _FindFDLByAnyParams(-1, FIDL_THREADS);
    if (!temp)return;
    ThreadFlag = false;
    while (temp) {
#ifdef NEURO_LIB_WTHREAD
	temp->cbt->ThreadTime = SuspendThread(temp->cbt->ThreadH);
#endif
	temp = temp->prev;
    }

}

DLL_EXPORT void _NeZaliPay() {
    FIDL *temp = _FindFDLByAnyParams(-1, FIDL_THREADS);
    if (!temp)return;
    ThreadFlag = true;
    while (temp) {
#ifdef NEURO_LIB_WTHREAD
	temp->cbt->ThreadTime = ResumeThread(temp->cbt->ThreadH);
#else
	TrueActivateNeuronT((void *) temp->data.FreedoomID);
#endif
	temp = temp->prev;
    }
}

DLL_EXPORT CBT *_NewCBT(NEURON *n) {
    CBT *retval = NULL;
    if (!n)return NULL;
    if (ThreadFlag == false)return NULL;
    retval = (CBT *) _MallocZeroBytes(sizeof (CBT));
    if (retval) {
	retval->neuron = n;
	retval->listpointer = _CreateFDL((long) retval, FIDL_THREADS);
    }
    return retval;
}

DLL_EXPORT void _FreeCBT(CBT *cbt) {
    _DeleteFDL((FIDL *) cbt->listpointer);
    //    RemoveCBTFromList(cbt);
#ifdef NEURO_LIB_WTHREAD
    void *tr = cbt->ThreadH;
#endif

    free(cbt);

#ifdef NEURO_LIB_WTHREAD
    CloseHandle(tr);
#endif

}

DLL_EXPORT void _SetDefaultFunctions(NEURON *n) {
    n->ActivateFunc = OptimiZActivateNeuronFunc; //DefActivateFunc;
    n->ReturnFunc = OptimiZReturnNeuronFunc;
}

DLL_EXPORT NEURON *_CreateNeuron(ntype val) { //Создает нейрон в памяти и возвращает на него указатель
    NEURON *temp = (NEURON *) _MallocZeroBytes(sizeof (NEURON));
    if (!temp)return 0;
    FIDL *tempfdl = _FindFDLByAnyParams(-1, FIDL_NEURONS);


    temp->state = STATE_NOT_READY;

    temp->IDOffset = -1;
    if (tempfdl) {
	temp->IDOffset = tempfdl->data.FreedoomID;
	_DeleteFDL(tempfdl);
    }
    temp->val = val;
    temp->chance = 100;
    _SetDefaultFunctions(temp);
    //	temp->ActivateFunc=DefActivateFunc;
    //	temp->ReturnFunc=DefReturnFunc;

    temp->state = STATE_READY;

    AddNeuronsCount(1);

    return temp;
}

DLL_EXPORT NEURON *_FreeNeuron(NEURON *n) { //Функция удаляет выбранный элемент списка без проверок, возвращает предидущий иначе последующий элемент
    if (!n)return 0;

    NEURON *nnext = n->next, *nprev = n->prev, *ntemp = 0;

    if (n->state == STATE_READY)
	n->state = STATE_NOT_READY;
    else return 0;

    if (nnext) {
	ntemp = nnext;
	nnext->prev = nprev;
    }

    if (nprev) {
	ntemp = nprev;
	nprev->next = nnext;
    }

    if (n->IDOffset != -1) {
	_CreateFDL(n->IDOffset, FIDL_NEURONS);
    }

    AddNeuronsCount(-1);
    free(n);
    return ntemp;
}

DLL_EXPORT int _DeleteNeuron(NEURON *n) { //Функция удаляет нейрон полностью, с проверками,возвращает колличество разорванных связей.
    int retval = 0;
    if (!n)return -1;

    if (n->state == STATE_READY)
	n->state = STATE_NOT_READY;
    else return -2;

    NLAYER *nlay = (NLAYER *) n->Layer;
    //	NEURON *nnext=n->next,*nprev=n->prev;
    LINKL *lin = n->in, *lout = n->out;

    if (lin)retval += _DeleteLinksList(lin);
    if (lout)retval += _DeleteLinksList(lout);

    if (n == nlay->first) {
	if (nlay->first == nlay->end)
	    nlay->first = nlay->end = _FreeNeuron(n);
	else nlay->first = _FreeNeuron(n);
    } else if (n == nlay->end)
	nlay->end = _FreeNeuron(n);
    else _FreeNeuron(n);

    return retval;
}

DLL_EXPORT int _AddNeuronToList(NEURON *it, NEURON *listitem) { //Функция добавляет нейрон к списку после элемента listitem
    if (!it || !listitem)return -1;
    NEURON *next = listitem->next;
    if (next) {
	next->prev = it;
    }
    it->next = next;
    it->prev = listitem;
    listitem->next = it;
    it->Layer = listitem->Layer;

    return 0;
}

DLL_EXPORT int _DeleteNeuroList(NEURON *first) {
    if (!first)return -1;
    NEURON *temp = first, *curf = 0;
    do {
	curf = temp->next;
	_DeleteNeuron(temp);
    } while ((temp = curf));
    return 0;
}

DLL_EXPORT LINK *_ConnectNeuron(NEURON *from, NEURON *to, ntype weight) { //Соединяет 2 нейрона и возвращает элемент связи
    LINKL *lfrom, *lto;
    LINK *curlink;

    if (!from || !to)return 0;

    if (!(curlink = _CreateLink(weight)))return 0;
//_GetEndListItem
    if (!from->out) {
	from->out = lfrom = _CreateLinkListItem(NULL);
    } else lfrom = _CreateLinkListItem(from->out);
    if (!to->in) {
	to->in = lto = _CreateLinkListItem(NULL);
    } else lto = _CreateLinkListItem(to->in);

    lfrom->Neuron = from;
    lto->Neuron = to;

    from->outcount += 1;
    to->incount += 1;

    return _SetLinkToList(curlink, lfrom, lto);

}

DLL_EXPORT LINK *_GetConnection(NEURON *from, NEURON *to) {
    if (!from || !to)return 0;
    LINKL *lfrom = from->out, *lto = to->in;
    if (lfrom) {
	while (lfrom) {
	    if (lfrom->link->to == to)return lfrom->link;
	    lfrom = lfrom->next;
	}
    } else if (lto) {
	while (lto) {
	    if (lto->link->from == from)return lto->link;
	    lto = lto->prev;
	}
    } else return 0;
    return 0;
}

DLL_EXPORT NEURON *_GetNeuronByConnectIndex(NEURON *from, int index, bool InLink) {
    if (!from)return 0;
    LINKL *cur = 0;
    int count = 0;
    if (InLink)
	cur = from->in;
    else
	cur = from->out;
    if (cur) {
	do {
	    if (count == index) {
		if (InLink) {
		    return (NEURON *) ((LINKL *) cur->link->from)->Neuron;
		} else {
		    return (NEURON *) ((LINKL *) cur->link->to)->Neuron;
		}
	    }
	    count++;
	} while ((cur = cur->next));
    }
    return 0;
}

DLL_EXPORT NEURON *_GetNeuronByConnectWeight(NEURON *from, ntype index, bool InLink) {
    if (!from)return 0;
    LINKL *cur = 0;
    int count = 0;
    if (InLink)
	cur = from->in;
    else
	cur = from->out;
    if (cur) {
	do {
	    if (cur->link->weight == index) {
		if (InLink) {
		    return (NEURON *) ((LINKL *) cur->link->from)->Neuron;
		} else {
		    return (NEURON *) ((LINKL *) cur->link->to)->Neuron;
		}
	    }
	    count++;
	} while ((cur = cur->next));
    }
    return 0;
}

DLL_EXPORT void _DisConnectNeuron(NEURON *from, NEURON *to) {
    LINKL *listf = from->out;
    while (listf) {
	if (listf->state == STATE_READY)
	    if (listf->link->to == to) {
		_DeleteLinkWList(listf->link);
		from->outcount--;
		to->incount--;
		break;
	    }
	listf = listf->next;
    }

}

DLL_EXPORT int _ActivateNeuron(NEURON *n) { //Функция активации нейрона в отдельном потоке
    if (n) {
	CBT *act = _NewCBT(n);
	if (act) {
	    if (n->incount) { //|Не будем делить на 0... Пока что (:
		//Здесь формула рассчета, а пора ли на самом деле.
		if ((n->incount_excited / n->incount * 100) >= n->chance) //Нейрон готов к активации

#ifdef NEURO_LIB_WTHREAD
		    act->ThreadH = CreateThread(NULL, 0, ActivateNeuronT, act, 0, &act->ThreadId);
	    } else act->ThreadH = CreateThread(NULL, 0, ActivateNeuronT, act, 0, &act->ThreadId);
#else
		    TrueActivateNeuronT(act);
	    } else TrueActivateNeuronT(act); //Скорее всего стартовый слой(один из)
#endif


	} else return -1;
    } else return -2;
    return 0;
}


//-------------CLASS-----------------------

NeuronsBase::NeuronsBase() {

    /*    CBTLroot = NULL;
	CBTLend = NULL;
     */
    ThreadFlag = true;
    log = NULL;
}

NeuronsBase::NeuronsBase(LogSystem *logs) {
    //    CBTLroot = NULL;
    //    CBTLend = NULL;
    ThreadFlag = true;
    log = logs;
}

NeuronsBase::~NeuronsBase() {

}

void NeuronsBase::SimulateComa() {
    _ZalipNULL();
    if (log) {
	log->AddInfo(DI_LOG_LEVEL_INFO, L"SimulateComa");
    }
}

void NeuronsBase::OutOfComa() {
    _NeZaliPay();
    if (log) {
	log->AddInfo(DI_LOG_LEVEL_INFO, L"OutOfComa");
    }
}

CBT *NeuronsBase::NewCBT(NEURON *n) {
    return _NewCBT(n);
}

void NeuronsBase::FreeCBT(CBT *cbt) {
    _FreeCBT(cbt);
}
//-----------------------------------------

void NeuronsBase::SetDefaultFunctions(NEURON *n) {
    _SetDefaultFunctions(n);
}

NEURON *NeuronsBase::CreateNeuron(ntype val) {
    const wchar_t *descr = L"NEURON *NeuronsBase::CreateNeuron(ntype val)\r\n";
    NEURON *retv = 0;
    retv = _CreateNeuron(val);
    if (log) {
	if (!retv)
	    log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"val:%x,return:0x0", val);
	else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"val:%x,Return:0x%X02", val, retv);
    }
    return retv;
}

NEURON *NeuronsBase::FreeNeuron(NEURON *n) {
    const wchar_t *descr = L"NEURON *NeuronsBase::FreeNeuron(NEURON *n)\r\n";
    NEURON *retv = 0;
    retv = _FreeNeuron(n);
    if (log) {
	if (!retv)
	    log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"Neuron:0x%X02,return:0", n);
	else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"Neuron:0x0,return:0x%X02", retv);
    }
    return retv;
}

int NeuronsBase::DeleteNeuron(NEURON *n) {
    const wchar_t *descr = L"int NeuronsBase::DeleteNeuron(NEURON *n)\r\n";
    int retv = 0;
    retv = _DeleteNeuron(n);
    if (log) {
	if (!retv)
	    log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"Neuron:0x%X02,return:0", n);
	else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"Neuron:0x0,return:%d", retv);
    }
    return retv;
}

int NeuronsBase::AddNeuronToList(NEURON *it, NEURON *listitem) {
    const wchar_t *descr = L"int NeuronsBase::AddNeuronToList(NEURON *it, NEURON *listitem)\r\n";
    int retv = 0;
    retv = _AddNeuronToList(it, listitem);
    if (log) {
	if (retv)
	    log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"Neuron:0x%X02,NeuroList:0x%X02,return:%d", it, listitem, retv);
	else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"Neuron:0x%X02,NeuroList:0x%X02,return:0kау", it, listitem);
    }
    return retv;
}

LINK *NeuronsBase::ConnectNeuron(NEURON *from, NEURON *to, ntype weight) {
    const wchar_t *descr = L"LINK *NeuronsBase::ConnectNeuron(NEURON *from, NEURON *to, ntype weight)\r\n";
    LINK *retv = 0;
    retv = _ConnectNeuron(from, to, weight);
    if (log) {
	if (!retv)
	    log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"From:0x%X02,To:0x%X02,return:0", from, to);
	else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"From:0x%X02,To:0x%X02,return:%d", from, to, retv);
    }
    return retv;
}

LINK *NeuronsBase::GetConnection(NEURON *from, NEURON *to) {
    const wchar_t *descr = L"LINK *NeuronsBase::GetConnection(NEURON *from, NEURON *to)\r\n";
    LINK *retv = 0;
    retv = _GetConnection(from, to);
    if (log) {
	if (!retv)
	    log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"From:0x%X02,To:0x%X02,return:0x0", from, to);
	else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"From:0x%X02,To:0x%X02,return:0x%x", from, to, retv);
    }
    return retv;
}

NEURON *NeuronsBase::GetNeuronByConnectIndex(NEURON *from, int index, bool InLink) {
    const wchar_t *descr = L"NEURON *NeuronsBase::GetNeuronByConnectIndex(NEURON *from, int index, bool InLink)\r\n";
    NEURON *retv = 0;
    retv = _GetNeuronByConnectIndex(from, index, InLink);
    if (log) {
	if (!retv)
	    log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"From:0x%X02,index:%d,Return:0", from, index);
	else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"From:0x%X02,index:%d,Return:0x%X02", from, index, retv);
    }
    return retv;

}

NEURON *NeuronsBase::GetNeuronByConnectWeight(NEURON *from, ntype index, bool InLink) {
    const wchar_t *descr = L"NEURON *NeuronsBase::GetNeuronByConnectUWeS\"s(NEURON *from, ntype index, bool InLink)\r\n";
    NEURON *retv = 0;
    retv = _GetNeuronByConnectWeight(from, index, InLink);
    if (log) {
	if (!retv)
	    log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"From:0x%X02,weight:%x,Return:0", from, index);
	else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"From:0x%X02,weight:%x,Return:0x%X02", from, index, retv);
    }
    return retv;

}

int NeuronsBase::ActivateNeuron(NEURON *n) {
    const wchar_t *descr = L"int NeuronsBase::ActivateNeuron(NEURON *n)\r\n";
    int retv = 0;
    retv = _ActivateNeuron(n);
    if (log) {
	if (retv)
	    log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"!NEURON!:0x%X02,return:%d", n, retv);
	else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"!NEURON!:0x%X02,return:-0", n);
    }
    return retv;
}

int NeuronsBase::DeleteNeuroList(NEURON *first) {
    const wchar_t *descr = L"int NeuronsBase::DeleteNeuroList(NEURON *first)\r\n";
    int retv = 0;
    retv = _DeleteNeuroList(first);
    if (log) {
	if (!retv)
	    log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"First:0x%X02,return:+0", first);
	else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"First:0x%X02,return:%d", first, retv);
    }
    return retv;
}

