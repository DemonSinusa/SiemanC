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
#include "States.h"

DLL_EXPORT int _SetLinkWeight(LINK *it, ntype weight) { //Устанавливает вес связи

    it->weight = weight;

    return 0;
}

DLL_EXPORT LINK *_CreateLink(ntype weight) { //Создает связь

    LINK *created = (LINK *) _MallocZeroBytes(sizeof (LINK));
    if (!created)return 0;

    created->weight = weight;
    AddLincsCount(1);
    return created;
}

DLL_EXPORT void _FreeLink(LINK *it) { //Удаляет связь
    if (it)free(it);
    AddLincsCount(-1);
}

DLL_EXPORT LINK *_SetLinkToList(LINK *it, LINKL *from, LINKL *to) { //Функция связывает 2 элемента списка через элемент типа LINK
    if (!it)return 0;
    if (!from || !to)return 0;
    FIDL *tempfdl = _FindFDLByAnyParams(-1, FIDL_LINKS);
    it->from = from;
    it->to = to;
    from->link = it;
    to->link = it;
    if (tempfdl) {
	from->IDOffset = tempfdl->data.FreedoomID;
	to->IDOffset = tempfdl->data.FreedoomID;
	_DeleteFDL(tempfdl);
    }
    from->state = to->state = STATE_READY;
    return it;
}

DLL_EXPORT LINKL *_CreateLinkListItem(LINKL *prev) { //Функция создает новый элемент списка,или добавляет его после указанного
    LINKL *temp = (LINKL *) _MallocZeroBytes(sizeof (LINKL));
    if (!temp)return 0;

    temp->state = STATE_NOT_READY;

    temp->IDOffset = -1;
    if (prev) {
	temp->Neuron = prev->Neuron;
	prev->next = temp;
	temp->prev = prev;
    }
    AddLinclistsCount(1);
    return temp;
}

DLL_EXPORT LINKL *_FreeLinkListItem(LINKL *it) { //Функция удаляет выбранный элемент списка без проверок, возвращает предидущий иначе последующий элемент
    if (!it)return 0;
    LINKL *templ = 0;

    LINKL *prevl = it->prev;
    LINKL *nextl = it->next;
    if (it->state == STATE_READY)
	it->state = STATE_NOT_READY;
    else return templ;

    if (nextl) {
	templ = nextl;
	nextl->prev = prevl;
    }

    if (prevl) {
	templ = prevl;
	prevl->next = nextl;
    }
    free(it);
    AddLinclistsCount(-1);
    return templ;
}

DLL_EXPORT LINKL *_GetEndListItem(LINKL *first) { //Возвращает последний элемент в списке
    LINKL *temp = first;
    if (!temp)return 0;
    while (temp->next)temp = temp->next;
    return temp;
}

DLL_EXPORT int _DeleteLinkWList(LINK *it) { //Функция удаляет связь полностью, с проверками
    int retval = 0;
    NEURON *nfrom = 0, *nto = 0;
    LINKL *lfrom = (LINKL *) it->from, *lto = (LINKL *) it->to;
    if (!it)return 0;
    //Если есть it->from то должен быть и it->to и наоборот, иначе обязана быть ошибка.
    if (!it->from) {
	_FreeLink(it);
	return 0;
    }

    if (lfrom->IDOffset != -1 || lto->IDOffset != -1) {
	if (lfrom->IDOffset == lto->IDOffset) {
	    _CreateFDL(lfrom->IDOffset, FIDL_LINKS);
	} else {
	    //Если выполняется эта часть условия, то это ошибка сохранения (!Умну Дублинекатинг!)
	    _CreateFDL(lfrom->IDOffset, FIDL_LINKS);
	    _CreateFDL(lto->IDOffset, FIDL_LINKS);
	}
    }
    if (lfrom) {
	nfrom = (NEURON *) lfrom->Neuron;
	if (nfrom->out == lfrom)
	    nfrom->out = _FreeLinkListItem(lfrom);
	else _FreeLinkListItem(lfrom);

	retval += 1;
    }

    if (lto) {
	nto = (NEURON *) lto->Neuron;
	if (nto->in == lto)
	    nto->in = _FreeLinkListItem(lto);
	else _FreeLinkListItem(lto);

	if (!nto->in)_DeleteNeuron(nto);
	retval += 1;
    }

    _FreeLink(it);
    return retval;
}

