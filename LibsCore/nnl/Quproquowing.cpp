/*
 * File:   Quproquowing.cpp(SlnguaG("BreakingBad",->Banqbitch Siemens BananA<^v)->o== "МарачончкЪ")
 * Author: iceritual
 *
 * Created on 8 июля 2015 г., 15:13
 */

#ifdef NEURO_LIB_WTHREAD        //Как оказалось, потоки ниразу не ускоряют работу
// А только лишь вызывают сложности с взаимообменом, я не верил, что можно обойтись без них
//При попытке это доказать- поверил.
#include <windows.h> //Нужна для нейронных потоков в winapi
#endif

/*
 * 1.Отладить сохранение связей в фэйлб, проследить полностью в отладке.
 */

#ifdef _WINANY
#include <io.h>
#else
#include <unistd.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <fcntl.h>
#include <errno.h>


#include "LogSystem.h"
#include "FreedomCase.h"

#include "DataFileTypes.h"
#include "States.h"
#include "Link.h"
#include "Neuron.h"
#include "Layer.h"
#include "LangPack.h"
#include "Utils.h"

#include "Quproquowing.h"

void *StubFNK(const char *fmt, ...) {
    return StubFNK(fmt, 1);
}

DLL_EXPORT void _CloseBlinkBasePart(BBNB *BB) {
    if (BB) {
        if (BB->threadfh)
            fclose(BB->threadfh);
        if (BB->fredoomeggsfh)
            fclose(BB->fredoomeggsfh);
        _wCrossUnlink(BB->threadFN);
        _wCrossUnlink(BB->fredoomeggsFN);
        BB->threadfh = NULL;
        BB->fredoomeggsfh = NULL;
    }
}

DLL_EXPORT void _CloseBaseBlock(BBNB *BB) {
    BBNB *BigBaseBlock = BB;

    if (BigBaseBlock->lst)_CloseLogFramework(BigBaseBlock->lst);

    if (BigBaseBlock->layerfh)
        fclose(BigBaseBlock->layerfh);
    if (BigBaseBlock->neurofh)
        fclose(BigBaseBlock->neurofh);
    if (BigBaseBlock->linkfh)
        fclose(BigBaseBlock->linkfh);
    _CloseBlinkBasePart(BigBaseBlock);

    free(BigBaseBlock->layerFN);
    free(BigBaseBlock->neuroFN);
    free(BigBaseBlock->linkFN);
}

FILE *_WFopenWNLoging(wchar_t *File, wchar_t *MainModes, LSD *log, wchar_t *ParentDescr) {
    FILE *fh = NULL;
    if (!File || !log || !MainModes)return NULL;
    wchar_t *descr = (wchar_t *)L"->FILE *_WOpenWNLoging(wchar_t *File, wchar_t *MainModes, LSD *log, wchar_t *ParentDescr)\r\n", *fdescr = descr;
    int fulldescrlen = ParentDescr ? wcslen(ParentDescr) + wcslen(descr) : wcslen(descr);

    descr = (wchar_t *)malloc((fulldescrlen + 1) * sizeof (wchar_t));
    wcscpy(descr, ParentDescr);
    wcscat(descr, fdescr);

    /*
     * Последовательность такая:
     * Сначала делаем то, для чего на самом деле предназначается функция.
     * Если не удалось, проверяем и пишем в лог почему
     * Если причина не критична, то делаем то,для чего предназначена функция, но с соотв. поправками.
     */

    if (!(fh = _wCrossFopen(File, MainModes))) {
        if (!_wCrossAccess(File, 3)) {
            if ((fh = _wCrossFopen(File, L"rb")))
                _AddNoRestructInfo(log, DI_LOG_LEVEL_WARNING, descr,
                                   LGPTAGS[LGP_FILENOTRW].LgpData, -2, File, LGPTAGS[LGP_LDT_DEFRN].LgpData, LGPTAGS[LGP_LDT_DEFRN].LgpData);
        } else {
            if (errno == EACCES) {
                _AddNoRestructInfo(log, DI_LOG_LEVEL_ERROR, descr,
                                   LGPTAGS[LGP_FILENOACCESS].LgpData, -1, File, LGPTAGS[LGP_LDT_DEFRN].LgpData, LGPTAGS[LGP_LDT_DEFRN].LgpData);
            } else {
                if (!(fh = _wCrossFopen(File, L"w+b")))
                    _AddNoRestructInfo(log, DI_LOG_LEVEL_ERROR, descr,
                                       LGPTAGS[LGP_FILENOALL].LgpData, -3, File, LGPTAGS[LGP_LDT_DEFRN].LgpData, LGPTAGS[LGP_LDT_DEFRN].LgpData);
            }
        }
    }
    free(descr);
    return fh;
}

DLL_EXPORT BBNB *_OpenBaseBlock(wchar_t *wpath, char UseLog) {
    const wchar_t *descr = L"int SaveLoadNLib::OpenBase(wchar_t *wpath)\r\n";
    BBNB *BigBaseBlock = NULL;
    wchar_t *wname = NULL, *LSDLogPath = NULL;
    bool breakflag = false;
    int fnamelen = 0, fullen = 0;

    if (!wpath)return NULL;
    int pathlen = wcslen(wpath);

    BigBaseBlock = (BBNB *) _MallocZeroBytes(sizeof (BBNB));
    if (!BigBaseBlock)return NULL;

    if (UseLog > 0) {
        wname = (wchar_t *)L"LogSysem.txt";
        fnamelen = wcslen(wname);
        fullen = pathlen + fnamelen + 3;
        LSDLogPath = (wchar_t *)malloc(fullen * sizeof (wchar_t));
        swprintf(LSDLogPath, fullen - 1, L"%ls%ls%ls", wpath, TRUE_SLASH, wname);
        BigBaseBlock->lst = _OpenLogFramework(UseLog, LSDLogPath);
        free(LSDLogPath);
    }
    //---------Делаем дела-------------
    wname = (wchar_t *)L"layers.dat";
    fnamelen = wcslen(wname);
    fullen = pathlen + fnamelen + 3;
    BigBaseBlock->layerFN = (wchar_t *)malloc(fullen * sizeof (wchar_t));
    swprintf(BigBaseBlock->layerFN, fullen - 1, L"%ls%ls%ls", wpath, TRUE_SLASH, wname);
    wname = (wchar_t *)L"neurons.dat";
    fnamelen = wcslen(wname);
    fullen = pathlen + fnamelen + 3;
    BigBaseBlock->neuroFN = (wchar_t *)malloc(fullen * sizeof (wchar_t));
    swprintf(BigBaseBlock->neuroFN, fullen - 1, L"%ls%ls%ls", wpath, TRUE_SLASH, wname);
    wname = (wchar_t *)L"links.dat";
    fnamelen = wcslen(wname);
    fullen = pathlen + fnamelen + 3;
    BigBaseBlock->linkFN = (wchar_t *)malloc(fullen * sizeof (wchar_t));
    swprintf(BigBaseBlock->linkFN, fullen - 1, L"%ls%ls%ls", wpath, TRUE_SLASH, wname);
    wname = (wchar_t *)L"threads.dat";
    fnamelen = wcslen(wname);
    fullen = pathlen + fnamelen + 3;
    BigBaseBlock->threadFN = (wchar_t *)malloc(fullen * sizeof (wchar_t));
    swprintf(BigBaseBlock->threadFN, fullen - 1, L"%ls%ls%ls", wpath, TRUE_SLASH, wname);
    wname = (wchar_t *)L"fredoom.case";
    fnamelen = wcslen(wname);
    fullen = pathlen + fnamelen + 3;
    BigBaseBlock->fredoomeggsFN = (wchar_t *)malloc(fullen * sizeof (wchar_t));
    swprintf(BigBaseBlock->fredoomeggsFN, fullen - 1, L"%ls%ls%ls", wpath, TRUE_SLASH, wname);

    if (!(BigBaseBlock->layerfh = _WFopenWNLoging(BigBaseBlock->layerFN, (wchar_t *)L"a+b", BigBaseBlock->lst, (wchar_t *)descr)))breakflag = true;
    if (!(BigBaseBlock->neurofh = _WFopenWNLoging(BigBaseBlock->neuroFN, (wchar_t *)L"a+b", BigBaseBlock->lst, (wchar_t *)descr)))breakflag = true;
    if (!(BigBaseBlock->linkfh = _WFopenWNLoging(BigBaseBlock->linkFN, (wchar_t *)L"a+b", BigBaseBlock->lst, (wchar_t *)descr)))breakflag = true;

    BigBaseBlock->threadfh = _WFopenWNLoging(BigBaseBlock->threadFN, (wchar_t *)L"wb", BigBaseBlock->lst, (wchar_t *)descr);
    BigBaseBlock->fredoomeggsfh = _WFopenWNLoging(BigBaseBlock->fredoomeggsFN, (wchar_t *)L"wb", BigBaseBlock->lst, (wchar_t *)descr);

    //----Самые крутые в своей крутезне!--------
    if (breakflag == true)_CloseBaseBlock(BigBaseBlock);

    return BigBaseBlock;
}

