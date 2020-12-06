#include "bsl_LoaderDesc.h"
#include "bsl_Uart.h"

#define MemMax        4096
#define MemAllocated  (4096+1024)
static u8 status[3];
extern  u8*   mem; // Need the memory address for the loader.
static u8 Loader_Load(u8* mainAddr){
    u8 packetReceived = 0;
    u8 curr_byte;
    u8 byte_ctr = 0;
    //u8* packet;
    while(!packetReceived){
        curr_byte = Bsl_Uart_Rx();
        mainAddr[0] = curr_byte;
        return Success;
        if(byte_ctr == 0){
            if (curr_byte > MemMax)
                return MemoryFail;
            //packet = (u8*)malloc(curr_byte);
        }
        if((curr_byte == 0x00) && (byte_ctr > 0)){
            packetReceived = 1;
            break;
        }
        mainAddr[byte_ctr++] = curr_byte;
    }
    return Success;
    switch(mainAddr[2]){
        case Ping: 
            if(mainAddr[1] == Ping) //checksum for ping is the ping itself
            {
                
                status[0] = 0x03; //size
                status[1] = Success; //checksum
                status[2] = Success; //status
                return Success;
            }else
            {
                //Something went wrong, send  Nack
                return Nak;
            }
        default:
            return Success;
    }

    return Success;
}


static IVMLoaderDesc loader = {
    Loader_Load//,
    //Loader_Tx
    /*
    Loader_Ping,
    Loader_GetStatus,
    Loader_Run,
    Loader_Reset
    */
};

static bool init = 0;
ILoader Loader_GetFactory(const char* whichOne){
    if(!init){
        whichOne = 0;
        init = true;       
    }

    return &loader;
}