#include <stdlib.h>
#include <stdio.h>
#include <swilib.h>
#include "parametrs.h"



char *dfname="4:\\Zbin\\var\\clipbuf.dat";

void ElfKiller(void)                              //��� ��� ���� �� ���������:
{
kill_elf();
}

int SaveData(WSHDR *data,char *dfile){
	FILE *fh;
	WPARAM p;
	p.maxlen=data->maxlen;
	p.unk1=data->unk1;
if((fh=fopen(dfile,"wb"))==NULL)return -1;
if(fwrite(&p,sizeof(WPARAM),1,fh)!=1){fclose(fh);return -2;}
if(fwrite(data->wsbody,p.maxlen*sizeof(unsigned short),1,fh)!=1){fclose(fh);return -3;}
fclose(fh);
return 0;
}

int main()
{
  WSHDR *mem=NULL;           //�� ������ ������, ������� � �������!
  mem=GetClipBoard(); //�� ��������� ������ � ���� ����������
  if(mem)          //���� ����� ������ ����
  {
  	if(SaveData(mem,dfname)){
		dfname[0]='0';
		SaveData(mem,dfname);
  	}
  }
  SUBPROC((void *)ElfKiller); //����� ���� �� �������
  return(0);                  //����� ���� ����������
}