DLL_EXPORT long _AddLICXblk(BBNB *wco) {
    /*Резервирует кусок ОЗУ под ПЗУ блок
     * возвращает его смещение в файле
     */
    wchar_t *descr = (wchar_t *)L"AddLICXblk(BBNB *wco)";
    if (!wco)return -1;
    long linkOS = -1;
    FIDL *freelnk = _FindFDLByAnyParams(-1, FIDL_LINKS);
    if (freelnk) {
        linkOS = freelnk->data.FreedoomID;
        _DeleteFDL(freelnk);
    } else {
        fseek(wco->linkfh, 0, SEEK_END);
        linkOS = ftell(wco->linkfh);
        LICX *mem = (LICX *) malloc(sizeof (LICX));
        mem->around.inlist.listnext = mem->around.inlist.listprev = -1;
        mem->around.outlist.listnext = mem->around.outlist.listprev = -1;
        if (fwrite(mem, sizeof (LICX), 1, wco->linkfh) != 1) {
            if (wco->lst) {
                _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_ERROR, descr, LGPTAGS[LGP_FILENOACCESS].LgpData, 1, wco->linkFN, L"произведена попытка записи. ", L"Покидаем последовательность.");
            }
            linkOS = -1;
        }
        free(mem);
    }
    return linkOS;
}

DLL_EXPORT int _ShtampPointers(long linkOS, LAR *around, LINKL *lnk, BBNB *wco) {
    /*Расставляет указатели смещений относительно записаного блока
     * Резервирует блок данных при необходимости
     * отрицательный код -ошибка 0-успех
     */
    wchar_t *descr = (wchar_t *)L"ShtampPointers(long linkOS, LAR *around, LINKL *lnk, BBNB *wco)";
    if (!wco)return -1;
    if (linkOS == -1)return -2;
    if ((!around) || (!lnk))return -3;
    LINKL *from = (LINKL *) lnk->link->from, *to = (LINKL *) lnk->link->to, *temp = NULL;
    //    long mOS = linkOS + sizeof (LICX) - sizeof (LAR);
    temp = from->prev;
    while (temp && temp->state != STATE_READY)temp = temp->prev;
    if (temp) {
        if (temp->IDOffset != -1)
            around->inlist.listprev = temp->IDOffset;
        else {
            around->inlist.listprev = _AddLICXblk(wco);
        }
    } else around->inlist.listprev = -1;

    temp = from->next;
    while (temp && temp->state != STATE_READY)temp = temp->next;
    if (temp) {
        if (temp->IDOffset != -1)
            around->inlist.listnext = temp->IDOffset;
        else {
            around->inlist.listnext = _AddLICXblk(wco);
        }
    } else around->inlist.listnext = -1;

    temp = to->prev;
    while (temp && temp->state != STATE_READY)temp = temp->prev;
    if (temp) {
        if (temp->IDOffset != -1)
            around->outlist.listprev = temp->IDOffset;
        else {
            around->outlist.listprev = _AddLICXblk(wco);
        }
    } else around->outlist.listprev = -1;

    temp = to->next;
    while (temp && temp->state != STATE_READY)temp = to->next;
    if (temp) {
        if (temp->IDOffset != -1)
            around->outlist.listnext = temp->IDOffset;
        else {
            around->outlist.listnext = _AddLICXblk(wco);
        }
    } else around->outlist.listnext = -1;

    fseek(wco->linkfh, linkOS, SEEK_SET);
    if (fwrite(around, sizeof (LAR), 1, wco->linkfh) != 1) {
        if (wco->lst) {
            _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_ERROR, descr, LGPTAGS[LGP_FILENOACCESS].LgpData, 1, wco->linkFN, L"произведена попытка записи. ", L"Покидаем последовательность.");
        }
        return -4;
    } else return 0;
}

DLL_EXPORT int _TransmutateAndWriteLink(LINKL *cur, NEURON *carrier, BBNB *wco) {
    /*
     * Функция записывает выборочный блок связи, расставляет указатели смещений
     * возвращает NULL при успехе иначе код ошибки
     */
    wchar_t *descr = (wchar_t *)L"TransmutateAndWriteLink(LINKL *cur, NEURON *carrier, BBNB *wco)";
    if (!wco)return -1;
    if ((!cur) || (!carrier))return -2;
    LICX lnkmw;
    NEURON *temp = NULL;
    int retval = 0;

    _ConvertLINKtoLICX(cur->link, &lnkmw);
    if (((LINKL *) cur->link->from)->Neuron == carrier) {
        if (carrier->IDOffset != (-1))
            lnkmw.OSneurofrom = carrier->IDOffset;
        else {
            //Сюда попадаем при неверном условии сверху... или верном..
            //В зависимости от того что именно необходимо доказать
            carrier->IDOffset = lnkmw.OSneurofrom = _BuryOnceNeuron(carrier, wco->neurofh);
            if (carrier->IDOffset == (-1)) {
                if (wco->lst) {
                    _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_WARNING, descr, LGPTAGS[LGP_FILENOTRW].LgpData,
                                       3, wco->linkFN, L"произведена попытка записи прилежащего Нейрона. ", L"Раскошельтесь на ПЗУ пожалуйста..");
                }
                retval = -3;
            }
            temp = (NEURON *) ((LINKL *) cur->link->to)->Neuron;
            if (temp->IDOffset != (-1))
                lnkmw.OSneuroto = temp->IDOffset;
            else {
                temp->IDOffset = lnkmw.OSneuroto = _BuryOnceNeuron(temp, wco->neurofh);
                if (temp->IDOffset == (-1)) {
                    if (wco->lst) {
                        _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_WARNING, descr, LGPTAGS[LGP_FILENOTRW].LgpData,
                                           4, wco->linkFN, L"произведена попытка записи прилежащего Нейрона. ", L"Раскошельтесь пожалуйста на ПЗУ ещё...");
                    }
                    retval = -4;
                }
            }
        }
    } else {
        if (carrier->IDOffset != (-1))
            lnkmw.OSneuroto = carrier->IDOffset;
        else {
            //А это уже правильнее.. Как мне думается.
            //В зависимости от того что именно необходимо доказать
            carrier->IDOffset = lnkmw.OSneuroto = _BuryOnceNeuron(carrier, wco->neurofh);
            if (carrier->IDOffset == (-1)) {
                if (wco->lst) {
                    _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_WARNING, descr, LGPTAGS[LGP_FILENOTRW].LgpData,
                                       5, wco->linkFN, L"произведена попытка записи прилежащего Нейрона. ", L"Раскошельтесь на ПЗУ пожалуйста..");
                }
                retval = -5;
            }
            temp = (NEURON *) ((LINKL *) cur->link->from)->Neuron;
            if (temp->IDOffset != (-1))
                lnkmw.OSneurofrom = temp->IDOffset;
            else {
                temp->IDOffset = lnkmw.OSneurofrom = _BuryOnceNeuron(temp, wco->neurofh);
                if (temp->IDOffset == (-1)) {
                    if (wco->lst) {
                        _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_WARNING, descr, LGPTAGS[LGP_FILENOTRW].LgpData,
                                           6, wco->linkFN, L"произведена попытка записи прилежащего Нейрона. ", L"Раскошельтесь пожалуйста на ПЗУ ещё...");
                    }
                    retval = -6;
                }
            }
        }
    }

    if (cur->IDOffset == (-1)) {
        if ((cur->IDOffset = _AddLICXblk(wco)) == (-1)) {
            if (wco->lst) {
                _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_ERROR, descr, LGPTAGS[LGP_FILENOTRW].LgpData,
                                   7, wco->linkFN, L"произведена попытка записи частицы связей. ", L"Причина неуспешной записи по извесному смещению неизвесна...");
            }
            retval = -7;
        }

    }

    if ((retval = _BuryListBlock(wco->linkfh, cur->IDOffset, &lnkmw))) {
        if (wco->lst) {
            _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_ERROR, descr, LGPTAGS[LGP_FILENOTRW].LgpData,
                               retval * (-1), wco->linkFN, L"произведена попытка записи частицы связей. ", L"Причина неуспешной записи по извесному смещению неизвесна...");
        }
    }

    if ((retval = _ShtampPointers(cur->IDOffset, NULL, cur, wco))) {
        if (wco->lst) {
            _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_ERROR, descr, LGPTAGS[LGP_FILENOTRW].LgpData,
                               retval, wco->linkFN, L"произведена попытка записи указателей смещений. ", L"Причина неуспешной записи неизвесна...");
        }
    }

    return retval;
}

