#include <swilib.h>
//#include <stdlib.h>
#include <cfg_items.h>
#include "conf_loader.h"

/*
    Переделанный загрузчик конфига под gcc.
    (c) Z.Vova
*/


char *successed_config_filename="?:\\ZBin\\etc\\Macro.bcfg";

//Пригодиться
CFG_HDR *lastcfg=NULL;
unsigned int lastcfglen=0;


int SaveConfigData() {
	int result=0,fh=0;
	unsigned int err;
	if(successed_config_filename[0]=='?')InitConfig();
	else {
		if ((fh=_open(successed_config_filename,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&err))!=-1) {
			if (_write(fh,lastcfg,lastcfglen,&err)!= (int)lastcfglen) result=-1;
			_close(fh,&err);
		} else
			result=-1;
	}
	return result;
}
//__attribute__((section("CONFIG_C")))
int LoadConfigData(const char *fname, CFG_HDR *cfghdr0, int * __config_begin, int * __config_end) {
	int f;
	unsigned int ul;
	char *buf;
	int result=0;
	void *cfg;

	//extern const int __config_end, __config_begin;
	cfg=(void*)cfghdr0;
	volatile unsigned int _segb = (volatile unsigned int)__config_begin;
	volatile unsigned int _sege = (volatile unsigned int)__config_end;


	lastcfglen= (_sege - _segb)-4;
	if (!(buf=(char *)malloc(lastcfglen))) return -1;
	if ((f=_open(fname,A_ReadOnly+A_BIN,0,&ul))!=-1) {
		if (_read(f,buf,lastcfglen,&ul) == (int)lastcfglen) {
			memcpy(cfg,buf,lastcfglen);
			lastcfg=(CFG_HDR *)cfg;
			_close(f,&ul);
		} else {
			_close(f,&ul);
			//goto L_SAVENEWCFG;
			//--------
			successed_config_filename[0]=fname[0];
			if((result=SaveConfigData())<0)successed_config_filename[0]='?';
		}
	} else {
		//----------
		successed_config_filename[0]=fname[0];
		if((result=SaveConfigData())<0)successed_config_filename[0]='?';
		//----------
		/*
		L_SAVENEWCFG:
		if ((f=_open(fname,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
		{
		  if (_write(f,cfg,lastcfglen,&ul)!= (int)lastcfglen) result=-1;
		  _close(f,&ul);
		}
		else
		  result=-1;
		  */
	}
	mfree(buf);
	return result;
}


int InitConfig() {
	int nate=0;
	__CONFIG_EXTERN(0, cfghdr0);    // нулевой конфиг и первый его элемент cfghdr0

	successed_config_filename[0]='4';
	if ((nate=LoadConfigData(successed_config_filename, __CONFIG(0, cfghdr0)))<0) {
		successed_config_filename[0]='0';
		nate=LoadConfigData(successed_config_filename, __CONFIG(0, cfghdr0));
	}
	return nate;
}


