#ifdef NEURO_LIB_WTHREAD
#include <windows.h> //Нужна для нейронных потоков в winapi
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

DLL_EXPORT void _ActivateLayerFunc(NLAYER *lay, NEURON *first, NEURON *end) {
    NEURON *tempn = first, *tmove = end;
    while (tempn) {
        if (!tempn->incount) {
            lay->neurocount_activ--; //Возбуждение спадает
            _ActivateNeuron(tempn);
            tempn = tempn->next;
        } else if ((tempn->incount_excited / tempn->incount * 100) >= tempn->chance) {
            lay->neurocount_activ--; //Возбуждение спадает
            _ActivateNeuron(tempn);
            tempn = tempn->next;
        } else {
            tmove = tempn->next;
            //Переместить нейрон в начало списка tempn->next=lay->first
            if (tempn != lay->first) { //Имеет смысл только если он не первый
                if (tempn->prev)
                    tempn->prev->next = tempn->next;
                if (tempn->next)
                    tempn->next->prev = tempn->prev;
                tempn->next = lay->first;
                tempn->next->prev = tempn;
                lay->first = tempn;
            }
            tempn = tmove;
        }
    }
}

DLL_EXPORT void _SetLayerActivateChance(NLAYER *lay, char chance) {
    lay->chance = chance;
}

DLL_EXPORT NLAYER *_CreateCenterLayer(NEURON *first) {
    NLAYER *temp = (NLAYER *) _MallocZeroBytes(sizeof (NLAYER));
    NEURON *tempn = first;
    if (!temp)return 0;
    FIDL *tempfdl = _FindFDLByAnyParams(-1, FIDL_LAYERS);

    temp->state = STATE_NOT_READY;

    temp->IDOffset = -1;
    if (tempfdl) {
        temp->IDOffset = tempfdl->data.FreedoomID;
        _DeleteFDL(tempfdl);
    }
    //temp->neurocount=temp->neurocount_activ=0;
    temp->chance = 100;
    temp->ActivateFunc = _ActivateLayerFunc;
    temp->first = temp->end = tempn;
    if (tempn)
        do {
            temp->neurocount++;
            temp->end = tempn;
            tempn->Layer = temp;
            tempn = tempn->next;
        } while (tempn);

    temp->state = STATE_READY;

    AddLayersCount(1);

    return temp;
}

DLL_EXPORT NLAYER *_CreateLayerWNeuroCount(int count, ntype *memblock) {
    NLAYER *temp = 0;
    NEURON *tempn = 0, *templist = 0;
    ntype val = 0;
    int vcount = 0;
    if (memblock) {
        val = memblock[vcount];
        vcount++;
        templist = _CreateNeuron(val);
        while (vcount != count) {
            val = memblock[vcount];
            vcount++;
            tempn = _CreateNeuron(val);
            _AddNeuronToList(tempn, templist);
        }
    } else {
        val = 0;
        vcount++;
        templist = _CreateNeuron(val);
        while (vcount != count) {
            vcount++;
            tempn = _CreateNeuron(val);
            _AddNeuronToList(tempn, templist);
        }
    }
    temp = _CreateCenterLayer(templist);
    if (!temp) {
        _DeleteNeuroList(templist);
        return 0;
    } else return temp;
}

DLL_EXPORT int _AddUperLayer(NLAYER *uplay, NLAYER *center) {
    NLAYER *temp = center;
    if (!temp || !uplay)return -1;
    if (temp->up) {
        uplay->up = temp->up;
        uplay->down = temp;
        temp->up->down = uplay;
        temp->up = uplay;
    } else {
        uplay->down = temp;
        temp->up = uplay;
    }

    return 0;
}

DLL_EXPORT int _AddDownLayer(NLAYER *downlay, NLAYER *center) {
    NLAYER *temp = center;
    if (!temp || !downlay)return -1;
    if (temp->down) {
        downlay->down = temp->down;
        downlay->up = temp;
        temp->down->up = downlay;
        temp->down = downlay;
    } else {
        downlay->up = temp;
        temp->down = downlay;
    }

    return 0;
}

DLL_EXPORT int _AddPrevLayer(NLAYER *prevlay, NLAYER *center) {
    NLAYER *temp = center;
    if (!temp || !prevlay)return -1;
    if (temp->prev) {
        prevlay->prev = temp->prev;
        prevlay->next = temp;
        temp->prev->next = prevlay;
        temp->prev = prevlay;
    } else {
        prevlay->next = temp;
        temp->prev = prevlay;
    }

    return 0;
}

