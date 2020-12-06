@if exist "vmport.o" del "vmport.o"
@if exist "vmport.hex" del "vmport.hex"
avr-gcc -Os -Wall -DF_CPU=16000000UL -mmcu=atmega328p -D IntegrationTest admin_testPrecompiledProgram.c vm.c vmstack.c hal.c hal_Out.c bsl_COut.c bsl_xtoa.c -o vmport.o
avr-objcopy -O ihex -j .text -j .data vmport.o  vmport.hex
avrdude -c arduino -p atmega328p -b 57600 -P COM5 -D -U flash:w:vmport.hex:i
pause