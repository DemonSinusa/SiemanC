#ifndef _LANG_H_
#define _LANG_H_

#include "libexport.h"

//---------------------------------------------------------------------------

enum LGP_ID {
    LGP_AlreadyStarted = 0,
    LGP_LangCodePage,
    LGP_LibTitle,
    LGP_LibCopyLeWrongERR,

    LGP_YESNO,
    LGP_NOYES,

    LGP_UNYESNO,
    LGP_UNNOYES,

    LGP_UNDEREXYZ,
    LGP_DEUNREXYZ,
    LGP_REDEUNXYZ,

    LGP_LDT_DEFRN, //\r\n

    LGP_DEFERROR, //				L"!Ошибка №-%d!%c%cНа момент происхождения описана как:%c%c%s"
    LGP_DEFWARN, //				L"!Предупреждение №-%d!%c%cНа момент происхождения описано как:%c%c%s"
    LGP_INFO, //					L"!На заметку по №-%d!%c%cНа момент происхождения принесло:%c%c%s"
    LGP_DEBUGLZ, //				L"Отладки ради по №-%d%c%cНеначто здесь смотреть.:Ж;}"

    LGP_LDW_NOTALL, //			"Не все данные удалось получить (частичная потеряшка)"

    LGP_CLLOOPBACK, //			L"Дай-ка сообзитьъ..."

    LGP_FILENOTRW,
    LGP_FILENOACCESS,
    LGP_FILENOALL,

    LGP_LangCode, // Пусть всегда будет в конце

    LGP_DATA_NUM
};

//---------------------------------------------------------------------------
//typedef struct LGP_Item LGP_Item;

typedef struct LGP_Item {
    char *tag;
    int id;
    wchar_t *LgpData;
} LGP;

typedef struct LGP_file_block {
    int id;
    int taglen, lgpdatalen;
} LGPFB;

#ifdef __cplusplus
extern "C" {
#endif

    DLL_EXPORT int lgpLoadLangpackByFile(const wchar_t *file_path);
    DLL_EXPORT int lgpLoadLangpack(wchar_t *settings_path);
    DLL_EXPORT void lgpModifyLGPStringByID(int id, wchar_t *lgpstr);
    DLL_EXPORT void lgpModifyLGPStringByTag(char *tagstr, wchar_t *lgpstr);
    DLL_EXPORT int lgpSaveLangpackByFile(wchar_t *file_path);
    DLL_EXPORT int lgpSaveLangpack(wchar_t *settings_path);
    DLL_EXPORT void lgpFreeLangPack(void);
    //---------------------------------------------------------------------------

    extern LGP_Item LGPTAGS[];

#ifdef __cplusplus
}
#endif

#endif /* _LANG_H_ */

