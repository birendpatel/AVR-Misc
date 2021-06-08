# -*- MakeFile -*-
# Copyright (C) 2021 Biren Patel
# MIT License
# Build for main.c

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

MCU = -mmcu=atmega328p

CFLAGS = -O2 -Wall -Werror -Wextra -Wpedantic
CFLAGS += -DF_CPU=16000000UL
CFLAGS += $(MCU)

IPATH = -I../drivers

vpath %.h ../drivers/
vpath %.c ../drivers/

#------------------------------------------------------------------------------#
# build
#------------------------------------------------------------------------------#

main.hex: main.bin
	avr-objcopy -v -O ihex $< $@

main.bin: main.o dio.o pb5.o
	$(CC) $(MCU) $^ -o $@

main.o : main.c
	$(CC) $(CFLAGS) $(IPATH) -c $< -o $@

dio.o : dio.h

pb5.o : dio.h pb5.h

#------------------------------------------------------------------------------#
# programmer
#------------------------------------------------------------------------------#

flash: main.hex
	avrdude -v -p $(DEVICE) -c $(TYPE) -P $(PORT) -U $(MEMOP)

#------------------------------------------------------------------------------#
# clean
#------------------------------------------------------------------------------#

clean:
	rm -f *.hex *.o *.bin