DLL_EXPORT int _AddNextLayer(NLAYER *nextlay, NLAYER *center) {
    NLAYER *temp = center;
    if (!temp || !nextlay)return -1;
    if (temp->next) {
        nextlay->next = temp->next;
        nextlay->prev = temp;
        temp->next->prev = nextlay;
        temp->next = nextlay;
    } else {
        nextlay->prev = temp;
        temp->next = nextlay;
    }

    return 0;
}

DLL_EXPORT int _AddNeuroListToLayer(NLAYER *lay, NEURON *first, NEURON *end) {
    int count = 0;
    NEURON *temp = first;
    NLAYER *oldlay = 0;
    if (!first || !end)return 0;
    oldlay = (NLAYER *) first->Layer;
    if (oldlay) {
        if (oldlay->first == first)
            oldlay->first = end->next;
        if (oldlay->end == end)
            oldlay->end = end->next;
    }
    if (first->prev) {
        first->prev->next = end;
        end->prev = first->prev;
    }
    if (lay->first) {
        lay->end->next = first;
        first->prev = lay->end;
        lay->end = first;
    } else {
        lay->first = lay->end = first;
    }
    while (temp != end->next) {
        temp->Layer = lay;
        lay->neurocount++;
        lay->end = temp;
        count++;
        temp = temp->next;
    }
    lay->end->next = 0;
    return count;
}

DLL_EXPORT NLAYER *_CreateHiLoLayer(NLAYER *down, NLAYER *up, NEURON *first) {
    NLAYER *temp = _CreateCenterLayer(first);
    if (!temp)return 0;

    if (up)temp->up = up;
    if (down)temp->down = down;

    return temp;
}

DLL_EXPORT NLAYER *_CreateParallelLayer(NLAYER *prev, NLAYER *next, NEURON *first) {
    NLAYER *temp = _CreateCenterLayer(first);
    if (!temp)return 0;

    if (next)temp->next = next;
    if (prev)temp->prev = prev;

    return temp;
}

/*
 * Дублекатоникатинг+заебательнопереперенедопроверятель по всем пара-пам-пам..
 * Для завихрюнистобоюднодизраскритикоA<Б^ Вирту6соскипфюхь.
 * -Сомнительная и странно поподозрительности необломая,
 * -Так над/2=обратнозавыноровленая по разложненностиЯ~=$(-^/<);
 * -Человечкчкчо как золевичочек-перперекрытовысаживатель, щта? скажете?
 * -Есть.
 * -Ну так  ?
 * -(тктк) Да ну так-то да параноюперевысаживаю, бывает,ненадо так, пере&&!|Си|-|ЖИВ|!&&~=аАБЪЬьъБЮA<^>..
 * -хде?
 * -тамь, недоперекротров0бдопереобшапуривает шваргующих, а они там какие-то медеЦЪско с чем-то вроде аргональным...
 * -(?ВСЕМ?)1.Всем "НЕПЕРЕКРЫТНОСТНОПОДОМНЫМ" по "НЕДОПЕРЕВЫСАЖИАТЕЛЮПОДОБНОВУ", взаимноантиобратноудобному, \
 конечно, обоюднопридержЖживающегося этого всего, ну и много там чего..Эээххъ(.
 * -ЧЧ так печально?
 * -Да кота найти не могу.. а осталС . {if(a->out){int gdRUznt=0; while(a->out){gDRUznt+=1;
 //gDRUznt+1; ПлаКЪИХК ПоКТЬШЪЖж13ВЙ &DD->o(||||&&!||!&&||||)~='"'&^("Пяньъкж-хкустик")>("0x4402 ZMRWNA<")v(х)..
 //А дзжмусикэта все нет и еще 2,5Гг. Нибудет Pi(iii)ЪЯДТХЖ(КЗТПИЙ)
 //(Пиговновая ДиссоциативциON ноподобна маленькому многомерному какушенку нплинъа ViD->O0pay(MoneyCollector.c))
 //UuuuuuUYyуУЙQ,~- хдэ мой^собственной Дзжмусикэт? Почему его все ++ wait too ublong long timeisafter? Нечем заняться,
 // продолжаем тогддкгдгдге поминновородяш,.="хорромордоввывворовывать...взаимноуже готова.
 * a->out=a->out->next;
 }
 }
 }
 */


DLL_EXPORT void _DeleteLayer(NLAYER *it) {
    if (!it)return;
    if (it->state != STATE_READY)return;
    it->state = STATE_NOT_READY;

    _DeleteNeuroList(it->first);

    if (it->up)it->up->down = it->down;
    if (it->down)it->down->up = it->up;
    if (it->next)it->next->prev = it->prev;
    if (it->prev)it->prev->next = it->next;

    if (it->IDOffset != -1) {
        _CreateFDL(it->IDOffset, FIDL_LAYERS);
    }

    AddLayersCount(-1);
    free(it);
}

