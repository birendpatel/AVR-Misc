# -*- MakeFile -*-
# Copyright (C) 2021 Biren Patel
# MIT License
# Build for unison.c

.PHONY: flash clean

#------------------------------------------------------------------------------#
# hardware
#------------------------------------------------------------------------------#
MEMOP = flash:w:unison.hex:i
DEVICE = ATmega328P
PORT = /dev/ttyACM0
TYPE = arduino

#------------------------------------------------------------------------------#
# compiler
#------------------------------------------------------------------------------#
CC = avr-gcc
CFLAGS = -O2 -mmcu=atmega328p -Wall -Werror -Wextra -Wpedantic
CFLAGS += -DF_CPU=16000000UL

IPATH = -I../drivers

vpath %.h ../drivers/
vpath %.c ../drivers/

#------------------------------------------------------------------------------#
# build
#------------------------------------------------------------------------------#
unison.hex: unison.bin
	avr-objcopy -v -O ihex $< $@

# note: important to place cflags here so that -mmcu flag is exposed to linker
unison.bin: dio.o unison.o
	$(CC) $(CFLAGS) $^ -o $@

unison.o: unison.c
	$(CC) $(CFLAGS) $(IPATH) -c $< -o $@

dio.o: dio.h

#------------------------------------------------------------------------------#
# programmer
#------------------------------------------------------------------------------#

flash: unison.hex
	avrdude -v -p $(DEVICE) -c $(TYPE) -P $(PORT) -U $(MEMOP)

#------------------------------------------------------------------------------#
# clean
#------------------------------------------------------------------------------#

clean:
	rm -f *.hex *.o *.bin
