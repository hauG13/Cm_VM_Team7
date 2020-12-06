/* hal_Loader.h -- Hardware Abstraction Layer interface which decouples (or bridges)
//          the board support (machine dependent) modules to the VM portable code.
//
*/

#ifndef __hal_loader_h
#define __hal_loader_h

#include "bsl_Uart.h"
u8 hal_Loader(u8* mainAddr);
#endif