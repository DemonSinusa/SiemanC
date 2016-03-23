/*
 * File:   LogSystem.h
 * Author: Anton
 *
 * Created on 16 мая 2014 г., 19:45
 */

#ifndef LOGSYSTEM_H
#define	LOGSYSTEM_H

#include "libexport.h"

//#define LOGLEVEL_ZBUG   0
//#define LOGLEVEL_INFO   1
//#define LOGLEVEL_MESS   2
//#define LOGLEVEL_WARN   3
//#define LOGLEVEL_ERROR  4
/*
 * Пользуясь случаем хочу выразить благодарность коллективу энтузиастов из кадастра
 * и этим ж закадастрить каждый &пальцеклацный& |Окаменений| !в заголовках заголовка достаточно будет!
 * текст по методу рекурсивного последовательного разложения "Кадастровой Важности". Хоть это и был Я)
 * 
 * Пример:Х.ХХ.ХХХ
 * Вибратор.хи
 * Вибратор.си	2.
 * ---Неоченьважно.01
 * ---Оченьважно.02
 * ---Чутьповажнее.03
 * ---итд
 * Механика.хи
 * Механика.си	1.
 * МШЗингер.си
 *
 * Для Вовки эт важнее, но он и без нас там как на зоне
 * Для меня вот важно-оченьважно-чутьповажнее вызывает некоторый
 * "Затруднительный интерес" но если как по приммеру то после ознакомления
 *  может вызвать некоторое негодование и бурление масс,из технаря,а если
 *  зарекурсивить по степени важности,то разрабов.
 *
 *
 */

//Открыт новый параметр "Кадастровой важности" по методу рекурсивного разложения.
//Инженеры,падаем,падшие поднимаются с вопросом, "а что такое тогороттрнаоброт?"
//Это и есть простое понятие рекурсии для Российского сленгпака.
//тогороттрнаоброт!&|тогороттрнаоброт|&!тогороттрнаоброт
//Fff,kz cgfkbk((cz)) yf cj,cndtyyjq rjgbgfcnt
//Если возникают сложности с соблюдением точности и пропорциональности
//рекомендую узнать что положиться в основницу,и сколько сочницы с ядренностью
//остается из того что было на предидущем этапе,а там как погипотэнтузиаст...
//Главное вмеру если уверенность позволяет оставить без разбирательной составляющей.
//Так печется все что угодно у лучших умов и всего остального до чего тянемся.
//Удачных эксперементов БелыйКролк
//

enum log_levels {
    DI_LOG_LEVEL_ERROR = 1,
    DI_LOG_LEVEL_WARNING,
    DI_LOG_LEVEL_MESSAGE,
    DI_LOG_LEVEL_INFO,
    DI_LOG_LEVEL_DEBUG
};

typedef struct _log_system_datatype {
    wchar_t *LPath;
    char levl;
    int msgcount;
    FILE *fh;
    void (* WriteTo)(_log_system_datatype *it, wchar_t *msg, int lvl);
} LSD;

class DLL_EXPORT LogSystem {
public:
    LogSystem(char lvl);
    LogSystem(wchar_t *path, char lvl);
    ~LogSystem();

    int AddInfo(const wchar_t *info);
    int AddInfo(char lvl, const wchar_t *info);
    int AddInfo(char lvl, const wchar_t *descr, const wchar_t *fmt, ...);
    LSD *GetLSD();
private:
    LSD *LogSystemType;
};

#ifdef __cplusplus
extern "C" {
#endif

    DLL_EXPORT LSD *_OpenLogFramework(char lvl, wchar_t *path);
    DLL_EXPORT int _AddInfo(LSD *LogSystemDatabase, char lvl, const wchar_t *info);
    DLL_EXPORT int _AddNoRestructInfo(LSD *LogSystemDatabase, char lvl, const wchar_t *descr, const wchar_t *fmt, ...);
    DLL_EXPORT void _CloseLogFramework(LSD *LogSystemDatabase);

#ifdef __cplusplus
}
#endif

#endif	/* LOGSYSTEM_H */