DLL_EXPORT void _MoveDataFromLayer(NLAYER *from, NLAYER *to) {
    if (!from || !to)return;
    if (from->state != STATE_READY || to->state != STATE_READY)return;
    from->state = STATE_NOT_READY;
    NEURON *temp = from->first;

    while (temp) {
        temp->Layer = to;
        to->neurocount++;
        from->neurocount--;
        temp = temp->next;
    }

    if (to->first) { //Если существует, вставить в конец списка
        to->end->next = from->first;
        to->end = from->end;
        //            if(from->end)from->end->next=to->first;
        //            else return;
    } else { //Иначе перевязать на себя
        to->first = from->first;
        to->end = from->end;
    }

    from->first = 0;
    from->end = 0;
    from->state = STATE_READY;
}

DLL_EXPORT void _ActivateLayer(NLAYER *lay) {
    //	NLAYER *temp=lay;
    _ActivateLayerFunc(lay, lay->first, lay->end);
}

DLL_EXPORT int _ConnectLayer(NLAYER *first, NLAYER *second, int method, int (*func)(NLAYER *, NLAYER *)) {

    int tempintval = 0;
    LINK *templink = NULL;
    NEURON *tempf = NULL, *temp2f = NULL;
    NEURON *temps = NULL, *temp2s = NULL;
    NEURON *tempneuro = NULL, *tempneuro2 = NULL;
    if ((!first) || (!second))return -1;
    if (!first->first)return -2;
    if (!second->first)return -3;

    switch (method) {
    case 0: {
        if (func)
            return func(first, second);
        else return 0;
    }
    case 1: {
        //Метод @Галлактика+-@
        tempf = first->first, temp2f = first->end;
        temps = second->first, temp2s = second->end;
        while (tempf && temp2s) {
            templink = _ConnectNeuron(tempf, temp2s, tempintval);
            if (!templink)break;
            tempintval++;
            tempf = tempf->next;
            temp2s = temp2s->prev;
        }
        while (temps && temp2f) {
            templink = _ConnectNeuron(temps, temp2f, tempintval);
            if (!templink)break;
            tempintval--;
            temps = temps->next;
            temp2f = temp2f->prev;
        }
        //По кругу с разных сторон пока не сойдуться в центре
        //!Плевать на количественную разницу.
        //!В ущерб идет качественная структурная оптимизация
        //!Существует вероятность неподключенных остатков
        break;
    }
    case 2: {
        //Прямой путь "Правильный"
        tempf = first->first, temp2f = first->end;
        temps = second->first, temp2s = second->end;
        while (tempf && temps) {
            templink = _ConnectNeuron(tempf, temps, tempintval);
            if (!templink)break;
            tempintval++;
            tempf = tempf->next;
            temps = temps->next;
        }
        tempintval = 0;
        while (temp2f && temp2s) {
            templink = _ConnectNeuron(temp2f, temp2s, tempintval);
            if (!templink)break;
            tempintval++;
            temp2f = temp2f->prev;
            temp2s = temp2s->prev;
        }
        break;
        //По с разных сторон пока не всё
        //!Плевать на количественную разницу.
        //!В ущерб не идет качественная структурная оптимизация
        //!Существует вероятность неподключенных остатков
    }
    case 3: {
        //Метод "MechanicaLoop" (.спустись в ад и вернись назад.)
        tempf = first->first, temp2f = first->end;
        temps = second->first, temp2s = second->end;
        char breakbyte = 0;
        LINK *temp = 0;
        temps = temps->next;
        while (tempf) {
            if (temps) {
                templink = _ConnectNeuron(tempf, temps, tempintval);
                if (!templink)break;
            } else while (tempf) {
                    if (tempf->next) {
                        templink = _ConnectNeuron(tempf, tempf->next, tempintval);
                        if (!templink)break;
                    } else {
                        breakbyte = 1;
                        break;
                    }
                    tempf = tempf->next;
                }
            tempintval++;
            if (!breakbyte) {
                tempf = tempf->next;
            } else break;
            temps = temps->next;
        }
        while (temp2s) {
            if (breakbyte) {
                while (tempf) {
                    temp = _GetConnection(tempf, tempf->prev);
                    if (temp->weight == tempintval - 1) {
                        templink = _ConnectNeuron(tempf, temp2s, tempintval);
                        if (!templink)break;
                    } else {
                        templink = _ConnectNeuron(temp2s, tempf, tempintval);
                        if (!templink)break;
                        temp2s = temp2s->prev;
                        break;
                    }
                    tempf = tempf->prev;
                }
                breakbyte = 0;
            }

            templink = _ConnectNeuron(tempf, temp2s, tempintval);
            if (!templink)break;
            if (temp2s->prev) {
                templink = _ConnectNeuron(temp2s, tempf->prev, tempintval);
                temp2s = temp2s->prev;
            }
            tempintval--;
            tempf = tempf->prev;
        }
        //По с разных сторон перекрестным огнем, по остаткам как по головам.
        //!Плевать на количественную разницу.
        //!В ущерб не идет качественная структурная оптимизация но есть вероятность залупиться
        //!Не существует вероятности неподключенных остатков

    }
    case 4: {
        //Метод "О-о-."(+79033235592) 18:02 (Скат покрыжен, Shina получена)
        tempf = first->first, temp2f = first->end;
        temps = second->first, temp2s = second->end;
        tempneuro = tempf, tempneuro2 = temp2f;
        tempintval = 0;
        while (tempneuro && tempneuro2) {
            while (tempf) {
                templink = _ConnectNeuron(tempf, temp2s, tempintval);
                if (!templink)break;
                tempf = tempf->next;
            }
            tempneuro = tempneuro->next;
            tempneuro2 = tempneuro2->prev;
            tempf = tempneuro;
            temp2s = tempneuro2;
        }
        break;
        //Это внеземная технология, описывать не имею права, все следует из названия метода.
    }
    case 5: {
        //Метод оптимизации Ni+N(i+1)=Zi;Ni=N(i+1);Zi=Z(i+1)
        //Требует оптимизации.../
        tempf = first->first, temp2f = first->end;
        temps = second->first, temp2s = second->end;
        while (tempf->next) {
            templink = _ConnectNeuron(tempf, temps, tempintval);
            if (!templink)break;
            templink = _ConnectNeuron(tempf->next, temps, tempintval * (-1));
            if (!templink)break;
            tempf = tempf->next;
            temps = temps->next;
        }
        while (temps) {
            templink = _ConnectNeuron(temp2f, temps, tempintval);
            if (!templink)break;
            temps = temps->next;
        }
        break;
        //Точнее и однозначнее быть не может
        //!Лучше из большего к меньшему количеству.
        //хзхз!В ущерб не идет качественная структурная оптимизация
        //!Существует вероятность неподключенных остатков
    }
    case 6: {
        //Метод цели Ni+N(i+1)=Zi;Ni=N(i+2);Zi=Z(i+1)
        tempf = first->first, temp2f = first->end;
        temps = second->first, temp2s = second->end;
        while (tempf && tempf->next) {
            templink = _ConnectNeuron(tempf, temps, tempintval);
            if (!templink)break;
            templink = _ConnectNeuron(tempf->next, temps, tempintval * (-1));
            tempf = tempf->next->next;
            temps = temps->next;
        }
        while (temps) {
            templink = _ConnectNeuron(temp2f, temps, tempintval);
            if (!templink)break;
            temps = temps->next;
        }
        break;
        //Разнообразнее быть не может
        //!Лучше из большего к меньшему количеству.
        //В ущерб идет качественная структурная оптимизация при кривизне
        //организации выбора метода связи!
        //(ващпе не страшно, с 1 раза не въедут, придется въехать с другого раза)
        //не существует вероятности неподключенных остатков
    }
    default: {
        if (!func)return -4;
        else return func(first, second);
    }
    }
    return 1;
}