DLL_EXPORT int _TransmutateAndWriteLinks(LINKL *first, NEURON *carrier, BBNB *wco) {
    /*
     * Функция записывает весь список связей принадлежащий определенному Нейрону
     * возвращает NULL при успехе иначе код ошибки
     */
    wchar_t *descr = (wchar_t *)L"TransmutateAndWriteLinks(LINKL *first, NEURON *carrier, BBNB *wco)";
    if (!wco)return -1;
    if ((!first) || (!carrier))return -2;
    LINKL *temp = first;
    int retval = 0;
    while (temp) {
        if (!_TransmutateAndWriteLink(temp, carrier, wco))
            temp = temp->next;
    }
    return retval;
}

//Перед вызовом этой функции правильнее будет понимать,
//в какой последовательности и после каких действий её вызывать
//while(linkl){ ГДЕ-ТО_ЗДЕСЬ ;linkl=linkl->next;}

/*
DLL_EXPORT int _AtomizeLINKLfeatsLICX(LINKL *cur, BBNB *wco, LICX * cLINK) {
    wchar_t *descr = (wchar_t *)L"AtomizeLINKLfeatsLICX(LINKL *from, LINKL *to, BBNB *wco, LICX *cLINK)";
    if (!wco)return -1;
    if ((!cur))return -2;
    FIDL *avdrug = NULL;
    if (!cLINK)return -3;
    NEURON *holder = NULL;

    LINKL *from = (LINKL *) cur->link->from, *to = (LINKL *) cur->link->to;


    if (cur->state == STATE_READY) {
	cur->state = STATE_NOT_READY;

	if (cur->IDOffset == -1) {
	    if (!(avdrug = _FindFDLByAnyParams(-1, ONCEFIDL_LINKS))) {
		//Выполниться разок, самый первый вход..
		fseek(wco->linkfh, 0, SEEK_END);
		cur->IDOffset = _CreateFDL(ftell(wco->linkfh), ONCEFIDL_LINKS)->data.FreedoomID;
	    } else {
		cur->IDOffset = avdrug->data.FreedoomID + sizeof (LICX);
		_CreateFDL(cur->IDOffset, ONCEFIDL_LINKS);
	    }
	}

	if (from->state == STATE_READY) {
	    //Защита от операций, ВНЕЗАПНЫХ..
	    from->state = STATE_NOT_READY;
	    if (from->prev)
		cLINK->around.inlist.listprev = from->prev->IDOffset;
	    else cLINK->around.inlist.listprev = -1;

	    if (from->next) {
		if (from->next->IDOffset != (-1))
		    cLINK->around.inlist.listnext = from->next->IDOffset;
		else {
		    if (!(avdrug = _FindFDLByAnyParams(-1, ONCEFIDL_LINKS))) {
			//Выполниться ONCE
			fseek(wco->linkfh, 0, SEEK_END);
			cLINK->around.inlist.listnext = _CreateFDL(ftell(wco->linkfh), ONCEFIDL_LINKS)->data.FreedoomID;
		    } else {
			//Проход будет осуществляться по предидущим проделкам
			cLINK->around.inlist.listnext = avdrug->data.FreedoomID + sizeof (LICX);
			_CreateFDL(cLINK->around.inlist.listnext, ONCEFIDL_LINKS);
		    }
		}
	    } else cLINK->around.inlist.listnext = -1;

	    holder = (NEURON *) from->Neuron;
	    if (holder->IDOffset != -1)
		cLINK->OSneurofrom = holder->IDOffset;
	    else {
		//Сохранить одиночный нейрон ИНИИПЕТЬЪ!
		//Вызовется либо часто либо неочень но это очень неточно
		if (wco->lst) {
		    _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_WARNING, descr, LGPTAGS[LGP_DEFWARN].LgpData, 1, L"Инспектируемый объект не имеет неизвестного держателя. ", L"Собираем параметры.");
		}
		cLINK->OSneurofrom = _BuryOnceNeuron(holder, wco->neurofh);
	    }

	    from->state = STATE_READY;
	} else {
	    if (wco->lst) {
		_AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_ERROR, descr, LGPTAGS[LGP_DEFERROR].LgpData, 1, L"Объект в режиме не готов. ", L"Покидаем последовательность.");
	    }
	    cur->state = STATE_READY;
	    return -4;
	}

	if (to->state == STATE_READY) {
	    to->state = STATE_NOT_READY;
	    if (to->prev)
		cLINK->around.outlist.listprev = to->prev->IDOffset;
	    else cLINK->around.outlist.listprev = -1;

	    if (to->next) {
		if (to->next->IDOffset != -1)
		    cLINK->around.outlist.listnext = to->next->IDOffset;
		else {
		    if (!(avdrug = _FindFDLByAnyParams(-1, ONCEFIDL_LINKS))) {
			fseek(wco->linkfh, 0, SEEK_END);
			cLINK->around.outlist.listnext = _CreateFDL(ftell(wco->linkfh), ONCEFIDL_LINKS)->data.FreedoomID;
		    } else {
			cLINK->around.outlist.listnext = avdrug->data.FreedoomID + sizeof (LICX);
			_CreateFDL(cLINK->around.outlist.listnext, ONCEFIDL_LINKS);
		    }
		}
	    } else cLINK->around.outlist.listnext = -1;

	    holder = (NEURON *) to->Neuron;
	    if (holder->IDOffset != -1)
		cLINK->OSneuroto = holder->IDOffset;
	    else {
		//Сохранить одиночный нейрон ИНИИПЕТЬЪ!
		//Вызовется либо часто либо неочень но это очень неточно
		if (wco->lst) {
		    _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_WARNING, descr, LGPTAGS[LGP_DEFWARN].LgpData, 2, L"Инспектируемый объект не имеет неизвестного держателя. ", L"Собираем параметры.");
		}
		cLINK->OSneuroto = _BuryOnceNeuron(holder, wco->neurofh);
	    }

	    from->state = STATE_READY;
	} else {
	    if (wco->lst) {
		_AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_ERROR, descr, LGPTAGS[LGP_DEFERROR].LgpData, 2, L"Объект в режиме не готов. ", L"Покидаем последовательность.");
	    }
	    cur->state = STATE_READY;
	    return -5;
	}
	cur->state = STATE_READY;
    }
    //Тем самым можем вызвать нереально непреодолимые сложности у тех, кто не понимает,что творит
    //А копипастить нельзя, если чувствуешь, что получиться копипаста, то лучЦЪ перечувствовать
    return 0;
}

DLL_EXPORT int _DeAtomizeLINKLunLICX(LICX *XLINK, LINK * worklink) {
    //На 3 этапа
    //1:Проверка на входящие
    //2:Сделать что можем
    //3:Вернуть отчет
    if (!XLINK)return -1;
    if (!worklink)return -2;
    int reply = 0;

    _ConvertLICXtoLINK(XLINK, worklink);
    reply = 1;

    return reply;
}

DLL_EXPORT long _TransmutateAndWriteLList(LINKL *first, NEURON *carrier, BBNB * wco) {
    wchar_t *descr = (wchar_t *)L"TransmutateAndWriteLList(LINKL *first, NEURON *carrier, BBNB *wco)";
    if ((!wco) || (carrier))return -1;
    LINKL *listblk = first ? first : carrier->in ? carrier->in : carrier->out;
    LICX wrtblk;
    int errcode = 0;

    if (!listblk)return -1;

    while (listblk) {
	_ConvertLINKtoLICX(listblk->link, &wrtblk);
	if (!(errcode = _AtomizeLINKLfeatsLICX(listblk, wco, &wrtblk))) {
	    fseek(wco->linkfh, listblk->IDOffset, SEEK_SET);
	    fwrite(&wrtblk, sizeof (LICX), 1, wco->linkfh);
	} else {
	    if (wco->lst) {
		_AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_WARNING, descr, LGPTAGS[LGP_DEFWARN].LgpData, errcode, L"Это просто мало тренировок вспыльчивости", LGPTAGS[LGP_NOYES].LgpData);
	    }
	    break;
	}

	listblk = listblk->next;
    }
    _DeleteFDLListByType(ONCEFIDL_LINKS);

    return first->IDOffset;
}
 */
