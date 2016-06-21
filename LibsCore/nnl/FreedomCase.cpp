/*
 * File:   FreedomCase.cpp
 * Author: iceritual
 *
 * Created on 6 июня 2015 г., 11:39
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "LogSystem.h"

#include "DataFileTypes.h"

#include "FreedomCase.h"

BFIDL *ultrastack = NULL;

FIDL *_NewFDL(BFIDL *parent) {
    FIDL *curdl = NULL;
    curdl = (FIDL *) _MallocZeroBytes(sizeof (FIDL));
    if (!curdl)return NULL;
    curdl->data.memberlfidl = curdl;
    curdl->memberbfidl = parent;
    return curdl;
}

DLL_EXPORT FIDL *_CreateFDL(long IDOffSet, char type) {
    //Добавление элемента IDOffSet в список принадлежащий type,
    //возвращает созданный элемент, иначе NULL
    FIDL *curid = NULL;
    BFIDL *temp = ultrastack;
    if (temp) {
        //Если в ультрастек что-то уже попадало, то
        while (temp && temp->type != type) {
            if (temp->type == type) break;

            if (!temp->next) {
                temp->next = (BFIDL *) _MallocZeroBytes(sizeof (BFIDL));
                if (!temp->next) {
                    temp = NULL;
                    break;
                }
                temp->next->prev = temp;
                temp->next->type = type;
            }
            temp = temp->next;
        }
    } else {
        //Если в ультрастек еще ничего не впихнуто, то
        temp = ultrastack = (BFIDL *) _MallocZeroBytes(sizeof (BFIDL));
        if (temp) {
            temp->type = type;
        }
    }

    if (!temp)return NULL;
    else {

        if (!(curid = _NewFDL(temp)))return NULL;

        if (temp->e_fidl) {
            //Просто добавить элемент к списку
            temp->e_fidl->next = curid;
            curid->prev = temp->e_fidl;
            temp->e_fidl = curid;
        } else {
            //Просто элемент является первым в списке
            temp->r_fidl = temp->e_fidl = curid;
        }
        curid->data.FreedoomID = IDOffSet;
    }

    return curid;
}

DLL_EXPORT FIDL *_DeleteFDL(FIDL *cur) {
    //Удаление элемента cur из списка со всеми протекающими
    //Возвращает последующий элемент данного списка, иначе предидущий.
    FIDL *temp = NULL;
    BFIDL *Bbase = NULL;
    if (!cur)return NULL;

    Bbase = (BFIDL *) cur->memberbfidl;

    if (cur->prev) {
        cur->prev->next = cur->next;
        temp = cur->prev;
    } else {
        if (Bbase->r_fidl == cur)Bbase->r_fidl = cur->next;
    }

    if (cur->next) {
        cur->next->prev = cur->prev;
        temp = cur->next;
    } else {
        if (Bbase->e_fidl == cur)Bbase->e_fidl = cur->prev;
    }

    free(cur);

    if (!Bbase->r_fidl) {
        if (Bbase->prev)Bbase->prev->next = Bbase->next;
        else ultrastack = Bbase->next;
        if (Bbase->next)Bbase->next->prev = Bbase->prev;

        free(Bbase);
    }

    return temp;
}

DLL_EXPORT FIDL *_FindFDLByAnyParams(long IDOffSet,signed char type) {
    //Поиск не строго определенного параметрами элемента в списке.
    //Если typе<0 то поиск осуществляется глобально.
    //Возвращает найденый элемент списка иначе NULL.
    BFIDL *temp = ultrastack;
    FIDL *ids = NULL;
    if (!temp)return NULL;
    if (type < 0) {
        if (IDOffSet != -1)
            while (temp) {
                ids = temp->e_fidl;
                while (ids && ids->data.FreedoomID != IDOffSet)ids = ids->prev;
                if (ids->data.FreedoomID == IDOffSet)break;
                temp = temp->next;
            }


    } else {
        while (temp && temp->type != type)temp = temp->next;

        if (temp) {
            ids = temp->e_fidl;
            if (IDOffSet != -1)
                while (ids && ids->data.FreedoomID != IDOffSet)ids = ids->prev;
        }
    }
    return ids;
}

DLL_EXPORT FIDL *_DeleteFDLByParm(long IDOffSet, char type) {
    //Удаление не строго определенного параметрами элемента в списке.
    //Возвращает последующий элемент данного списка, иначе предидущий.
    //Либо NULL если нечего возвращать

    return _DeleteFDL(_FindFDLByAnyParams(IDOffSet, type));

}

DLL_EXPORT BFIDL *_DeleteFDLList(BFIDL *cur) {
    //Удаление целого списка элементов по переданному указателю на спискодержателя.
    //Возвращает последующий элемент данного списка, иначе предидущий.
    BFIDL *temp = NULL;
    FIDL *ids = cur->e_fidl;
    if (cur->prev)temp = cur->prev;
    if (cur->next)temp = cur->next;

    while (ids)ids = _DeleteFDL(ids);
    return temp;
}

DLL_EXPORT BFIDL *_DeleteFDLListByType(char type) {
    //Удаление целого списка элементов по переданному в качестве параметра типу.
    //Возвращает последующий элемент данного списка, иначе предидущий
    //либо NULL если весь список пуст или не содержит данный тип.
    BFIDL *temp = ultrastack, *retv = NULL;
    FIDL *ids = NULL;
    while (temp && temp->type != type)temp = temp->next;

    if (temp) {
        if (temp->prev)retv = temp->prev;
        if (temp->next)retv = temp->next;
        ids = temp->e_fidl;
        while (ids)ids = _DeleteFDL(ids);
    }
    return retv;
}

FreedomCase::FreedomCase() {
    log = NULL;
}

FreedomCase::FreedomCase(LogSystem *logs) {
    log = logs;
}

FreedomCase::~FreedomCase() {
}

FIDL *FreedomCase::CreateFDL(long IDOffSet, char type) {
    const wchar_t *descr = L"FIDL *CreateFDL(long IDOffSet, char type)\r\n";
    FIDL *retv = 0;
    retv = _CreateFDL(IDOffSet, type);
    if (log) {
        if (!retv)
            log->AddInfo(DI_LOG_LEVEL_ERROR, descr, L"IDOffSet:%d,Type:%d,return:NULLI", IDOffSet, type);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"IDOffSet:%d,Type:%d,return:0x%X", IDOffSet, type, retv);
    }
    return retv;
}

FIDL *FreedomCase::DeleteFDL(FIDL *cur) {
    const wchar_t *descr = L"FIDL *DeleteFDL(FIDL *cur)\r\n";
    FIDL *retv = 0;
    retv = _DeleteFDL(cur);
    if (log) {
        if (!retv)
            log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"Container:0x%X,return:NULL", cur);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"Container:0x%X,return:0x%X", cur, retv);
    }
    return retv;
}

FIDL *FreedomCase::FindFDLByAnyParams(long IDOffSet, char type) {
    const wchar_t *descr = L"FIDL *FindFDLByAllParams(long IDOffSet, char type)\r\n";
    FIDL *retv = 0;
    retv = _FindFDLByAnyParams(IDOffSet, type);
    if (log) {
        if (!retv)
            log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"IDOffSet:%d,Type:%d,return:NULL", IDOffSet, type);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"IDOffSet:%d,Type:%d,return:0x%X", IDOffSet, type, retv);
    }
    return retv;
}

FIDL *FreedomCase::DeleteFDLByParm(long IDOffSet, char type) {
    const wchar_t *descr = L"FIDL *DeleteFDLByParm(long IDOffSet, char type)\r\n";
    FIDL *retv = 0;
    retv = _DeleteFDLByParm(IDOffSet, type);
    if (log) {
        if (!retv)
            log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"IDOffSet:%d,Type:%d,return:NULL", IDOffSet, type);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"IDOffSet:%d,Type:%d,return:0x%X", IDOffSet, type, retv);
    }
    return retv;
}

BFIDL *FreedomCase::DeleteFDLList(BFIDL *cur) {
    const wchar_t *descr = L"BFIDL *DeleteFDLList(BFIDL *cur)\r\n";
    BFIDL *retv = 0;
    retv = _DeleteFDLList(cur);
    if (log) {
        if (!retv)
            log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"Container:0x%X,return:NULL", cur);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"Container:0x%X,return:0x%X", cur, retv);
    }
    return retv;
}

BFIDL *FreedomCase::DeleteFDLListByType(char type) {
    const wchar_t *descr = L"BFIDL *DeleteFDLListByType(char type)\r\n";
    BFIDL *retv = 0;
    retv = _DeleteFDLListByType(type);
    if (log) {
        if (!retv)
            log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"Type:%d,return:NULL", type);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"Type:%d,return:0x%X", type, retv);
    }
    return retv;
}

FIDL *FreedomCase::NewFDL(BFIDL *parent) {
    const wchar_t *descr = L"FIDL *NewFDL(BFIDL *parent)\r\n";
    FIDL *retv = 0;
    retv = _NewFDL(parent);
    if (log) {
        if (!retv)
            log->AddInfo(DI_LOG_LEVEL_ERROR, descr, L"Parent:0x%X,return:NULLI", parent);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"Parent:0x%X,return:0x%X", parent, retv);
    }
    return retv;
}
