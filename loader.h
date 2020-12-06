#ifndef __CmVM_VMLoader_h
#define __CmVM_VMLoader_h

#include "bsl_Uart.h"


/*
void VMLoader_Ping(void);
char VMLoader_GetStatus(void);
void VMLoader_Download(void);
void VMLoader_Run(u8*);
void VMLoader_Reset(void);
*/
//ILoader Loader_GetFactory(const char* whichOne);
u8 VMLoader_Load(u8*);
#endif