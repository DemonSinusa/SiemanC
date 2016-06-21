//#include "..\inc\swilib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

#include "DataFileTypes.h"
#include "LGP_DefLGP.h"
#include "LangPack.h"


//wchar_t lgpData[LGP_DATA_NUM][];
int lgpLoaded = 0;
int reloaded = 0;

//---------------------------------------------------------------------------
//Стоковый задефайнинг приколачиванием
//тегов к айдишникам
LGP_Item LGPTAGS[] = {
    {(char *) "LGP_AlreadyStarted", LGP_AlreadyStarted, NULL},
    {(char *) "LGP_LangCodePage", LGP_LangCodePage, NULL},
    {(char *) "LGP_LibTitle", LGP_LibTitle, NULL},
    {(char *) "LGP_LibCopyLeWrongERR", LGP_LibCopyLeWrongERR, (wchar_t *)LG_LIBCOPYLEWRONGERR},

    {(char *) "LGP_YESNO", LGP_YESNO, NULL},
    {(char *) "LGP_NOYES", LGP_NOYES, NULL},

    {(char *) "LGP_UNYESNO", LGP_UNYESNO, NULL},
    {(char *) "LGP_UNNOYES", LGP_UNNOYES, NULL},

    {(char *) "LGP_UNDEREXYZ", LGP_UNDEREXYZ, NULL},
    {(char *) "LGP_DEUNREXYZ", LGP_DEUNREXYZ, NULL},
    {(char *) "LGP_REDEUNXYZ", LGP_REDEUNXYZ, NULL},

    {(char *) "LGP_LDT_DEFRN", LGP_LDT_DEFRN, NULL},

    {(char *) "LGP_DEFERROR", LGP_DEFERROR, NULL},
    {(char *) "LGP_DEFWARN", LGP_DEFWARN, NULL},
    {(char *) "LGP_INFO", LGP_INFO, NULL},
    {(char *) "LGP_DEBUGLZ", LGP_DEBUGLZ, NULL},

    {(char *) "LGP_LDW_NOTALL", LGP_LDW_NOTALL, NULL},

    {(char *) "LGP_CLLOOPBACK", LGP_CLLOOPBACK, NULL},

    {(char *) "LGP_FILENOTRW", LGP_FILENOTRW, NULL},
    {(char *) "LGP_FILENOACCESS", LGP_FILENOACCESS, NULL},
    {(char *) "LGP_FILENOALL", LGP_FILENOALL, NULL},

    {(char *) "LGP_LangCode", LGP_LangCode, NULL},

    {(char *) "LGP_DATA_NUM", LGP_DATA_NUM, NULL}
};

//---------------------------------------------------------------------------

DLL_EXPORT void lgpModifyLGPStringByTag(char *tagstr, wchar_t *lgpstr) {
    for (int i = 0; i < LGP_DATA_NUM; i++) {

        if (!strcmp(LGPTAGS[i].tag, tagstr)&&(LGPTAGS[i].id != LGP_LibCopyLeWrongERR)) {
            if (LGPTAGS[i].LgpData)free(LGPTAGS[i].LgpData);
            LGPTAGS[i].LgpData = (wchar_t *)_MallocZeroBytes((wcslen(lgpstr) + 1) * sizeof (wchar_t));
            wcsncpy(LGPTAGS[i].LgpData, lgpstr, wcslen(lgpstr));
            break;
        }
    }
}

DLL_EXPORT void lgpModifyLGPStringByID(int id, wchar_t *lgpstr) {
    for (int i = 0; i < LGP_DATA_NUM; i++) {

        if ((LGPTAGS[i].id == id)&&(LGPTAGS[i].id != LGP_LibCopyLeWrongERR)) {
            if (LGPTAGS[i].LgpData)free(LGPTAGS[i].LgpData);
            LGPTAGS[i].LgpData = (wchar_t *)_MallocZeroBytes((wcslen(lgpstr) + 1) * sizeof (wchar_t));
            wcsncpy(LGPTAGS[i].LgpData, lgpstr, wcslen(lgpstr));
            break;
        }
    }
}

