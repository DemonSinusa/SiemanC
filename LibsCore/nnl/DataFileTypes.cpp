/*
 * File:   DataFileTypes.h
 * Author: 123
 *
 * Created on 1 Март 2014 г., 18:58
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "DataFileTypes.h"

void *_MallocZeroBytes(unsigned int size) {
    void *datablk = NULL;
    datablk = malloc(size);
    if (datablk)memset(datablk, 0x00, size);
    return datablk;
}

#ifdef __linux__

#include <unistd.h>

int _wCrossUnlink(const wchar_t* filename) {
    int unret = 0;
    const wchar_t *ss = filename;
    int i = (int) wcsrtombs(NULL, &ss, 0, NULL);
    if (i < 0) return -1;
    char *ffile = (char *) malloc(i + 1);
    wcsrtombs(ffile, &filename, i, NULL);
    ffile[i] = 0;
    unret = unlink(ffile);
    free(ffile);
    return unret;
}

FILE* _wCrossFopen(const wchar_t* filename, const wchar_t* mode) {
    FILE *fh = 0;
    const wchar_t *ss = filename;
    int i = (int) wcsrtombs(NULL, &ss, 0, NULL);
    if (i < 0) return NULL;
    char *ffile = (char *) malloc(i + 1);
    wcsrtombs(ffile, &filename, i, NULL);
    ffile[i] = 0;

    ss = mode;
    i = (int) wcsrtombs(NULL, &ss, 0, NULL);
    char *fmode = 0;
    if (i < 0) {
        fmode = (char *) "a+b";
    } else {
        fmode = (char *) malloc(i + 1);
        wcsrtombs(fmode, &mode, i, NULL);
        fmode[i] = 0;
    }
    fh = fopen(ffile, fmode);

    free(ffile);
    free(fmode);

    return fh;
}

int _wCrossAccess(const wchar_t* filename, int mode) {
    const wchar_t *ss = filename;
    int i = (int) wcsrtombs(NULL, &ss, 0, NULL), Iret = -1;

    if (i < 0) return -1;
    char *ffile = (char *) malloc(i + 1);

    wcsrtombs(ffile, &filename, i, NULL);
    ffile[i] = 0;

    //ENOENT	Файл не найден
    //EACCES	Нет доступа

    Iret = access(ffile, mode);
    free(ffile);

    return Iret;
}
#else
//То же только под Шиндовс


#endif

