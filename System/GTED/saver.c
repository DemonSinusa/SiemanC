#include <swilib.h>

extern unsigned int STKSZ;
extern unsigned int STKSZ50;

extern int u_disk; //�������� ��������� �������� ����� (� ������ �� STKSZ50)
extern int d_disk; //�������� ��������� ������� ����� (� ������ �� STKSZ50)
extern unsigned int usp; //��������� �� ������� ����
extern unsigned int dsp; //��������� �� ������ ����
extern unsigned int dbat[]; //������� ������������� ������ ������� ����� �� ��������� �����
extern unsigned int ubat[]; //������� ������������� ������ �������� ����� �� ��������� ����e
extern char stkfile[];
extern char filename[];

extern char *dstk;
extern char *ustk;

extern volatile int disk_access;

extern unsigned int bl_ds(unsigned int pos);

extern int terminated; //������� �������� �������
extern volatile unsigned int draw_mode;

extern void DiskErrorMsg(int mode);

#define flush_obuf(FILEH,P) {if (P>=STKSZ50) {if (_write(FILEH,obuf,P,&ul)!=P) DiskErrorMsg(4); P=0;}}

void savetext(void)
{
  char *ibuf=NULL;
  char *obuf=NULL;

  int sf;
  int f;
  unsigned int p;
  unsigned int ul;
  int i;
  char c;
  unsigned int seekpos;

  if (!(ibuf=malloc(STKSZ50)))
  {
    LockSched();
    ShowMSG(1,(int)"Can't alloc IBUF!");
    UnlockSched();
    goto LERR1;
  }
  if (!(obuf=malloc(STKSZ50)))
  {
    LockSched();
    ShowMSG(1,(int)"Can't alloc OBUF!");
    UnlockSched();
    goto LERR1;
  }
  f=_open(filename,A_ReadWrite+A_BIN+A_Create+A_Truncate,P_READ+P_WRITE,&ul); //������� �������� ����
  if (f==-1)
  {
    DiskErrorMsg(4);
    goto LERR1;
  }
  sf=_open(stkfile,A_ReadOnly+A_BIN,P_READ,&ul); //���� �������� �����
  if (f==-1)
  {
    DiskErrorMsg(3);
    goto LERR2;
  }

  i=0;
  while(i<=u_disk)
  {
    //����� ������� ���� ���������������
    p=ubat[i++];
    seekpos=STKSZ50*p;
    if (_lseek(sf,seekpos,0,&ul,&ul)!=seekpos) DiskErrorMsg(2);
    if (_read(sf,ibuf,STKSZ50,&ul)!=STKSZ50) DiskErrorMsg(0);
    p=0;
    while(p!=STKSZ50)
    {
      if (!ibuf[p]) ibuf[p]=0x0D;
      p++;
    }
    if (_write(f,ibuf,STKSZ50,&ul)!=STKSZ50) DiskErrorMsg(4);
  }
  //����� ������� ���� �� ���
  p=0;
  i=0;
  while(p!=usp)
  {
    c=ustk[p];
    if (!c) c=0x0D;
    obuf[i]=c;
    i++;
    flush_obuf(f,i);
    p++;
  }
  p=dsp;
  while(p!=STKSZ)
  {
    //����� ������ ���� �� ���
    c=dstk[p];
    if (!c) c=0x0D;
    obuf[i]=c;
    i++;
    flush_obuf(f,i);
    p++;
  }
  if (_write(f,obuf,i,&ul)!=i) DiskErrorMsg(4); //���������
  i=d_disk;
  while(i>=0)
  {
    //����� ������ ����
    p=dbat[i--];
    seekpos=STKSZ50*p;
    if (_lseek(sf,seekpos,0,&ul,&ul)!=seekpos) DiskErrorMsg(2);
    if (_read(sf,ibuf,STKSZ50,&ul)!=STKSZ50) DiskErrorMsg(0);
    p=0;
    while(p!=STKSZ50)
    {
      if (!ibuf[p]) ibuf[p]=0x0D;
      p++;
    }
    if (_write(f,ibuf,STKSZ50,&ul)!=STKSZ50) DiskErrorMsg(4);
  }
  _close(sf,&ul); //����� ������ ����������� � ������� �����
LERR2:
  _close(f,&ul);
LERR1:
  mfree(ibuf);
  mfree(obuf);
  disk_access=0;
  draw_mode=1; //��������������
  REDRAW();
}