wchar_t *lgpModifyLGPStringByIndex(int id, wchar_t *lgpstr) {
    if (LGPTAGS[id].LgpData)free(LGPTAGS[id].LgpData);
    LGPTAGS[id].id = id;
    LGPTAGS[id].LgpData = (wchar_t *)_MallocZeroBytes((wcslen(lgpstr) + 1) * sizeof (wchar_t));
    wcsncpy(LGPTAGS[id].LgpData, lgpstr, wcslen(lgpstr));
    return LGPTAGS[id].LgpData;
}

//---------------------------------------------------------------------------

void lgpLoadDefault() {

    lgpModifyLGPStringByIndex(LGP_AlreadyStarted, (wchar_t *)LG_ALREADY_STARTED);
    lgpModifyLGPStringByIndex(LGP_LangCodePage, (wchar_t *) LG_LANGCODEPAGE);
    lgpModifyLGPStringByIndex(LGP_LibTitle, (wchar_t *) LG_LIBTITLE);
    //	lgpModifyLGPStringByIndex(LGP_LibCopyLeWrongERR,(wchar_t *) LG_LIBCOPYLEWRONGERR);
    lgpModifyLGPStringByIndex(LGP_YESNO, (wchar_t *) LG_YESNO);
    lgpModifyLGPStringByIndex(LGP_NOYES, (wchar_t *) LG_NOYES);

    lgpModifyLGPStringByIndex(LGP_UNYESNO, (wchar_t *) LG_UNYESNO);
    lgpModifyLGPStringByIndex(LGP_UNNOYES, (wchar_t *) LG_UNNOYES);

    lgpModifyLGPStringByIndex(LGP_UNDEREXYZ, (wchar_t *) LG_UNDEREXYZ);
    lgpModifyLGPStringByIndex(LGP_DEUNREXYZ, (wchar_t *) LG_DEUNREXYZ);
    lgpModifyLGPStringByIndex(LGP_REDEUNXYZ, (wchar_t *) LG_REDEUNXYZ);

    lgpModifyLGPStringByIndex(LGP_LDT_DEFRN, (wchar_t *) LDT_DEFRN);

    lgpModifyLGPStringByIndex(LGP_DEFERROR, (wchar_t *) LG_DEFERROR);
    lgpModifyLGPStringByIndex(LGP_DEFWARN, (wchar_t *) LG_DEFWARN);
    lgpModifyLGPStringByIndex(LGP_INFO, (wchar_t *) LG_INFO);
    lgpModifyLGPStringByIndex(LGP_DEBUGLZ, (wchar_t *) LG_DEBUGLZ);

    lgpModifyLGPStringByIndex(LGP_LDW_NOTALL, (wchar_t *) LDW_NOTALL);

    lgpModifyLGPStringByIndex(LGP_CLLOOPBACK, (wchar_t *) LG_CLLOOPBACK);

    lgpModifyLGPStringByIndex(LGP_FILENOTRW, (wchar_t *) LG_FILENOTRW);
    lgpModifyLGPStringByIndex(LGP_FILENOACCESS, (wchar_t *) LG_FILENOACCESS);
    lgpModifyLGPStringByIndex(LGP_FILENOALL, (wchar_t *) LG_FILENOALL);


    lgpModifyLGPStringByIndex(LGP_LangCode, (wchar_t *) LG_LANGCODE);

}
//---------------------------------------------------------------------------

DLL_EXPORT int lgpSaveLangpackByFile(wchar_t *file_path) {
    FILE *hFile;
    LGPFB lgfb;
    char *memblk = NULL;
    //    wchar_t *hui = NULL;

    hFile = _wCrossFopen(file_path, L"w+b");

    if (!hFile)
        return -1;

    for (int i = 0; i < LGP_DATA_NUM; i++) {
        lgfb.id = LGPTAGS[i].id;
        lgfb.taglen = strlen(LGPTAGS[i].tag) + 1;
        lgfb.lgpdatalen = (wcslen(LGPTAGS[i].LgpData) + 1) * sizeof (wchar_t);

        memblk = (char *) _MallocZeroBytes(lgfb.taglen + lgfb.lgpdatalen);
        memcpy(memblk, LGPTAGS[i].tag, lgfb.taglen);
        memcpy(&memblk[lgfb.taglen], LGPTAGS[i].LgpData, lgfb.lgpdatalen);
        //	hui = (wchar_t *) & memblk[lgfb.taglen];
        fwrite(&lgfb, sizeof (LGPFB), 1, hFile);
        fwrite(memblk, lgfb.taglen + lgfb.lgpdatalen, 1, hFile);
        free(memblk);
    }
    fclose(hFile);

    return 1;
}

