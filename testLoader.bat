@if exist "hal_TestLoader.hex" del "hal_TestLoader.hex"
@if exist "hal_TestLoader.o" del "hal_TestLoader.o"
avr-gcc -Os -Wall -D ArduinoNano -DF_CPU=16000000UL -mmcu=atmega328p hal_TestLoader.c hal_Loader.c vm.c vmstack.c hal.c hal_Out.c bsl_Uart.c bsl_COut.c bsl_xtoa.c -o hal_TestLoader.o
avr-objcopy -O ihex -j .text -j .data hal_TestLoader.o  hal_TestLoader.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM5 -D -U flash:w:hal_TestLoader.hex:i
pause
