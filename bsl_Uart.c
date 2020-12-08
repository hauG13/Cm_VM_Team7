#include "bsl_Uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/**
 * Initialize UART communication settings to communicate with 9600 baud, 8 data bit and 1 stop bit
 */
void Bsl_Uart_Init(void){
    /*Set baud rate */
    UBRR0H = (unsigned char)(103>>8);
    UBRR0L = (unsigned char)103;
    /*Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    /* Set frame format: 8data, 1stop bit */
    UCSR0C = (3<<UCSZ00);
}

/**
 * Receive a character through UART
 */
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

/**
 * Transmits a packet via UART precedded with an Ack or Nak, and ending with a 0 to comply with the packet format specifications
 */
void Bsl_Send_Packet(char ackOrNak, u8* packet, u8 packet_size){
  Bsl_Uart_Tx((char)ackOrNak);
  u8 i;

  for(i = 0; i < packet_size; i++){
      Bsl_Uart_Tx(packet[i]);
  }
  Bsl_Uart_Tx((char)0);
}
