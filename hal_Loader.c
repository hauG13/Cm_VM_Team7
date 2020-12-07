//#include "bsl_loaderdesc.h"
#include "loader.h"
#include "_stdtype.h"
#include "out.h"
//static ILoader vmLoader;
#define Status_Packet_Size 4
static u8 status[Status_Packet_Size];
static u32 byte_ctr;
static u32 size;
static u32 start_addr;
static u32 end_addr;
//void VMLoader_Init(ILoader loader){vmLoader = loader;}
/*
void VMLoader_Ping(void) {vmLoader->p(p);}
char VMLoader_GetStatus(void) {return vmLoader->gs(void);}
void VMLoader_Download(void) {vmLoader->d(void);}
void VMLoader_Run(u8* a) {vmLoader->ru(a);}
void VMLoader_Reset(void) {vmLoader->re(void);}
*/



#define MaxPacketSize 11
#define MemMax 512
#define MemAllocated  (512+36)
/*public*/ //static  u8     memAllocated[MemAllocated];

// To get the base RAM address on a memory segment increment.
static u8* GetBaseAddr(u8* memAddr, u32 memInc) {
    u32 a = (u32)memAddr + memInc;
    u32 m = memInc - 1U;
//t    VMOut_PutS("Admin: a = "); VMOut_PutX((u32)a); VMOut_PutN();
//t    VMOut_PutS("Admin: m = "); VMOut_PutX((u32)m); VMOut_PutN();

    u32 r = a & ~m;
//t    VMOut_PutS("Admin: r = "); VMOut_PutX((u32)r); VMOut_PutN();
    return (u8*)r;
} 

static void Loader_Init(void){
    byte_ctr = 0;
    status[0] = 0x03; //size
    status[1] = Success; //checksum
    status[2] = Success; //status
    status[3] = 0x00;
    start_addr = 0;
    end_addr = 0;
    size = 0;
}

static void Send_Packet(char AckOrNak, u8* packet, u8 packet_size){
    VMOut_PutC((char) AckOrNak);
     u8 i;
     for(i = 0; i < packet_size; i++){
         VMOut_PutX(packet[i]);
     }
     VMOut_PutC((char)0);
}

static bool init = 0;
u8 hal_Loader(u8* mainAddr){
    if(!init){
        //whichOne = 0;
        Loader_Init();
        init = true;
    }
    

    u32 curr_byte;
    
    u8 i;
    while(1){
        byte_ctr = 0;
        curr_byte = Bsl_Uart_Rx(); //Receive packet size
    while(curr_byte == 0){ curr_byte = Bsl_Uart_Rx();} //Receive packet size}
    u8 checksum = 0;
    size = curr_byte;//Receive packet size

    //if(size > MemMax){
   //     Send_Packet(Nak, (void *)0,0 );
        //Program too large to be executed, respond with a Nak
    //    status[1] = MemoryFail;
    //    status[2] = MemoryFail;
        // Send an Ack to tell the Host command was received successfully & code is now running
        /*
        VMOut_PutC((char)Nak);
        VMOut_PutC((char)0);
        */
  //  }

    u8 packet[size];
    packet[byte_ctr++] = curr_byte;
    packet[byte_ctr++] = Bsl_Uart_Rx(); //Receive Checksum
    packet[byte_ctr++] = Bsl_Uart_Rx(); //Receive command
    
    while(byte_ctr <  size){
        curr_byte = Bsl_Uart_Rx();
        packet[byte_ctr++] = curr_byte;
        checksum += curr_byte;
    }

    
    /*
    if((char)(checksum) != packet[1]){ 
        //status[0] = 0x03; //size
        //status[1] = InvalidCmd; //checksum
        //status[2] = InvalidCmd; //status
        Send_Packet(Nak, (void *)0, 0 ); //Checksum doesn't match, means transmission failed, send Nak
        //}
    */
    switch(packet[2]){
        case Ping:
            if(packet[1] != Ping){
                Send_Packet(Nak, (void *)0, 0);
            }else{
                Send_Packet(Ack, (void *)0, 0);
            }
            //return Success;
            break;
        case GetStatus:
            Send_Packet(Ack, status, 0);
            //return Success; 
            break;
        case Download:;         
            u32 addr =  (((u32)packet[3] << 24) | ((u32)packet[4] << 16) | ((u32)packet[5] << 8)  | (u32)packet[6] );
            u32 pgm_size = ( ((u32)packet[7] << 24) | ((u32)packet[8] << 16) | ((u32)packet[9] << 8)  | (u32)packet[10] );

            //Override of memory location where program will be written to
            for(i = addr; i < pgm_size; i++){
                mainAddr[i] = 0; 
            }
            //mainAddr = &memAllocated[addr]; //Move pointer to designated memory area
            //mainAddr = GetBaseAddr(memAllocated, pgm_size);
            //t VMOut_PutS("loadObjFile of size = %u\n", (u32)size);
            start_addr = addr;
            end_addr = start_addr;
            u8 i;
            /*
            for(i = 0; i < pgm_size; i++){
                memAllocated[i] = 0x00; //Override of the memory area
            }*/
            Send_Packet(Ack, (void *)0, 0); //No memory validations for now

            /*
            if(pgm_size > MemMax){ //Program to be sent is too big to be loaded into memory
                status[0] = 0x03; //size
                status[1] = MemoryFail; //checksum
                status[2] = MemoryFail; //status
            }*/
            
            break;
        case SendData:
        /*
            mem = GetBaseAddr(memAllocated, (u32)36UL);
            //Load program data into memory
            for(i = 3; i < size-1; i++){
                mainAddr[end_addr++] = packet[i];
            }
            // Send an Ack to tell the Host command was received successfully & code is now running
            VMOut_PutC((char)Ack);
            VMOut_PutC((char)0);
          */
        // if((char)(checksum) != packet[1]){ //Checksum 
          //  status[0] = 0x03; //size
           // status[1] = InvalidCmd; //checksum
           // status[2] = InvalidCmd; //status
            //Send_Packet(Nak, status,0 );
        //}else{
            //if(end_addr < pgm_size){
                for(i = 3; i < size; i++){
                    mainAddr[end_addr++] = packet[i];
                }
                if((end_addr-start_addr) == pgm_size)
                     mainAddr[end_addr] = 0;
                Send_Packet(Ack, (void *)0, 0); //Ack to notify current data packet was received successfully
            //}
            
        //}

            //return Success; 
            break;
        case Run:;
            u32 p_addr =  (((u32)packet[3] << 24) | ((u32)packet[4] << 16) | ((u32)packet[5] << 8)  | (u32)packet[6] );
            //mainAddr = &memAllocated[p_addr];
            // Send an Ack to tell the Host command was received successfully & code is now running
            Send_Packet(Ack, (void *)0, 0);
            return Success; 
            break;
        case Reset:
            // mainAddr[start_addr] = 0;
            
            for(i = 0; i < end_addr; i++){
                mainAddr[i] = 0; //Reset memory, will be treated as a HALT opcode 
            }
            //Reset memory loader
            Loader_Init();
            // Send an Ack to tell the Host command was received successfully & code is now running
            VMOut_PutC((char)Ack);
            VMOut_PutC((char)0);
            //return Success;
            break;
        default:
            VMOut_PutC((char)Ack);
            status[0] = 0x03;
            status[1] = UnknownCmd;
            status[2] = UnknownCmd;


            //return Success;
            break;
    }
    }
    

    return Success;
}

//void VMLoader_Tx(u8* packet) {vmLoader->t(packet);}
/*
ILoader Loader_GetFactory(const char* whichOne){
    if(!init){
        Loader_Init();
    }
}*/


