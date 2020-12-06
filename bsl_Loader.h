#ifndef __bsl_loader_h
#define __bsl_loader_h

#include "bsl_stdtype.h"
#include "_stdtype.h"

    struct IVMLoaderDesc;
typedef struct IVMLoaderDesc* ILoader;

ILoader Loader_GetFactory(const char* whichOne);

#endif