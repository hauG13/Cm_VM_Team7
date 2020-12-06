/* _xtoa.h - 'to ascii' functions (xtoa): itoa, utoa, and ftoa (used only as private functions)
//
// Copyright (C) 1999-2020 by Michel de Champlain
//
*/

#ifndef __bsl_xtoa_h
#define __bsl_xtoa_h

#include "_stdtype.h"

void bsl_itoa(i32 i, char* buf);
void bsl_utoa(u32 n, char* buf, i8 next, u8 base);

#endif