/* hal.c -- Hardware Abstraction Layer implementation
//
// Copyright (C) 1985-2020 by Michel de Champlain
//
*/

#include "hal.h"
#include "out.h"
#include "loader.h"

void Hal_Init(void) {
    VMOut_Init(Out_GetFactory("console")); // "" to save space, later should be "console".
    //VMLoader_Init(Loader_GetFactory("loader"));
#ifdef FullVersion
    VMLoader_Init(Loader_GetFactory(""));
#endif
}