DLL_EXPORT int lgpSaveLangpack(wchar_t *settings_path) {
    unsigned int lenfpath = 0;
    wchar_t *lang_file = NULL;
    wchar_t *TEMPLATES_LGFILE = (wchar_t *)L"lang.lgp";
    int retval = 0;

    if (lgpLoaded < 1)return 0;

    lenfpath = (wcslen(settings_path) + wcslen(TEMPLATES_LGFILE) + 3) * sizeof (wchar_t);

    lang_file = (wchar_t *) malloc(lenfpath);

    wcscpy(lang_file, settings_path);
    if (lang_file[wcslen(lang_file) - 1] != ((wchar_t *) TRUE_SLASH)[0])
        wcsncat(lang_file, (wchar_t *) TRUE_SLASH, 1);
    wcscat(lang_file, TEMPLATES_LGFILE);


    retval = lgpSaveLangpackByFile(lang_file);
    free(lang_file);

    return retval;
}
//---------------------------------------------------------------------------

DLL_EXPORT int lgpLoadLangpackByFile(const wchar_t *file_path) {
    FILE *hFile;
    LGPFB lgfb;
    int size = 0;
    char *tagblk = NULL;
    int ptr = 0;

    hFile = _wCrossFopen(file_path, L"rb");

    if (!hFile)
        return 0;

    fseek(hFile, 0, SEEK_END);
    size = ftell(hFile);
    fseek(hFile, 0, SEEK_SET);

    //--------------Здесь ошибка, надо проверить?---
    //--И начался парсинг формата
    for (ptr = 0; ptr < size;) {
        if ((fread(&lgfb, sizeof (LGPFB), 1, hFile)) == 1) {
            tagblk = (char *) malloc(lgfb.taglen + lgfb.lgpdatalen);
            //	    lgpstr = (wchar_t *)malloc(lgfb.lgpdatalen);
            if ((fread(tagblk, lgfb.taglen + lgfb.lgpdatalen, 1, hFile)) == 1) {
            }
            lgpModifyLGPStringByTag(tagblk, (wchar_t *) & tagblk[lgfb.taglen]);

            free(tagblk);
            //	    free(lgpstr);
        }
        //	if ((fread(lgpstr, lgfb.lgpdatalen, 1, hFile)) == 1) {
        //
        //	}
        //	(wchar_t *) & buf[ptr + lgfb->taglen + sizeof(LGPFB)];
        //--Добавляем,сверяем, и всё остальное.

        ptr += lgfb.lgpdatalen + lgfb.taglen + sizeof (LGPFB);
    }
    //--И все, что могли, загрузили.

    fclose(hFile);

    reloaded++;

    return 1;
}

DLL_EXPORT int lgpLoadLangpack(wchar_t *settings_path) {
    unsigned int lenfpath = 0;
    wchar_t *lang_file = NULL;
    wchar_t *TEMPLATES_LGFILE = (wchar_t *)L"lang.lgp";
    int retval = 0;

    lenfpath = (wcslen(settings_path) + wcslen(TEMPLATES_LGFILE) + 3) * sizeof (wchar_t);

    lang_file = (wchar_t *) malloc(lenfpath);

    wcscpy(lang_file, settings_path);
    if (lang_file[wcslen(lang_file) - 1] != ((wchar_t *) TRUE_SLASH)[0])
        wcscat(lang_file, (wchar_t *) TRUE_SLASH);
    wcscat(lang_file, TEMPLATES_LGFILE);

    //	lgpData = (wchar_t **)malloc(LGP_DATA_NUM * sizeof(wchar_t *));

    lgpLoadDefault();

    lgpLoaded = 1;

    retval = lgpLoadLangpackByFile(lang_file);

    //Обновить значения переменных, перерисовать там.. и все остальное короч...
    // чето_тут=lgpData[гдето_в_перечислении]
    return retval;
}

//---------------------------------------------------------------------------

DLL_EXPORT void lgpFreeLangPack(void) {
    int i, id;
    for (i = 0; i < LGP_DATA_NUM; i++) {
        id = LGPTAGS[i].id;
        if (id != LGP_LibCopyLeWrongERR)
            free(LGPTAGS[id].LgpData);
    }
    //lgpLoadDefault();
}
//---------------------------------------------------------------------------

