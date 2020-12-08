#include "loader.h"
#include "_stdtype.h"
#include "out.h"
#define Status_Packet_Size 4
static u8 status[Status_Packet_Size];
static u32 byte_ctr;
static u32 size;
static u32 start_addr;
static u32 end_addr;



#define MaxPacketSize 11
#define MemMax 512
#define MemAllocated  (512+36)
u8    mem[MemMax];
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

/**
 * Set memory pointers and counters to default/base values & status array to Success
 */
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


static bool init = 0;
/**
 * Communication links with host serial loader. Waits for commands & load programs received from host into memory for the VM to execute
 */
u8 hal_Loader(u8* mainAddr){
    if(!init){
        Loader_Init();
        init = true;
    }
    u32 curr_byte;
    
    u8 i;
    while(1){ //Executes until a run command is received from the host serial loader
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
         Bsl_Send_Packet(Nak, (void *)0, 0 );
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
        status[0] = 0x03; //size
        status[1] = InvalidCmd; //checksum
        status[2] = InvalidCmd; //status
        Bsl_Send_Packet(Nak, (void *)0, 0 ); //Checksum doesn't match, means transmission failed, send Nak
        }
    */
   //Handle various possible commands sent from the host serial loader
    switch(packet[2]){
        case Ping:
            if(packet[1] != Ping){
                Bsl_Send_Packet(Nak, (void *)0, 0); //Failed checksum check, send Nak
            }else{
                Bsl_Send_Packet(Ack, (void *)0, 0);
            }
            break;
        case GetStatus:
            Bsl_Send_Packet(Ack, status, 0);
            break;
        case Download:;         
            u32 addr =  (((u32)packet[3] << 24) | ((u32)packet[4] << 16) | ((u32)packet[5] << 8)  | (u32)packet[6] );
            u32 pgm_size = ( ((u32)packet[7] << 24) | ((u32)packet[8] << 16) | ((u32)packet[9] << 8)  | (u32)packet[10] );
            if(pgm_size > MemAllocated){

            }else{
                //Override of memory location where program will be written to
                for(i = addr; i < pgm_size; i++){
                    mainAddr[i] = 0;  //Override of the memory area
                }

                start_addr = addr;
                end_addr = start_addr;
                Bsl_Send_Packet(Ack, (void *)0, 0); //Response to tell host packet was received properly and memory was cleared
            }
            break;
        case SendData:
                for(i = 3; i < size; i++){
                    mainAddr[end_addr++] = packet[i];
                }
                if((end_addr-start_addr) == pgm_size)
                    mainAddr[end_addr] = 0;
                Bsl_Send_Packet(Ack, (void *)0, 0); //Ack to notify current data packet was received successfully
            break;
        case Run:;
            //u32 p_addr =  (((u32)packet[3] << 24) | ((u32)packet[4] << 16) | ((u32)packet[5] << 8)  | (u32)packet[6] );
            // Send an Ack to tell the Host command was received successfully & code is now running
            Bsl_Send_Packet(Ack, (void *)0, 0);
            return Success; 
            break;
        case Reset:
            for(i = 0; i < end_addr; i++){
                mainAddr[i] = 0; //Reset memory, will be treated as a HALT opcode 
            }
            //Reset memory loader pointers 
            Loader_Init();
            // Send an Ack to tell the Host command was received successfully & code is now running
            Bsl_Send_Packet(Ack, (void *)0, 0);
            break;
        default:
            status[0] = 0x03;
            status[1] = UnknownCmd;
            status[2] = UnknownCmd;
            Bsl_Send_Packet(Nak, (void *)0, 0); //Unknown command, set status & wait
            break;
        }
    }
    return Success;
}