DLL_EXPORT int _ConnectLayerToNeuron(NLAYER *from, NEURON *it, int method) {
    NEURON *first = from->first, *second = from->end;
    LINK *templink = 0;
    int tempintval = 0, retval = 0;
    switch (method) {
    case 1: {
        //Метод "©И?"
        while (first) {
            templink = _ConnectNeuron(first, it, tempintval);
            if (!templink)break;
            tempintval++;
            first = first->next;
        }
        retval = 1;
        break;
    }
    default: {
        while (first) { //Метод "GodEve"(ЙЯОЙ)
            templink = _ConnectNeuron(first, it, tempintval);
            if (!templink)break;
            tempintval++;
            first = first->next;
        }
        first = from->first;
        while (first != second) {
            templink = _ConnectNeuron(first, first->next, tempintval);
            if (!templink)break;
            templink = _ConnectNeuron(second, second->prev, tempintval);
            if (!templink)break;
            tempintval--;
            second = second->prev;
            first = first->next;
        }
        templink = _ConnectNeuron(first, it, tempintval);
        if (!templink)break;
        retval = 0;
    }
    }
    return retval;
}

DLL_EXPORT NEURON *_GetNeuronByID(NLAYER *cur, long IDOffSet) {
    if (!cur)return 0;
    NEURON *temp = cur->first;
    while (temp) {
        if (temp->IDOffset == IDOffSet)break;
        temp = temp->next;
    }
    return temp;
}

