#ifndef __bsl_uart_h
#define __bsl_uart_h

#include "bsl_stdtype.h"
#include "_stdtype.h"
#include <stdlib.h>

    struct IVMUartDesc;
typedef struct IVMUartDesc* IUart;

IUart Uart_GetFactory(const char* whichOne);

void Bsl_Uart_Init(void);
u8 Bsl_Uart_Rx(void);
void Bsl_Uart_Tx(u8);
void Bsl_Send_Packet(u8* packet);
u8* Bsl_Receive_Packet(void);
#endif