#include "bsl_Uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void Bsl_Uart_Init(void){
    /*Set baud rate */
    UBRR0H = (unsigned char)(103>>8);
    UBRR0L = (unsigned char)103;
    /*Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0); //| (1 << RXCIE0) | (1 << TXCIE0);
    /* Set frame format: 8data, 1stop bit */
    UCSR0C = (3<<UCSZ00);
}

u8 Bsl_Uart_Rx(void){
    /* Wait for data to be received */
  while (!(UCSR0A & (1<<RXC0)));
  /* Get and return received data from buffer */
  return UDR0;
}

void Bsl_Uart_Tx(u8 data){
    /* Wait for empty transmit buffer */
  while (!(UCSR0A & (1<<UDRE0)));
  /* Put data into buffer, sends the data */
  UDR0 = data;
}

void Bsl_Send_Packet(u8* packet){
  while(*packet){
    Bsl_Uart_Tx(*packet++);
  }
  /*
  VMOut_PutC((char) AckOrNak);
  u8 i;
  for(i = 0; i < packet_size; i++){
      VMOut_PutX(packet[i]);
  }
  VMOut_PutC((char)0);
  */
}

u8* Bsl_Receive_Packet(void){
  u8 curr_byte, size, recv_ctr;
  u8* packet;
  curr_byte = Bsl_Uart_Rx(); //Receive packet size
  if(curr_byte != 0){
    recv_ctr = 0;
    size = curr_byte;
    packet = (u8*)malloc(size);
    packet[recv_ctr++] = size;
    do{
      packet[recv_ctr++] = Bsl_Uart_Rx();
    }while(curr_byte != 0);
  }
  return packet;
}