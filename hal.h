/* hal.h -- Hardware Abstraction Layer interface which decouples (or bridges)
//          the board support (machine dependent) modules to the VM portable code.
//
// Copyright (C) 1985-2020 by Michel de Champlain
//
*/

#ifndef __hal_h
#define __hal_h

#include "bsl_out.h"
#include "bsl_loader.h"

void Hal_Init(void);
#endif