DLL_EXPORT int _SetDataToLayer(ntype *mass, int n, NLAYER *lay) {
    NLAYER *templ = lay;
    NEURON *cur = templ->first;
    int i = 0;
    while (cur) {
        if (!cur->incount)lay->neurocount_activ++;
        if (i < n)
            cur->val = mass[i];
        else break;
        i++;
        cur = cur->next;
    }
    if (!cur && i < n)return -1;
    if (cur)return -2;
    return 0;
}

/*
 * Как вариант оставить только SetDataToLayer(ntype)
 * И дополнить либу функцией привидения значений массива X;Y к ntype
 */
//

/*
 * Как лучш всего сделать нечто вроде последовательного перелажатора и
 * размазывателя поступающих ячеек данных по массиву.
 * type=StartDataInject(sizeof(ntype),sizeof(data),data);//maxblktoonedata?
 * NextDataInject(type,sizeof(data),data);//(type,sizeof(data),data,maxblktoonedata)?0:1
 * malloced=GetNtypeMass(type);
 * ...
 * Free(malloced);
 * EndDataInject(type);
 * ...
 * Либо можно обойтись без временных массивов ntype и вставлять прямиком в слой
 * но это получится вилка для помещения данных втуда.
 */

DLL_EXPORT DIOMAN *_DataInjectStart(int szoftobox, int szofdata, void *data) {
    DIOMAN *retval = NULL;
    unsigned char *nude = (unsigned char *) data;
    int sizeost = szofdata;
    bool drop = false;

    if (!szofdata)return 0;

    retval = (DIOMAN *) _MallocZeroBytes(sizeof (DIOMAN));
    if (retval) {
        retval->blksz = szoftobox;
        retval->first = retval->end = _CreateNeuron(0);
        if (retval->end) {
            retval->count++;
            if (sizeost <= szoftobox) {
                //            retval->count++;
                memcpy(&retval->end->val, nude, szoftobox);
            } else {
                while (sizeost > szoftobox) {
                    //            retval->count++;
                    memcpy(&retval->end->val, nude, szoftobox);
                    nude += szoftobox;
                    sizeost -= szoftobox;

                    _AddNeuronToList(_CreateNeuron(0), retval->end);
                    if (retval->end->next) {
                        retval->count++;
                        retval->end = retval->end->next;
                    } else {
                        drop = true;
                        break;
                    }
                }
                if (drop == false)
                    memcpy(&retval->end->val, nude, sizeost);
            }
        }
    }
    return retval;
}

DLL_EXPORT bool _DataInjectNext(DIOMAN *InJack, int szofdata, void *data) {
    if (!InJack)return false;

    unsigned char *nude = (unsigned char *) data;
    int sizeost = szofdata;
    bool drop = false;

    _AddNeuronToList(_CreateNeuron(0), InJack->end);
    if (!InJack->end->next) return false;
    InJack->count++;
    InJack->end = InJack->end->next;

    if (sizeost <= InJack->blksz) {
        //            InJack->count++;
        memcpy(&InJack->end->val, nude, InJack->blksz);
    } else {
        while (sizeost > InJack->blksz) {
            //            InJack->count++;
            memcpy(&InJack->end->val, nude, InJack->blksz);
            nude += InJack->blksz;
            sizeost -= InJack->blksz;

            _AddNeuronToList(_CreateNeuron(0), InJack->end);
            //Проверка на память
            if (InJack->end->next) {
                InJack->count++;
                InJack->end = InJack->end->next;
            } else {
                drop = true;
                break;
            }
        }
        if (drop == false)
            memcpy(&InJack->end->val, nude, sizeost);
    }
    return true;
}

DLL_EXPORT void _DataInjectEnd(DIOMAN *InJack) {
    NEURON *temp = NULL, *curf = NULL;
    if (InJack) {
        temp = InJack->first;
        if (temp)
            do {
                curf = temp->next;
                _DeleteNeuron(temp);
            } while ((temp = curf));

        free(InJack);
    }
}

/*
 * Функция выделяет память но за освобождением не следит
 * об освобождении заботимся сами, никто ж заранее не знает где любой_из
 * перестанет нуждаться в этом массиве ntype-ов.
 */
DLL_EXPORT ntype *_GetNtypeMassFromDIJ(DIOMAN *InJack) {
    if (!InJack)return 0;
    ntype *netto = NULL;
    NEURON *temp = InJack->first;
    int i = 0;

    netto = (ntype *) _MallocZeroBytes(InJack->count * sizeof (ntype));
    if (netto) {
        while (temp) {
            netto[i] = temp->val;
            i++;
            temp = temp->next;
        }
    } else return 0;
    return netto;
}

//---------------------Dashko-balowashko 8)---------------------------------