DLL_EXPORT int _AtomizeNEURONfeatsNC(NEURON *n, NLAYER *lay, NC * card, BBNB *wco) {
    wchar_t *descr = (wchar_t *)L"AtomizeNeuronfeatsNCARD(NEURON *n, NLAYER *lay, BBNB *wco, NC *card)";
    //Функция только правильно заполняет структуру NC без ее записи, но не без записи компонентов и держателя
    if (!wco)return -1;
    if ((!n) || (!lay))return -2;
    FIDL *avdrug = NULL;
    if (!card)return -3;

    //? Смотря как миксовать.. Можно lay при сохранялке проверять..

    if (!n->next) {
        if (wco->lst) {
            _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_ERROR, descr, LGPTAGS[LGP_DEFERROR].LgpData, 1, L"Объект в режиме не готов. ", L"Покидаем последовательность.");
        }
        return -5;
    }
    //Мы готовы все на местах
    /* ХЙКONЪqwasisusinass.
     * Ночью мне закралась в бошку МысЛъ..
     * А что если делать определение изменений по Кадастровой Важности
     * Принцип: сперва определять неизменные части, точнее те, что в большинстве своем не изменяются
     * Далее их структурировать до объема^nan
     * В завершении отделять среди них полиморфирующие частицы но не структурировать
     * т.к. это невозможно по определению, если полиморф настоящий
     * т.е. заряженный Динамическим а не статическим
     * Полиморфизмом.. Ага, ха, статический полиморфизм... кто только такой бред сочиняет...
     * Хотя статический полиморфизм полюбасу можно структурировать, он же никуда не измениться
     * потому разденется)
     * (Смена изображений в телевизорном корпусе- ||!|| корпус-ст.Полиморф, экран Д.Полиморф)
     *
     */

     //->Сегментирование!=~СегментоаншквОрь~~=Флегментироаность-^
    //->iDlsyuazikovoOQ~==Ээхъ("New _X("A4",lengvGLSDGdgoOШккь)-^<A<$(П~~=(цЦ))Уэ;

    if (n->prev) {
        if (n->prev->IDOffset != -1)
            card->neuronprev = n->prev->IDOffset;
        else {
            //Только при флегментированом использовании общего механизма.
            _BuryOnceNeuron(n->prev, wco->neurofh);
        }
    } else card->neuronprev = -1;


    if (n->IDOffset == -1) {
        if (!(avdrug = _FindFDLByAnyParams(-1, ONCEFIDL_NEURONS))) {
            //Выполниться разок, самый первый вход..
            fseek(wco->neurofh, 0, SEEK_END);
            n->IDOffset = _CreateFDL(ftell(wco->neurofh), ONCEFIDL_NEURONS)->data.FreedoomID;
        } else {
            n->IDOffset = avdrug->data.FreedoomID + sizeof (NC);
            _CreateFDL(n->IDOffset, ONCEFIDL_NEURONS);
        }
    }

    if (n->next) {
        if (n->next->IDOffset != -1)
            card->neuronnext = n->next->IDOffset;
        else {
            if (!(avdrug = _FindFDLByAnyParams(-1, ONCEFIDL_NEURONS))) {
                //Выполниться разок, самый первый ненаход..
                fseek(wco->neurofh, 0, SEEK_END);
                n->next->IDOffset = card->neuronnext = _CreateFDL(ftell(wco->neurofh) + sizeof (NC), ONCEFIDL_NEURONS)->data.FreedoomID;
            } else {
                n->next->IDOffset = card->neuronnext = avdrug->data.FreedoomID + sizeof (NC);
                _CreateFDL(card->neuronnext, ONCEFIDL_NEURONS);
            }
        }
    } else card->neuronnext = -1;

    //Кончаем с расстановкой мест.


    return 0;
}

DLL_EXPORT long _TransmutateAndWriteNeurons(NEURON *first, NEURON *end, NLAYER *lay, BBNB * wco) {
    wchar_t *descr = (wchar_t *)L"BuryNeurons(NEURON *first, NEURON *end, NLAYER *lay,BBNB *wco)";
    if (!wco)return -1;
    NC neurocard;

    NEURON *temp = first ? first : (!lay) ? NULL : lay->first;
    int errcode = 0;

    if (!temp) return -1;

    while (temp) {
        //Тут может быть ваша реклама либо сейвинг указателей...
        //Кажется, хорошее место для записи указателей..
        _ConvertInfoToNeuronCard(temp, &neurocard);

        //#warning L"Это может вызвать проблемы с головой и ее кружением..."
        //	if (temp->in)neurocard.LListin = _TransmutateAndWriteLList(temp->in, temp, wco);
        //	if (temp->out)neurocard.LListout = _TransmutateAndWriteLList(temp->out, temp, wco);
        //#warning L"Если это произойдет, немедленно сделать что-то.."


        if (!(errcode = _AtomizeNEURONfeatsNC(temp, lay ? lay : (NLAYER *) temp->Layer, &neurocard, wco))) {
            fseek(wco->neurofh, temp->IDOffset, SEEK_SET);
            fwrite(&neurocard, sizeof (NC), 1, wco->neurofh);
        } else {
            if (wco->lst) {
                _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_WARNING, descr, LGPTAGS[LGP_DEFWARN].LgpData, errcode, L"Это просто мало тренировок усидчивости", LGPTAGS[LGP_NOYES].LgpData);
            }
            break;
        }

        if (temp->in) {
            _TransmutateAndWriteLinks(temp->in, temp, wco);
            neurocard.LListin = temp->in->IDOffset;
        }
        if (temp->out) {
            _TransmutateAndWriteLinks(temp->out, temp, wco);
            neurocard.LListin = temp->in->IDOffset;
        }
        //Придумать как не заниматься множественым перетиранием..
        /*
         * 1.Определить в куда сейвим
         * 2.Если пересохраняем то позаботиться о последующем если он новый: иначе узнать откуда сейв начать..
         * 3.Определиться с последующим сохраняемым, либо взять из его ID либо из БазыСвободных либо в конец
         * 4.Сохранить блок по правильному
         */

        temp = temp->next;
    }

    _DeleteFDLListByType(ONCEFIDL_NEURONS);


    return first ? first->IDOffset : (!lay) ? -1 : lay->first->IDOffset;
}

