#include <swilib.h>
#include <cfg_items.h>

//������������

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

#ifdef ELKA
#define DEF_POS {20,80,220,120}
#else
#define DEF_POS {10,70,120,90}
#endif

__CFG_BEGIN(0)

__root const CFG_HDR cfghdr0= {CFG_COLOR,"���� ����",0,0};
__root const char fon[4]= {0,0,0,100};

__root const CFG_HDR cfghdr1= {CFG_COLOR,"���� ������������",0,0};
__root const char pb[4]= {0xFF,0,0,100};

__root const CFG_HDR cfghdr2 = {CFG_RECT, "XYXY ������� ������������", 0, 239};
//��� ����������� ���, �����, ���. ��������, ���� ��������
__root const RECT POS = DEF_POS;

__root const CFG_HDR cfghdr3= {CFG_CBOX,"����� ������",0,4};
__root const int BUFER=0;
__root const CFG_CBOX_ITEM cfgcbox4[4]= {"16��","32��","64��","!128��-������ ����!"};


__CFG_END(0)
