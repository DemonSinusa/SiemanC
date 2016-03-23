/*
 * File:   LogSystem.cpp
 * Author: Anton
 *
 * Created on 16 мая 2014 г., 19:45
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctime>
#include <wchar.h>
//#include <winnt.h>


#include "DataFileTypes.h"
#include "LogSystem.h"

const wchar_t *log_levels_prefix[] = {
    L"Anus I NULL", L"E: ", L"W: ", L"M: ", L"I: ", L"D: "
    /*   [DI_LOG_LEVEL_DEBUG] = L"D: ",
       [DI_LOG_LEVEL_INFO] = L"I: ",
       [DI_LOG_LEVEL_MESSAGE] = L"M: ",
       [DI_LOG_LEVEL_WARNING] = L"W: ",
       [DI_LOG_LEVEL_ERROR] = L"E: "
     */
};

int _ConstructRestructedMSG(LSD *LogSystemDatabase, char lvl, const wchar_t *descr, const wchar_t *fmt, va_list args) {
    LSD *lst = LogSystemDatabase;
    if (lst) {
	if (lvl <= lst->levl) {
	    int msglen = 1024;
	    wchar_t *fullmsg = NULL, *fulldescr = NULL;

	    descr ? msglen += wcslen(descr) + 2 : msglen += 32;

	    fullmsg = (wchar_t *)malloc(sizeof (wchar_t) * msglen); // new wchar_t[msglen];

	    vswprintf(fullmsg, msglen, fmt, args);

	    if (descr) {
		fulldescr = (wchar_t *)malloc(sizeof (wchar_t)*(wcslen(descr) + 3)); // new wchar_t[wcslen(descr) + 3];
		wcscpy(fulldescr, L"(");
		wcscat(fulldescr, descr);
		wcscat(fulldescr, L")");
		wcscat(fullmsg, fulldescr);
		free(fulldescr);
	    }
	    lst->WriteTo(lst, fullmsg, lvl);

	    free(fullmsg);

	    return 0;
	} else return 1;
    } else return -1;
}

void _WriteTo(LSD *LogSystemDeeemmOoOnn, wchar_t *msg, int lvl) {
    time_t seconds = time(NULL);
    tm* timeinfo = localtime(&seconds);
    int wlen = 42;
    wchar_t *dtime = (wchar_t *)malloc(sizeof (wchar_t)*256), *fullmsg = NULL;
    wcsftime(dtime, 255, L"%H:%M:%S-(%d\\%m\\%Y)", timeinfo);
    wlen += wcslen(log_levels_prefix[lvl]) + wcslen(dtime) + wcslen(msg);
    fullmsg = (wchar_t *)malloc(sizeof (wchar_t) * wlen);
    swprintf(fullmsg, wlen, L"%d:%ls|%ls|:%ls", LogSystemDeeemmOoOnn->msgcount, log_levels_prefix[lvl], dtime, msg);
    if (LogSystemDeeemmOoOnn->fh) {
	fwprintf(LogSystemDeeemmOoOnn->fh, L"%ls\r\n", fullmsg);
	fflush(LogSystemDeeemmOoOnn->fh);
    }
    wprintf(L"%ls\r\n", fullmsg);
    free(fullmsg);
    free(dtime);
}

DLL_EXPORT LSD *_OpenLogFramework(char lvl, wchar_t *path) {
    LSD *lst = NULL;
    lst = (LSD *) _MallocZeroBytes(sizeof (LSD));
    lst->levl = lvl;
    if (path) {
	lst->fh = _wCrossFopen(path, L"wb+");
	if (lst->fh) {
	    lst->LPath = (wchar_t *)malloc(sizeof (wchar_t)*(wcslen(path) + 1));
	    lst->LPath = wcscpy(lst->LPath, path);
	}
    }
    lst->WriteTo = _WriteTo;
    return lst;
}

DLL_EXPORT int _AddInfo(LSD *LogSystemDatabase, char lvl, const wchar_t *flirtish) {
    if (LogSystemDatabase) {
	if (lvl <= LogSystemDatabase->levl) {
	    LogSystemDatabase->WriteTo(LogSystemDatabase, (wchar_t *)flirtish, lvl);
	    return 0;
	} else return 1;
    } else return -1;
}

DLL_EXPORT int _AddNoRestructInfo(LSD *LogSystemDatabase, char lvl, const wchar_t *descr, const wchar_t *fmt, ...) {
    int retval = 0;
    va_list args;

    va_start(args, fmt);
    retval = _ConstructRestructedMSG(LogSystemDatabase, lvl, descr, fmt, args);
    va_end(args);
    return retval;
}

DLL_EXPORT void _CloseLogFramework(LSD *LogSystemDatabase) {
    LSD *tlst = LogSystemDatabase;

    if (tlst) {
	if (tlst->fh)
	    fclose(tlst->fh);
	if (tlst->LPath)
	    free(tlst->LPath);
	free(tlst);
    }
}

LogSystem::LogSystem(char lvl) {
    LogSystemType = _OpenLogFramework(lvl, NULL);
}

LogSystem::LogSystem(wchar_t *path, char lvl) {
    LogSystemType = _OpenLogFramework(lvl, path);
}

LogSystem::~LogSystem() {
    _CloseLogFramework(LogSystemType);
}

int LogSystem::AddInfo(const wchar_t *info) {
    return _AddInfo(LogSystemType, 0, (wchar_t *)info);
}

int LogSystem::AddInfo(char lvl, const wchar_t *info) {
    return _AddInfo(LogSystemType, lvl, (wchar_t *)info);
}

int LogSystem::AddInfo(char lvl, const wchar_t *descr, const wchar_t *fmt, ...) {
    int retval = 0;
    va_list args;

    va_start(args, fmt);
    retval = _ConstructRestructedMSG(LogSystemType, lvl, descr, fmt, args);
    va_end(args);
    return retval;
}

LSD *LogSystem::GetLSD() {
    return LogSystemType;
}