DLL_EXPORT long _SaveLayerWONeurons(NLAYER *lay, LayAround *quadro, BBNB * wco) {
    //    wchar_t *descr = (wchar_t *)L"SaveLayerWONeurons( NLAYER *lay, LayAround *quadro, BBNB *wco)";
    if ((!wco) || (!lay))return -1;
    NLAYER *it = lay;
    LC lcard;

    if (it->IDOffset != (-1)) {
        fseek(wco->layerfh, it->IDOffset, SEEK_SET);
    } else {
        fseek(wco->layerfh, 0, SEEK_END);
        it->IDOffset = ftell(wco->layerfh);
    }

    _ConvertInfoToLCard(it, &lcard);

    if (quadro) {
        lcard.around.upcard = quadro->uplay;
        lcard.around.downcard = quadro->downlay;
        lcard.around.nextcard = quadro->nextlay;
        lcard.around.prevcard = quadro->prevlay;
        lcard.neurofirst = quadro->NeuroFirst;
    }

    _BuryLayerBlock(wco->layerfh, it->IDOffset, &lcard);

    return it->IDOffset;
}

DLL_EXPORT int _UpdatePointers(long Offset, LayAround *quadro, BBNB * wco) {
    if ((!quadro) || (!wco))return -1;
    if (Offset == (-1))return -2;
    //long OldOS=ftell(layerfh);

    LC LCard;

    fseek(wco->layerfh, Offset, SEEK_SET);
    if (fread(&LCard, sizeof (LC), 1, wco->layerfh) != 1)
        return -3;

    LCard.around.downcard = quadro->downlay;
    LCard.around.upcard = quadro->uplay;
    LCard.around.nextcard = quadro->nextlay;
    LCard.around.prevcard = quadro->prevlay;
    if (quadro->NeuroFirst != (-1))LCard.neurofirst = quadro->NeuroFirst;

    _BuryLayerBlock(wco->layerfh, Offset, &LCard);

    return 1;
}

DLL_EXPORT int _MultiSaveLayers(NLAYER *FromLAY, NLAYER *curlay, BBNB *wco, int deep) {
    wchar_t *descr = (wchar_t *)L"MultiSaveLayers(NLAYER *FromLAY, NLAYER *curlay, int deep)";
    if (!curlay)return -1;
    NLAYER *templay = curlay;
    if (deep >= 0) {
        LayAround la;
        _NullLayAround(&la);
        //memset(la,0,sizeof(LayAround));
        _SaveLayerWONeurons(templay, &la, wco);
        la.NeuroFirst = _TransmutateAndWriteNeurons(templay->first, templay->end, templay, wco);
        //	 = SaveNeuronsWOLists(templay);
        //	SaveConnectionsBlock(templay->first, templay->end);
        if (templay->up) {
            if (FromLAY) {
                if (templay->up != FromLAY) {
                    _MultiSaveLayers(templay, templay->up, wco, deep - 1);
                    la.uplay = templay->up->IDOffset;
                } else la.uplay = FromLAY->IDOffset;
            } else {
                _MultiSaveLayers(templay, templay->up, wco, deep - 1);
                la.uplay = templay->up->IDOffset;
            }
        }
        if (templay->down) {
            if (FromLAY) {
                if (templay->down != FromLAY) {
                    _MultiSaveLayers(templay, templay->down, wco, deep - 1);
                    la.downlay = templay->down->IDOffset;
                } else la.downlay = FromLAY->IDOffset;
            } else {
                _MultiSaveLayers(templay, templay->down, wco, deep - 1);
                la.downlay = templay->down->IDOffset;
            }
        }
        if (templay->next) {
            if (FromLAY) {
                if (templay->next != FromLAY) {
                    _MultiSaveLayers(templay, templay->next, wco, deep - 1);
                    la.nextlay = templay->next->IDOffset;
                } else la.nextlay = FromLAY->IDOffset;
            } else {
                _MultiSaveLayers(templay, templay->next, wco, deep - 1);
                la.nextlay = templay->next->IDOffset;
            }
        }
        if (templay->prev) {
            if (FromLAY) {
                if (templay->prev != FromLAY) {
                    _MultiSaveLayers(templay, templay->prev, wco, deep - 1);
                    la.prevlay = templay->prev->IDOffset;
                } else la.prevlay = FromLAY->IDOffset;
            } else {
                _MultiSaveLayers(templay, templay->prev, wco, deep - 1);
                la.prevlay = templay->prev->IDOffset;
            }
        }
        switch (_UpdatePointers(templay->IDOffset, &la, wco)) {
            if (wco->lst) {
            case -1: {
                _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_ERROR, descr, LGPTAGS[LGP_INFO].LgpData, 1,
                                   L"Функция обновления квадратных указателей вернула ошибку ", L" ,нЕчем..");
                break;
            }
            case -2: {
                _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_WARNING, descr, LGPTAGS[LGP_INFO].LgpData, 1,
                                   L"Функция обновления квадратных указателей вернула предупреждалку ", L" ,нЕкуда..");
                break;
            }
            case -3: {
                _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_ERROR, descr, LGPTAGS[LGP_INFO].LgpData, 2,
                                   L"Функция обновления квадратных указателей вернула предупреждалку ", L" ,нЕгде..");
                break;
            }
            default: {
                _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_INFO, descr, LGPTAGS[LGP_INFO].LgpData, 1,
                                   L"Функция обновления квадратных указателей вернула неопределенность ", L"делаем что нужно...");
            }
        }
        }
    }
    return 0;
}

DLL_EXPORT int _SaveNet(NLAYER *center, int deep, BBNB *wco) {
    wchar_t *descr = (wchar_t *)L"SaveNet(NLAYER *center, int deep, BBNB *wco)";
    int retval = 0;
    _ZalipNULL();
    if (!(retval = _WriteFreedomCase(wco))) {
        retval = _MultiSaveLayers(NULL, center, wco, deep);
    }
    _NeZaliPay();
    return retval;
}

