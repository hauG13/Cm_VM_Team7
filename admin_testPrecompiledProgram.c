/* admin.c - admin for the Cm Embedded Virtual Machine which:
//         - isolates the <stdio.h> with all put* in the VM
//         - defines _CRT_SECURE_NO_WARNINGS to avoid all MS secure crap on **_s
//
// Copyright (C) 1999-2020 by Michel de Champlain
//
*/
#include "hal.h"
#include "out.h"
#include "vm.h"

#ifdef Dos16
#define Target      "(Dos16)"
#elif defined(Arm7)
#define Target      "(Arm7)"
#else
#define Target      "(Win32)"
#endif


static u8 mem[] = { 0xE1, 0x00, 0x25, 0x71, 0xD5, 0x00, 0x2F, 0xFF, 0x85, 0xD5, 0x00, 0x44, 0xFF, 0x85,
0xD9, 0x09, 0xA8, 0xE0, 0x0E, 0xA0, 0x90, 0x1C, 0xE3, 0x04, 0xE0, 0x09, 0xA0, 0xB4, 0x00, 0xFF,
0x82, 0xE0, 0xF4, 0xFF, 0x87, 0x03, 0x04, 0xE7, 0xFF, 0xFF, 0xE7, 0xFF, 0xDB, 0x00, 0x54, 0x2E,
0x53, 0x74, 0x6D, 0x74, 0x00, 0x54, 0x65, 0x73, 0x74, 0x20, 0x31, 0x31, 0x3A, 0x20, 0x62, 0x72,
0x65, 0x61, 0x6B, 0x20, 0x53, 0x74, 0x61, 0x74, 0x65, 0x6D, 0x65, 0x6E, 0x74, 0x0A, 0x00, 0x39,
0x38, 0x37, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0x30, 0x0A, 0x00 };




int main(int argc, char* argv[]) {

//t VMOut_PutS("argv[0] = [%s]\n", argv[0]);
//t VMOut_PutS("argv[1] = [%s]\n", argv[1]);

    // Do Hal_Init() before any option messages.
    Hal_Init();
    VM_Init(mem);
    VM_execute(mem);
    
    return 0;
}