DLL_EXPORT int _SetIntDataToLayer(int *mass, int n, NLAYER *lay) {
    NLAYER *templ = lay;
    NEURON *cur = templ->first;
    int i = 0;
    while (cur) {
        if (!cur->incount)lay->neurocount_activ++;
        if (i < n)
            cur->val = mass[i];
        else break;
        i++;
        cur = cur->next;
    }
    if (!cur && i < n)return -1;
    if (cur)return -2;
    return 0;
}

DLL_EXPORT int _SetShortDataToLayer(short *mass, int n, NLAYER *lay) {
    NLAYER *templ = lay;
    NEURON *cur = templ->first;
    int i = 0;
    while (cur) {
        if (!cur->incount)lay->neurocount_activ++;
        if (i < n)
            cur->val = mass[i];
        else break;
        i++;
        cur = cur->next;
    }
    if (!cur && i < n)return -1;
    if (cur)return -2;
    return 0;
}

DLL_EXPORT int _SetByteDataToLayer(unsigned char *mass, int n, NLAYER *lay) {
    NLAYER *templ = lay;
    NEURON *cur = templ->first;
    int i = 0;
    while (cur) {
        if (!cur->incount)lay->neurocount_activ++;
        if (i < n)
            cur->val = mass[i];
        else break;
        i++;
        cur = cur->next;
    }
    if (!cur && i < n)return -1;
    if (cur)return -2;
    return 0;
}

//---------------CLASS------------------

LayersBase::LayersBase() {
    log = NULL;
}

LayersBase::LayersBase(LogSystem *logs) {
    log = logs;
}

void LayersBase::SetLayerActivateChance(NLAYER *lay, char chance) {
    const wchar_t *descr = L"void LayersBase::SetLayerActivateChance(NLAYER *lay, char chance)\r\n";
    _SetLayerActivateChance(lay, chance);
    if (log) {
        log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"Layer:0x%X02,chance:%d", lay, chance);
    }
}

NLAYER *LayersBase::CreateCenterLayer(NEURON *first) {
    const wchar_t *descr = L"NLAYER *LayersBase::CreateCenterLayer(NEURON *first)\r\n";
    NLAYER *retv = 0;
    retv = _CreateCenterLayer(first);
    if (log) {
        if (!retv)
            log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"Neuron:0x%X,return:3", first);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"Neuron:0x%X,return:0x%X", first, retv);
    }
    return retv;
}

NLAYER *LayersBase::CreateLayerWNeuroCount(int count, ntype *memblock) {
    const wchar_t *descr = L"NLAYER *LayersBase::CreateLayerWNeuroCount(int count, ntype *memblock)\r\n";
    NLAYER *retv = 0;
    retv = _CreateLayerWNeuroCount(count, memblock);
    if (log) {
        if (!retv)
            log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"count:%d,return:5", count);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"count:%d,return:Layer:0x%X", count, retv);
    }
    return retv;
}

int LayersBase::AddUperLayer(NLAYER *uplay, NLAYER *center) {
    const wchar_t *descr = L"int LayersBase::AddUperLayer(NLAYER *uplay, NLAYER *center)\r\n";
    int retv = 0;
    retv = _AddUperLayer(uplay, center);
    if (log) {
        if (retv)
            log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"uplay:0x%X04,center:0x%X04,return:%d", uplay, center, retv);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"uplay:0x%X04,center:0x%X04,return:>", uplay, center);
    }
    return retv;
}

int LayersBase::AddDownLayer(NLAYER *downlay, NLAYER *center) {
    const wchar_t *descr = L"int LayersBase::AddDownLayer(NLAYER *downlay, NLAYER *center)\r\n";
    int retv = 0;
    retv = _AddDownLayer(downlay, center);
    if (log) {
        if (retv)
            log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"downlay:0x%X04,center:0x%X04,return:%d", downlay, center, retv);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"downlay:0x%X04,center:0x%X04,return:<", downlay, center);
    }
    return retv;
}

int LayersBase::AddPrevLayer(NLAYER *prevlay, NLAYER *center) {
    const wchar_t *descr = L"int LayersBase::AddPrevLayer(NLAYER *prevlay, NLAYER *center)\r\n";
    int retv = 0;
    retv = _AddPrevLayer(prevlay, center);
    if (log) {
        if (retv)
            log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"prevlay:0x%X04,center:0x%X04,return:%d", prevlay, center, retv);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"prevlay:0x%X04,center:0x%X04,return:/", prevlay, center);
    }
    return retv;
}