DLL_EXPORT int _DeleteLinksList(LINKL *first) { //Полностью удаляет все связи,с проверкой, начинающиеся с first,возвращает кол-во действительно удаленных элементов
    LINKL *temp = first, *templ = 0;
    int retval = 0;

    if (!temp)return -1;

    while (temp) {
	templ = temp->next;
	if (_DeleteLinkWList(temp->link))
	    retval++;
	temp = templ;
    }
    return retval;
}

LinksBase::LinksBase() {
    log = NULL;
}

LinksBase::LinksBase(LogSystem *logs) {
    log = logs;
}

int LinksBase::SetLinkWeight(LINK *it, ntype weight) {
    const wchar_t *descr = L"int LinksBase::SetLinkWeight(LINK *it, ntype weight)\r\n";
    int rval = 0;
    rval = _SetLinkWeight(it, weight);
    if (log) {
	log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"weight:%x", weight);
    }
    return rval;
}

LINK *LinksBase::CreateLink(ntype weight) {
    const wchar_t *descr = L"LINK *LinksBase::CreateLink(ntype weight)\r\n";
    LINK *rval = 0;
    rval = _CreateLink(weight);
    if (log) {
	log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"weight:%x,return:0x%X02", weight, rval);
    }
    return rval;
}

void LinksBase::FreeLink(LINK *it) {
    const wchar_t *descr = L"void LinksBase::FreeLink(LINK *it)\r\n";
    if (log) {
	log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"LinkU:Freee\r\n");
    }
    _FreeLink(it);
}

LINK *LinksBase::SetLinkToList(LINK *it, LINKL *from, LINKL *to) {
    const wchar_t *descr = L"LINK *LinksBase::SetLinkToList(LINK *it, LINKL *from, LINKL *to)\r\n";
    LINK *rval = 0;
    rval = _SetLinkToList(it, from, to);
    if (log) {
	if (!rval)
	    log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"from:%x,to:%x,it:%x,return:Niht", from, to, it);
	else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"from:%x,to:%x,it:%x,return:%x", from, to, it, rval);
    }
    return rval;
}

LINKL *LinksBase::CreateLinkListItem(LINKL *prev) {
    const wchar_t *descr = L"LINKL *LinksBase::CreateLinkListItem(LINKL *prev)\r\n";
    LINKL *rval = 0;
    rval = _CreateLinkListItem(prev);
    if (log) {
	if (!rval)
	    log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"prev:%x,return:Net'\"", prev);
	else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"prev:%x,return:%x", prev, rval);
    }
    return rval;
}

LINKL *LinksBase::FreeLinkListItem(LINKL *it) {
    const wchar_t *descr = L"LINKL *LinksBase::FreeLinkListItem(LINKL *it)\r\n";
    LINKL *rval = 0;
    rval = _FreeLinkListItem(it);
    if (log) {
	if (!rval)
	    log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"it:%x,return:0", it);
	else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"it:0,return:%x", rval);
    }
    return rval;
}

LINKL *LinksBase::GetEndListItem(LINKL *first) {
    const wchar_t *descr = L"LINKL *LinksBase::GetEndListItem(LINKL *first)\r\n";
    LINKL *rval = 0;
    rval = _GetEndListItem(first);
    if (log) {
	if (!rval)
	    log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"first:%x,return:0", first);
	else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"first:%x,return:%x", first, rval);
    }
    return rval;
}

int LinksBase::DeleteLinkWList(LINK *it) {
    const wchar_t *descr = L"int LinksBase::DeleteLinkWList(LINK *it)\r\n";
    int rval = 0;
    rval = _DeleteLinkWList(it);
    if (log) {
	if (!rval)
	    log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"it:%x,return:0", it);
	else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"it:0,return:%d", rval);
    }
    return rval;
}

int LinksBase::DeleteLinksList(LINKL *first) {
    const wchar_t *descr = L"int LinksBase::DeleteLinksList(LINKL *first)\r\n";
    int rval = 0;
    rval = _DeleteLinksList(first);
    if (log) {
	if (!rval)
	    log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"first:%x,return:0", first);
	else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"first:0,return:%d", rval);
    }
    return rval;
}