DLL_EXPORT int _WriteFreedomCase(BBNB *wco) {
    /*
     * Функция записывает свободную кассу возвращает код ошибки?
     */
    wchar_t *descr = (wchar_t *)L"WriteFreedomCase(BBNB *wco)";
    if (!wco)return -1;
    FCBB freecb;
    BFIDL *temp = ultrastack;
    FIDL *tfidl = NULL;
    FILE *fh = NULL;
    long minusone = -1;
    int retval = 0;

    //Пишем на старые места в определенные файлы но имеем суперблок в отдельном файло
    //А то получиться сложно и неудобно... А еще признание, что я не знал заранее КАК..
    while (temp) {
        freecb.type = temp->type;
        switch (temp->type) {
        case FIDL_LAYERS: {
            fh = wco->linkfh;
            break;
        }
        case FIDL_NEURONS: {
            fh = wco->neurofh;
            break;
        }
        case FIDL_LINKS: {
            fh = wco->linkfh;
            break;
        }
        case FIDL_THREADS: {
            fh = wco->threadfh;
            break;
        }
        default: {
            temp = temp->next;
            continue;
        }
        }
        if ((tfidl = temp->r_fidl)) {
            freecb.entrypoint = temp->r_fidl->data.FreedoomID;
            do {
                fseek(fh, tfidl->data.FreedoomID, SEEK_SET);
                if (tfidl->next) {
                    fwrite(&tfidl->next->data.FreedoomID, sizeof (long), 1, fh);
                    freecb.itemscount++;
                } else {
                    fwrite(&minusone, sizeof (long), 1, fh);
                }
            } while ((tfidl = tfidl->next));
            freecb.itemscount++;
            if ((fwrite(&freecb, sizeof (FCBB), 1, wco->fredoomeggsfh)) != 1) {
                if (wco->lst) {

                    _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_ERROR, descr, LGPTAGS[LGP_FILENOTRW].LgpData, 1, wco->fredoomeggsFN, L"При попытке записи выяснилось:", L"Брякую");
                }
                retval = -1;
                break;
            }
        }
        temp = temp->next;
    }


    return retval;
}

DLL_EXPORT int _ReadFreedomCase(BBNB *wco) {
    /*
     * Функция читает свободную кассу возвращает код ошибки?
     */
    wchar_t *descr = (wchar_t *)L"ReadFreedomCase(BBNB *wco)";
    if (!wco)return -1;
    FCBB freecb;
    BFIDL *temp = ultrastack;
    FILE *fh = NULL;
    long neminusone = -1;
    int retval = 0;

    fseek(wco->fredoomeggsfh, 0, SEEK_SET);
    while (fread(&freecb, sizeof (FCBB), 1, wco->fredoomeggsfh) == 1) {
        switch (freecb.type) {
        case FIDL_LAYERS: {
            fh = wco->linkfh;
            break;
        }
        case FIDL_NEURONS: {
            fh = wco->neurofh;
            break;
        }
        case FIDL_LINKS: {
            fh = wco->linkfh;
            break;
        }
        case FIDL_THREADS: {
            fh = wco->threadfh;
            break;
        }
        default: {
            temp = temp->next;
            continue;
        }
        }
        if (freecb.entrypoint != (-1)) {
            neminusone = freecb.entrypoint;
            do {
                _CreateFDL(freecb.entrypoint, freecb.type);
                if (!fseek(fh, neminusone, SEEK_SET)) {
                    if (fread(&neminusone, sizeof (long), 1, fh) != 1) {
                        if (wco->lst) {
                            _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_ERROR, descr, LGPTAGS[LGP_FILENOTRW].LgpData, 1, wco->fredoomeggsFN, L"При попытке чтения выяснилось:", L"Брякую");
                        }
                        retval = -1;
                        break;
                    } else freecb.itemscount--;
                } else {
                    if (wco->lst) {
                        _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_ERROR, descr, LGPTAGS[LGP_FILENOTRW].LgpData, 2, wco->fredoomeggsFN, L"При попытке чтения выяснилось:", L"Брякую");
                    }
                    retval = -2;
                    break;
                }
            } while (neminusone != -1);
            freecb.itemscount--;
        }
    }
    return retval;
}

DLL_EXPORT NEURON * _UnBuryOnceNeuron(BBNB *wco, long NeuronFP, int *err) {
    wchar_t *descr = (wchar_t *)L"UnBuryOnceNeuron(BBNB *wco, long NeuronFP)";
    if ((NeuronFP == (-1)) || (!wco)) {
        if (err)*err = -1;
        return NULL;
    }
    //LayAround la;
    NC neurocard;
    NEURON * temp = 0;
    int err2 = 0;


    fseek(wco->neurofh, NeuronFP, SEEK_SET);
    if (fread(&neurocard, sizeof (NC), 1, wco->neurofh) != 1) {
        if (wco->lst) {
            _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_ERROR, descr, LGPTAGS[LGP_DEFERROR].LgpData, 1, L"Ошибка чтения ", L"просто мало тренировался");
        }
        if (err)*err = -2;
        return NULL;
    }

    if (neurocard.memorypoint) { //Получить адрес памяти загруженного нейрона
        temp = (NEURON *) neurocard.memorypoint;

        if (wco->lst) {
            _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_WARNING, descr, LGPTAGS[LGP_DEFWARN].LgpData, 1, L"Зачем пытаться раскопать раскопаное ", L"наверное что то не то с приоритетами выполнения.");
        }

        return temp;
    } else {
        //Иначе загрузить целиком нейрон

        if (wco->lst) {
            _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_INFO, descr, LGPTAGS[LGP_INFO].LgpData, 1, L"Начата процедура раскопок одиночного ядра,  ", L"делаем, раз нужно...");
        }

        temp = _CreateNeuron(neurocard.val);
        _ConvertInfoToNeuron(temp, &neurocard);
        temp->IDOffset = NeuronFP;
        temp->Layer = 0;
        //temp->incount=temp->outcount=0;


        //--------------------------
        _SetDefaultFunctions(temp);
        //--------------------------

        neurocard.memorypoint = temp;
        _BuryNeuronBlock(wco->neurofh, NeuronFP, &neurocard);

        //BugFix freedoom Neuron with link to freedoom neuron
        //Load them while not loaded all connected freedoom neurons
        if (neurocard.OSlayer == (-1)) {
            //LoadListsOfNeuron(neurocard.LListout,temp,false);
            if (wco->lst) {

                _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_INFO, descr, LGPTAGS[LGP_INFO].LgpData, 2, L"Это ядро-одиночка, не принадлежащее никакому слою ", L"делаем его королем (:) ");
            }
            _ReadAndUnTransmutateLinks(wco, -1, neurocard.LListout, temp, &err2);
            //	    _LoadListsOfNeuronXmode(wco, neurocard.LListout, temp, false);
        }

    }
    return temp;
}