int LayersBase::AddNextLayer(NLAYER *nextlay, NLAYER *center) {
    const wchar_t *descr = L"int LayersBase::AddNextLayer(NLAYER *nextlay, NLAYER *center)\r\n";
    int retv = 0;
    retv = _AddNextLayer(nextlay, center);
    if (log) {
        if (retv)
            log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"nextlay:0x%X04,center:0x%X04,return:%d", nextlay, center, retv);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"nextlay:0x%X04,center:0x%X04,return:\\", nextlay, center);
    }
    return retv;
}

int LayersBase::AddNeuroListToLayer(NLAYER *lay, NEURON *first, NEURON *end) {
    const wchar_t *descr = L"int LayersBase::AddNeuroListToLayer(NLAYER *lay, NEURON *first, NEURON *end)\r\n";
    int retv = 0;
    retv = _AddNeuroListToLayer(lay, first, end);
    if (log) {
        if (!retv)
            log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"layer:0x%X03,first:0x%X03,end:0x%X03,return:? ", lay, first, end);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"layer:0x%X03,first:0x%X03,end:0x%X03,return:%d", lay, first, end, retv);
    }
    return retv;
}

NLAYER *LayersBase::CreateHiLoHiLayer(NLAYER *down, NLAYER *up, NEURON *first) {
    const wchar_t *descr = L"NLAYER *LayersBase::CreateHiLoLayer(NLAYER *down, NLAYER *up, NEURON *first)\r\n";
    NLAYER *retv = 0;
    retv = _CreateHiLoLayer(down, up, first);
    if (log) {
        if (!retv)
            log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"down:0x%X03,up:0x%X03,first:0x%X03,return:0", down, up, first);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"down:0x%X03,up:0x%X03,first:0x%X03,return:0x%X03", down, up, first, retv);
    }
    return retv;
}

NLAYER *LayersBase::CreateParallelLayer(NLAYER *prev, NLAYER *next, NEURON *first) {
    const wchar_t *descr = L"NLAYER *LayersBase::CreateParallelLayer(NLAYER *prev, NLAYER *next, NEURON *first)\r\n";
    NLAYER *retv = 0;
    retv = _CreateParallelLayer(prev, next, first);
    if (log) {
        if (!retv)
            log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"prev:0x%X03,next:0x%X03,first:0x%X03,return:-1", prev, next, first);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"prev:0x%X03,next:0x%X03,first:0x%X03,return:0x%X03", prev, next, first, retv);
    }
    return retv;
}

void LayersBase::DeleteLayer(NLAYER *it) {
    const wchar_t *descr = L"void LayersBase::DeleteLayer(NLAYER *it)\r\n";
    if (log) {
        log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"U:DeleteLayer\r\n");
    }
    _DeleteLayer(it);
}

void LayersBase::MoveDataFromLayer(NLAYER *from, NLAYER *to) {
    const wchar_t *descr = L"void LayersBase::MoveDataFromLayer(NLAYER *from, NLAYER *to)\r\n";
    if (log) {
        log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"I^MoveDataFromLaye\r\n");
    }
    _MoveDataFromLayer(from, to);
}

int LayersBase::ConnectLayer(NLAYER *first, NLAYER *second, char method, int (*func)(NLAYER *, NLAYER *)) {
    const wchar_t *descr = L"int LayersBase::ConnectLayer(NLAYER *first, NLAYER *second, char method, int (*func)(NLAYER *, NLAYER *))\r\n";
    int retv = 0;
    retv = _ConnectLayer(first, second, method, func);
    if (log) {
        if (retv)
            log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"first:0x%X03,second:0x%X03,method:%c,func:%x,return:%d", first, second, method, func);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"first:0x%X03,second:0x%X03,method:%c,func:%x,return:-1", first, second, method);
    }
    return retv;
}

int LayersBase::ConnectLayerToNeuron(NLAYER *first, NEURON *it, char method) {
    const wchar_t *descr = L"int LayersBase::ConnectLayerToNeuron(NLAYER *first, NEURON *it, char method) \r\n";
    int retv = 0;
    retv = _ConnectLayerToNeuron(first, it, method);
    if (log) {
        if (retv)
            log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"first:0x%X03,it:0x%X03,method:%c,return:%d", first, it, method, retv);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"first:0x%X03,it:0x%X03,method:%c,return:0", first, it, method);
    }
    return retv;
}

NEURON *LayersBase::GetNeuronByID(NLAYER *cur, long IDOffSet) {
    const wchar_t *descr = L"NEURON *LayersBase::GetNeuronByID(NLAYER *cur, long IDOffSet)\r\n";
    NEURON *retv = 0;
    retv = _GetNeuronByID(cur, IDOffSet);
    if (log) {
        if (!retv)
            log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"cur:0x%X03,IDOffSet:0p%d,return:&", cur, IDOffSet);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"cur:0x%X03,IDOffSet:0p%d,return:0x%X", cur, IDOffSet, retv);
    }
    return retv;
}

