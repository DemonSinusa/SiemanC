#ifndef _LANGUAGE_H_
#define _LANGUAGE_H_

#define LG_COPYRIGHT   L"Default вАсе-4-Nики"

//Оставляем только один дефайн иначе будет кака
#define LANG_RU
//#define LANG_UA
//#define LANG_EN

#ifdef LANG_RU

#define LG_ALREADY_STARTED  L"Уже запущена!"
#define LG_LANGCODEPAGE   L"win-1251"

#define LG_LIBTITLE    L"NewLibLazy"
#define LG_LIBCOPYLEWRONGERR LG_COPYRIGHT

#define LG_YESNO    L">>Нет"
#define LG_NOYES    L"Нет"

#define LG_UNYESNO    L">>Да"
#define LG_UNNOYES    L"Да"

#define LG_UNDEREXYZ   L"Неоднозначностъ"
#define LG_DEUNREXYZ   L"--<<0>>++"
#define LG_REDEUNXYZ   L"Норовишь апдевайднутсъ!"

#define LDT_DEFRN    L"\r\n"

#define LG_DEFERROR    L"№-%d:На момент происхождения описана как:%ls%ls\t\t"
#define LG_DEFWARN    L"№-%d:На момент происхождения описано как:%ls%ls\t\t"
#define LG_INFO     L"№-%d:На момент происхождения принесло:%ls%ls\t\t"
#define LG_DEBUGLZ    L"№-%d:Неначто здесь смотреть.:Ж;}%ls%ls\t\t"

#define LDW_NOTALL    L"Не все данные удалось получить (частичная потеряшка)"

#define LG_CLLOOPBACK   L"Дай-ка сообзитьъ..."

#define LG_FILENOTRW   L"№-%d:Файл %ls существует,%ls\tно открыт с правами !\"RW\".%ls\t\t"
#define LG_FILENOACCESS   L"№-%d:Файл %ls существует,%ls\tно доступ к нему ограничен.%ls\t\t"
#define LG_FILENOALL   L"№-%d:Файл %ls отсутствует,создать невозможно,%ls\tдоступ к ресурсу ограничен.%ls\t\t"

#define LG_LANGCODE    L"Ру"


#endif

#ifdef LANG_UA

#define LG_ALREADY_STARTED "Вже працює!"
LGP_ClLoopback
#define LG_CLTITLE "Контакти..."
#define LG_CLT9INP "Ввід T9: "

#define LG_CLERROR "помилка"

#define LG_CLLOOPBACK "Loopback"
#define LG_GROUPNOTINLIST "Нема в списку"
//===============================


#define LG_LANGCODE "ua"

#endif

#ifdef LANG_EN

#define LG_ALREADY_STARTED "Already started!"

#define LG_CLTITLE "Contacts..."
#define LG_CLT9INP "T9 Key: "

#define LG_CLERROR "error"

#define LG_CLLOOPBACK "Loopback"

#define LG_LANGCODE "en"

#endif

#endif