DLL_EXPORT LINKL * _ReadAndUnTransmutateLinks(BBNB *wco, long in, long out, NEURON *carrier, int *err) {
    wchar_t *descr = (wchar_t *)L"ReadAndUnTransmutateLinks(BBNB *wco, long in,long out, NEURON *carrier, int *err) ";
    if ((!wco) || (!carrier))return NULL;
    long NextFP = in;
    LICX wrtblk;
    LINK * temp = NULL;
    int lcount = 0, err2 = 0;

    while (NextFP != -1) {
        fseek(wco->linkfh, NextFP, SEEK_SET);
        if (fread(&wrtblk, sizeof (LICX), 1, wco->linkfh) != 1) {
            if (wco->lst) {
                _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_ERROR, descr, LGPTAGS[LGP_DEFERROR].LgpData, 1, L"Проблема с чтением", L", что-то тут не так...");
            }
            if (err)*err = -2;
            break;
        }

        lcount++;

        if (wrtblk.memorypoint == 0) {
            temp = _ConnectNeuron(_UnBuryOnceNeuron(wco, wrtblk.OSneurofrom, &err2), carrier, wrtblk.weight);
            temp->activated = wrtblk.activated;
            wrtblk.memorypoint = temp;
        } else {
            //Второе попадание на одно соединение, делаем соответственно.
            if (wco->lst) {
                _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_INFO, descr, LGPTAGS[LGP_INFO].LgpData, 1, L"Второе попадание в связующее звено ", L"завершаем с ним работу.");
            }
            temp = (LINK *) wrtblk.memorypoint;
            wrtblk.memorypoint = 0;
        }

        if (temp) {
            _ConvertLICXtoLINK(&wrtblk, temp);
            ((LINKL *) temp->from)->IDOffset = ((LINKL *) temp->to)->IDOffset = NextFP;
        } else {
            if (wco->lst) {
                _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_ERROR, descr, LGPTAGS[LGP_DEFERROR].LgpData, 2, L"Проблема со слиянием", L" вероятно неудачно накоплиньъ...");
            }
            if (err)*err = -3;
            break;
        }

        if (!_BuryListBlock(wco->linkfh, NextFP, &wrtblk)) {
            NextFP = wrtblk.around.inlist.listnext;
        } else {
            if (wco->lst) {
                _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_ERROR, descr, LGPTAGS[LGP_DEFERROR].LgpData, 3, L"Проблема с записью данных нах потом?", L", что-то тут не так...");
            }
            if (err)*err = -4;
            break;
        }
    }
    carrier->incount = lcount;

    lcount = 0;
    NextFP = out;
    while (NextFP != (-1)) {

        fseek(wco->linkfh, NextFP, SEEK_SET);
        if (fread(&wrtblk, sizeof (LICX), 1, wco->linkfh) != 1) {
            if (wco->lst) {
                _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_ERROR, descr, LGPTAGS[LGP_DEFERROR].LgpData, 1, L"Проблема с чтением", L", что-то тут не так...");
            }
            if (err)*err = -2;
            break;
        }

        lcount++;

        if (wrtblk.memorypoint == 0) {
            temp = _ConnectNeuron(carrier, _UnBuryOnceNeuron(wco, wrtblk.OSneuroto, &err2), wrtblk.weight);
            temp->activated = wrtblk.activated;
            wrtblk.memorypoint = temp;

        } else {
            //Второе попадание на одно соединение, делаем соответственно.
            if (wco->lst) {
                _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_INFO, descr, LGPTAGS[LGP_INFO].LgpData, 1, L"Второе попадание в связующее звено ", L"завершаем с ним работу.");
            }
            temp = (LINK *) wrtblk.memorypoint;
            wrtblk.memorypoint = 0;
        }

        if (temp) {
            _ConvertLICXtoLINK(&wrtblk, temp);
            ((LINKL *) temp->from)->IDOffset = ((LINKL *) temp->to)->IDOffset = NextFP;
        } else {
            if (wco->lst) {
                _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_ERROR, descr, LGPTAGS[LGP_DEFERROR].LgpData, 2, L"Проблема со слиянием", L" вероятно неудачно накоплиньк...");
            }
            if (err)*err = -3;
            break;
        }

        if (!_BuryListBlock(wco->linkfh, NextFP, &wrtblk)) {
            NextFP = wrtblk.around.outlist.listnext;
        } else {
            if (wco->lst) {
                _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_ERROR, descr, LGPTAGS[LGP_DEFERROR].LgpData, 3, L"Проблема с записью данных над потом...", L", что-то тут не так..");
            }
            if (err)*err = -4;
            break;
        }
    }
    carrier->outcount = lcount;

    return carrier->in > carrier->out ? carrier->in : carrier->out;
}

DLL_EXPORT NEURON * _UnTransmutateAndReadNeurons(BBNB *wco, long NeuronFP, NLAYER * carrier, int *err) {
    wchar_t *descr = (wchar_t *)L"UnTransmutateAndReadNeurons(BBNB *wco, long NeuronFP, NLAYER *carrier)";
    if ((!wco) || (!carrier)) {
        if (err)*err = -1;
        return NULL;
    }
    if (NeuronFP == -1) {
        if (err)*err = -1;
        return NULL;
    }
    int err2 = 0;
    long NextFP = NeuronFP;
    NC ncard;
    NEURON * cur = NULL, *prev = NULL;

    while (NextFP != (-1)) {

        fseek(wco->neurofh, NextFP, SEEK_SET);
        if (fread(&ncard, sizeof (NC), 1, wco->neurofh) != 1) {
            if (wco->lst) {
                _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_ERROR, descr, LGPTAGS[LGP_DEFERROR].LgpData, 1, L"Проблема с чтением", L", что-то тут не так...");
            }
            if (err)*err = -2;
            break;
        }


        if (ncard.memorypoint) { //Получить адрес памяти загруженного нейрона
            cur = (NEURON *) ncard.memorypoint;
            if (!prev)carrier->first = cur;
            prev = cur;

            if (wco->lst) {
                _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_WARNING, descr, LGPTAGS[LGP_DEFWARN].LgpData, 1, L"Зачем пытаться раскопать раскопаное ", L"наверное что то не то с приоритетами выполнения.");
            }
            NextFP = ncard.neuronnext;
            continue;

        } else {
            //Иначе загрузить целиком нейрон

            if (wco->lst) {
                _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_INFO, descr, LGPTAGS[LGP_INFO].LgpData, 1, L"Начата процедура раскопок одиночного ядра,  ", L"делаем, раз нужно...");
            }



            if ((cur = _CreateNeuron(ncard.val)) != NULL) {
                //Не разрушаем последовательность
                if (!prev) {
                    carrier->first = cur;
                } else {
                    cur->prev = prev;
                    prev->next = cur;
                }
                prev = cur;

                _ConvertInfoToNeuron(cur, &ncard);
                cur->IDOffset = NeuronFP;
                cur->Layer = carrier;
                //temp->incount=temp->outcount=0;


                //--------------------------
                _SetDefaultFunctions(cur);
                //--------------------------

                ncard.memorypoint = cur;
                _BuryNeuronBlock(wco->neurofh, NeuronFP, &ncard);

                /*
                 * Необходимость была только при загрузке списка в виде постобработки для держателя.
                 * А теперь есть возможность обработки внутри цикла.. Это ниже.
                 * И теперь пофиг на принадлежность к злою)
                //BugFix freedoom Neuron with link to freedoom neuron
                //Load them while not loaded all connected freedoom neurons
                if (ncard.OSlayer == (-1)) {
                    //LoadListsOfNeuron(neurocard.LListout,temp,false);
                    if (wco->lst) {
                	_AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_INFO, descr, LGPTAGS[LGP_INFO].LgpData, 2, L"Это ядро-одиночка, не принадлежащее никакому слою ", L"делаем его королем (:) ");
                    }
                    _UnTransmutateAndReadLinks(wco, ncard.LListout, cur, false);
                    //	    _LoadListsOfNeuronXmode(wco, neurocard.LListout, temp, false);
                }
                 */
            } else {
                if (wco->lst) {
                    _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_WARNING, descr, LGPTAGS[LGP_DEFWARN].LgpData, 2, L"Недостаточно памяти", L"пожалуйста увеличте ОЗУ.");
                }

            }

        }

#warning L"Может вызвать проблемы с головой и ее кружением..."
        int knownicount = ncard.incount, knownocount = ncard.LListout;
        _ReadAndUnTransmutateLinks(wco, ncard.LListin, ncard.LListout, cur, &err2);
        if ((knownicount != cur->incount) || (knownocount != ncard.LListout)) {
            if (wco->lst) {
                _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_WARNING, descr, LGPTAGS[LGP_DEFWARN].LgpData, 3, L"А это проблема...", L"значения количества различны до и после.");
            }
        }
#warning L"При необходимости, что либо предпринять.."
        NextFP = ncard.neuronnext;
    }

    carrier->end = cur;

    return carrier->first;
}