void LayersBase::ActivateLayer(NLAYER *lay) {
    const wchar_t *descr = L"void LayersBase::ActivateLayer(NLAYER *lay)\r\n";
    if (log) {
        log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"ActivateLayer\r\n");
    }
    _ActivateLayer(lay);
}

int LayersBase::SetDataToLayer(ntype *mass, int n, NLAYER *lay) {
    const wchar_t *descr = L"int LayersBase::SetDataToLayer(ntype *mass, int n, NLAYER *lay) \r\n";
    int retv = 0;
    retv = _SetDataToLayer(mass, n, lay);
    if (log) {
        if (retv)
            log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"count:%d,Lay:0x%X02,return:%d", n, lay, retv);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"count:%d,Lay:0x%X02,return:NULY", n, lay);
    }
    return retv;
}

int LayersBase::SetIntDataToLayer(int *mass, int n, NLAYER *lay) {
    const wchar_t *descr = L"int LayersBase::SetIntDataToLayer(int *mass, int n, NLAYER *lay)\r\n";
    int retv = 0;
    retv = _SetIntDataToLayer(mass, n, lay);
    if (log) {
        if (retv)
            log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"count:%d,Lay:0x%X02,return:%d", n, lay, retv);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"count:%d,Lay:0x%X02,return:NOL\"", n, lay);
    }
    return retv;
}

int LayersBase::SetShortDataToLayer(short *mass, int n, NLAYER *lay) {
    const wchar_t *descr = L"int LayersBase::SetShortDataToLayer(short *mass, int n, NLAYER *lay)\r\n";
    int retv = 0;
    retv = _SetShortDataToLayer(mass, n, lay);
    if (log) {
        if (retv)
            log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"count:%d,Lay:0x%X02,return:%d", n, lay, retv);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"count:%d,Lay:0x%X02,return:0", n, lay);
    }
    return retv;
}

int LayersBase::SetByteDataToLayer(unsigned char *mass, int n, NLAYER *lay) {
    const wchar_t *descr = L"int LayersBase::SetByteDataToLayer(unsigned char *mass, int n, NLAYER *lay)\r\n";
    int retv = 0;
    retv = _SetByteDataToLayer(mass, n, lay);
    if (log) {
        if (retv)
            log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"count:%d,Lay:0x%X02,return:%d", n, lay, retv);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"count:%d,Lay:0x%X02,return:VZERO", n, lay);
    }
    return retv;
}

DIOMAN *LayersBase::DataInjectStart(int szoftobox, int szofdata, void *data) {
    const wchar_t *descr = L"DIOMAN *LayersBase::DataInjectStart(int szoftobox, int szofdata, void *data) \r\n";
    DIOMAN *retv = NULL;
    retv = _DataInjectStart(szoftobox, szofdata, data);
    if (log) {
        if (!retv)
            log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"length:%X0F%d,return:Niht!", szofdata, szoftobox);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"length:%X0F%d,return:Vobl'YaZz'\"%d", szofdata, szoftobox, retv);
    }
    return retv;
}

bool LayersBase::DataInjectNext(DIOMAN *InJack, int szofdata, void *data) {
    const wchar_t *descr = L"bool LayersBase::DataInjectNext(DIOMAN *InJack, int szofdata, void *data)\r\n";
    bool retv = 0;
    retv = _DataInjectNext(InJack, szofdata, data);
    if (log) {
        if (retv == false)
            log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"InJack:%d,length:%X0F%d,return:fаlsе", InJack, data, szofdata);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"InJack:%d,length:%X0F%d,return:tr0-1~1-0ЮЭ", InJack, data, szofdata);
    }
    return retv;
}

ntype *LayersBase::GetNtypeMassFromDIJ(DIOMAN *InJack) {
    const wchar_t *descr = L"ntype *LayersBase::GetNtypeMassFromDIJ(DIOMAN *InJack)\r\n";
    ntype *retv = 0;
    retv = _GetNtypeMassFromDIJ(InJack);
    if (log) {
        if (!retv)
            log->AddInfo(DI_LOG_LEVEL_WARNING, descr, L"InJack:%d,return:*void...", InJack);
        else log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"InJack:%d,return:%x", InJack, retv);
    }
    return retv;
}

void LayersBase::DataInjectEnd(DIOMAN *InJack) {
    const wchar_t *descr = L"void LayersBase::DataInjectEnd(DIOMAN *InJack)\r\n";
    _DataInjectEnd(InJack);
    if (log) {
        log->AddInfo(DI_LOG_LEVEL_INFO, descr, L"DataInjectEnd\r\n");
    }
}

