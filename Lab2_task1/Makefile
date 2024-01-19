################################################################################
# Makefile for practical two                                                   #
# Author: Thomas Grunenberg                                                    #
################################################################################


all: main.hex

main.hex: main.elf
	avr-objcopy -O ihex main.elf main.hex

main.elf: main.o lcd.o
	avr-gcc -mmcu=atmega88pa -o main.elf main.o lcd.o

main.o: main.c
	avr-gcc -mmcu=atmega88pa -c -Os main.c

lcd.o: lcd.c lcd.h
	avr-gcc -mmcu=atmega88pa -c -Os lcd.c

program: main.hex
	avrdude -P /dev/ttyUSB_MySmartUSB -p m88p -c avr911 -Uflash:w:main.hex:i


# Clean ########################################################################
clean:
	rm -f *.o *.elf *.hex *~ *.bak