DLL_EXPORT NLAYER * _LoadLayerWONeurons(BBNB *wco, long LayerID, LayAround * quadro, int *err) {
    wchar_t *descr = (wchar_t *)L"LoadLayerWONeurons(BBNB *wco,long LayerID, LayAround *quadro)";
    if (LayerID == (-1)) {
        if (err)*err = -1;
        return NULL;
    }
    NLAYER * curlay = 0;
    LC layc;
    fseek(wco->layerfh, LayerID, SEEK_SET);
    if (fread(&layc, sizeof (LC), 1, wco->layerfh) != 1) {
        if (err)*err = -2;
        if (wco->lst) {
            _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_ERROR, descr, LGPTAGS[LGP_DEFERROR].LgpData, 1, L"Проблема с чтением", L", что-то тут не так...");
        }
        return NULL;
    } else {
        if (quadro) {
            quadro->downlay = layc.around.downcard;
            quadro->uplay = layc.around.upcard;
            quadro->nextlay = layc.around.nextcard;
            quadro->prevlay = layc.around.prevcard;
            quadro->NeuroFirst = layc.neurofirst;
        }

        if (layc.memorypoint) {
            curlay = (NLAYER *) layc.memorypoint;
            return curlay;
        } else {
            if ((curlay = _CreateCenterLayer(0)) != NULL) {

                _ConvertInfoToLay(curlay, &layc);
                curlay->IDOffset = LayerID;
                layc.memorypoint = curlay;
                _BuryLayerBlock(wco->layerfh, LayerID, &layc);
            } else {
                if (err)*err = -3;
                if (wco->lst) {
                    _AddNoRestructInfo(wco->lst, DI_LOG_LEVEL_WARNING, descr, LGPTAGS[LGP_DEFWARN].LgpData, 1, L"Недостаточно памяти", L"пожалуйста увеличте ОЗУ.");
                }
            }
        }
    }
    return curlay;
}

DLL_EXPORT NLAYER * _MultiLoadLayers(BBNB *wco, NLAYER *FromLOS, long LayerOS, int deep, int *err) {
    wchar_t *descr = (wchar_t *)L"_MultiLoadLayers(BBNB *wco, NLAYER *FromLOS, long LayerOS, int deep)";
    if (LayerOS == -1) {
        if (err)*err = -1;
        return NULL;
    }
    NLAYER * templay = 0;
    if (deep >= 0) {
        LayAround la;
        _NullLayAround(&la);
        templay = _LoadLayerWONeurons(wco, LayerOS, &la, err);
        if (templay) {
            if (!templay->first) {
                _UnTransmutateAndReadNeurons(wco, la.NeuroFirst, templay, err);
                if (err)
                    if (*err != 0) {
                        *err = -2;
                        return NULL;
                    }
                //		LoadNeuronsWOLists(la.NeuroFirst, templay);
                //		LoadConnectionsBlock(templay->first, templay->end);
            } else return templay;

            if (la.uplay != (-1)) {
                if (FromLOS) {
                    if (la.uplay != FromLOS->IDOffset)
                        templay->up = _MultiLoadLayers(wco, templay, la.uplay, deep - 1, err);
                    else templay->up = FromLOS;
                } else {
                    templay->up = _MultiLoadLayers(wco, templay, la.uplay, deep - 1, err);
                }
            }
            if (la.downlay != (-1)) {
                if (FromLOS) {
                    if (la.downlay != FromLOS->IDOffset)
                        templay->down = _MultiLoadLayers(wco, templay, la.downlay, deep - 1, err);
                    else templay->down = FromLOS;
                } else {
                    templay->down = _MultiLoadLayers(wco, templay, la.downlay, deep - 1, err);
                }
            }
            if (la.nextlay != (-1)) {
                if (FromLOS) {
                    if (la.nextlay != FromLOS->IDOffset)
                        templay->next = _MultiLoadLayers(wco, templay, la.nextlay, deep - 1, err);
                    else templay->next = FromLOS;
                } else {
                    templay->next = _MultiLoadLayers(wco, templay, la.nextlay, deep - 1, err);
                }
            }
            if (la.prevlay != (-1)) {
                if (FromLOS) {
                    if (la.prevlay != FromLOS->IDOffset)
                        templay->prev = _MultiLoadLayers(wco, templay, la.prevlay, deep - 1, err);
                    else templay->prev = FromLOS;
                } else {
                    templay->prev = _MultiLoadLayers(wco, templay, la.prevlay, deep - 1, err);
                }
            }

        }
    }

    return templay;
}

DLL_EXPORT NLAYER *_LoadNet(BBNB *wco, int deep, int *err) {
    wchar_t *descr = (wchar_t *)L"LoadNet(BBNB *wco, int deep, int *err)";
    NLAYER *tlay = NULL;
    tlay = _MultiLoadLayers(wco, NULL, 0, deep, err);
    if (err)*err = _ReadFreedomCase(wco);
    return tlay;
}


//==================CLASS---------------------------------------

Quproquowing::Quproquowing() {
    BigBlock = new BBNB;
}

Quproquowing::Quproquowing(BBNB *GetdBB) {
    BigBlock = GetdBB;
}

Quproquowing::~Quproquowing() {
    delete BigBlock;
}

void Quproquowing::OpenBaseBlock(wchar_t *wpath, char UseLog) {
    BigBlock = _OpenBaseBlock(wpath, UseLog);
}

int Quproquowing::WriteFreedomCase() {
    return _WriteFreedomCase(BigBlock);
}

int Quproquowing::ReadFreedomCase() {
    return _ReadFreedomCase(BigBlock);
}

int Quproquowing::ShtampPointers(long linkOS, LAR *around, LINKL *lnk) {
    return _ShtampPointers(linkOS, around, lnk, BigBlock);
}

int Quproquowing::TransmutateAndWriteLink(LINKL *cur, NEURON *carrier) {
    return _TransmutateAndWriteLink(cur, carrier, BigBlock);
}

int Quproquowing::TransmutateAndWriteLinks(LINKL *first, NEURON *carrier) {
    return _TransmutateAndWriteLinks(first, carrier, BigBlock);
}

int Quproquowing::AtomizeNEURONfeatsNC(NEURON *n, NLAYER *lay, NC *card) {
    return _AtomizeNEURONfeatsNC(n, lay, card, BigBlock);
}

long Quproquowing::TransmutateAndWriteNeurons(NEURON *first, NEURON *end, NLAYER *lay) {
    return _TransmutateAndWriteNeurons(first, end, lay, BigBlock);
}

long Quproquowing::SaveLayerWONeurons(NLAYER *lay, LayAround *quadro) {
    return _SaveLayerWONeurons(lay, quadro, BigBlock);
}

int Quproquowing::UpdatePointers(long Offset, LayAround *quadro) {
    return _UpdatePointers(Offset, quadro, BigBlock);
}

int Quproquowing::MultiSaveLayers(NLAYER *FromLAY, NLAYER *curlay, int deep) {
    return _MultiSaveLayers(FromLAY, curlay, BigBlock, deep);
}

int Quproquowing::SaveNet(NLAYER *center, int deep) {
    return _SaveNet(center, deep, BigBlock);
}

LINKL *Quproquowing::ReadAndUnTransmutateLinks(long in, long out, NEURON *carrier, int *err) {
    return _ReadAndUnTransmutateLinks(BigBlock, in, out, carrier, err);
}

NEURON *Quproquowing::UnBuryOnceNeuron(long NeuronFP, int *err) {
    return _UnBuryOnceNeuron(BigBlock, NeuronFP, err);
}

NEURON *Quproquowing::UnTransmutateAndReadNeurons(long NeuronFP, NLAYER *carrier, int *err) {
    return _UnTransmutateAndReadNeurons(BigBlock, NeuronFP, carrier, err);
}

NLAYER *Quproquowing::LoadLayerWONeurons(long LayerID, LayAround *quadro, int *err) {
    return _LoadLayerWONeurons(BigBlock, LayerID, quadro, err);
}

NLAYER *Quproquowing::MultiLoadLayers(NLAYER *FromLOS, long LayerOS, int deep, int *err) {
    return _MultiLoadLayers(BigBlock, FromLOS, LayerOS, deep, err);
}

NLAYER *Quproquowing::LoadNet(int deep, int *err) {
    return _LoadNet(BigBlock, deep, err);
}

void Quproquowing::CloseBaseBlock() {
    _CloseBaseBlock(BigBlock);
}
