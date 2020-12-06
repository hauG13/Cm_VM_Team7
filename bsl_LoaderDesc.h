#ifndef __bsl_LoaderDesc_h
#define __bsl_LoaderDesc_h

#include "bsl_Uart.h"
/*
typedef void (*VMPing)(void);
typedef char (*VMGetStatus)(void);
typedef void (*VMDownload)(void);
typedef void (*VMRun)(u8*);
typedef void (*VMReset)(void);
*/
typedef u8 (*VMLoad)(u8*);
//typedef void (*VMTx)(u8*);

typedef struct IVMLoaderDesc{
    /*
    VMPing p;
    VMGetStatus gs;
    VMDownload d;
    VMRun ru;
    VMReset re;
    */
    VMLoad l;
    //VMTx t;
} IVMLoaderDesc;

#endif