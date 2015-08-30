RM=rm -f
PORT=/dev/ttyUSB0

lcdnew.hex: lcdnew.elf
	avr-objcopy -O ihex lcdnew.elf lcdnew.hex


lcdnew.elf: lcdnew.o
	avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -o lcdnew.elf lcdnew.o

lcdnew.o: lcdnew.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o lcdnew.o lcdnew.c

install: lcdnew.hex
	avrdude -F -V -c arduino -p ATMEGA328P -P $(PORT) -b 57600 -U flash:w:lcdnew.hex
clean:
	$(RM) lcdnew.elf lcdnew.hex lcdnew.o
	
