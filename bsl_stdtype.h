#ifndef __bsl_stdtype_h
#define __bsl_stdtype_h

#define Success 0x40
#define UnknownCmd 0x41
#define InvalidCmd 0x42
#define InvalidAddr 0x43
#define MemoryFail 0x44

#define Ack 0xCC
#define Nak 0x33

#define Ping 0x20
#define GetStatus 0x23
#define Download 0x21
#define SendData 0x24
#define Run 0x22
#define Reset 0x25
#endif