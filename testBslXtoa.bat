@if exist "bsl_COut.hex" del "bsl_COut.hex"
@if exist "bsl_COut.o" del "bsl_COut.o"
avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p -D DebugXtoa bsl_COut.c bsl_xtoa.c -o bsl_COut.o
avr-objcopy -O ihex -j .text -j .data bsl_COut.o  bsl_COut.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM5 -D -U flash:w:bsl_COut.hex:i
pause
