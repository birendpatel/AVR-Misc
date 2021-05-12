# -*- MakeFile -*-
# Copyright (C) 2021 Biren Patel
# MIT License
# The compilation process for AVR devices is quite unusual compared to PCs!

# on linux we need a few new packages:
# sudo apt-get install avr-gcc avr-libc avrdude binutils-avr
CC = avr-gcc

#mmcu flag required for io.h header file, -O required for delay.h header
CFLAGS = -O1 -mmcu=atmega328p -Wall -Werror -Wextra -Wpedantic

#its often a good idea to separate the mcu write from the hex build
#so we'll use the flash rule to separate the two processes.
.PHONY: flash clean

#we need our binary to be transformed to intel hex format.
#-O ihex means we want to create an output file in intel hex format.
hello.hex: hello.bin
	avr-objcopy -v -O ihex $< $@
	avr-size $@

#step 1 in the build dependency graph.
#We create an executable as usual, nothing new here.
#you can create an object file first as usual for larger projects.
#you can't execute the program on your PC! the .bin extension on linux is
#of course not necessary, but I use it as a mental note for mcu makefiles.
hello.bin: hello.c
	$(CC) $(CFLAGS) -o $@ $<
	avr-size $@

#avrdude allows us to get our code and data onto the flash memory on the AVR
#using our programmer (or perhaps bootloader).
#avrdude has an extremely detailed and helpful man page!
#the port can be determined from dmesg when you plug in your programmer.
#-U is the tricky bit. Consult the man page! It says "write to flash memory
#the contents of hello.hex which are in intel hex format".
#sometimes you see people turn off verification and signature checks with -V -F.
#dont do that!!!
#remember if you're on a stock arduino, the verbose output regarding the fuse
#bits is not correct. You need a programmer on the ICSP to read the fuses.
MEMOP = flash:w:hello.hex:i
DEVICE = ATmega328P
PORT = /dev/ttyACM0
TYPE = arduino

flash: hello.hex
	avrdude -v -p $(DEVICE) -c $(TYPE) -P $(PORT) -U $(MEMOP)

clean:
	rm -f ./hello.bin ./hello.o ./hello.hex
