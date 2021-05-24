# -*- MakeFile -*-
# Copyright (C) 2021 Biren Patel
# MIT License
# Build for echo.c

.PHONY: flash clean teletype

#------------------------------------------------------------------------------#
# hardware
#------------------------------------------------------------------------------#
MEMOP = flash:w:echo.hex:i
DEVICE = ATmega328P
PORT = /dev/ttyACM0
TYPE = arduino
BAUD_RATE = 9600

#------------------------------------------------------------------------------#
# compiler
#------------------------------------------------------------------------------#
CC = avr-gcc
CFLAGS = -O3 -mmcu=atmega328p -Wall -Werror -Wextra -Wpedantic
DEFS = -DF_CPU=16000000UL -DBAUD=$(BAUD_RATE)UL
IPATH = -I../assets/

vpath %.c ../assets/
vpath %.h ../assets/

#------------------------------------------------------------------------------#
# build
#------------------------------------------------------------------------------#
echo.hex: echo.bin
	avr-objcopy -v -O ihex $< $@

echo.bin: echo.o deque.o
	$(CC) $^ -o $@

echo.o: echo.c deque.h
	$(CC) $(CFLAGS) -c $(DEFS) $(IPATH) $< -o $@

deque.o: deque.h

#------------------------------------------------------------------------------#
# programmer
#------------------------------------------------------------------------------#
flash: echo.hex
	avrdude -v -p $(DEVICE) -c $(TYPE) -P $(PORT) -U $(MEMOP)

#------------------------------------------------------------------------------#
# utilities
#------------------------------------------------------------------------------#
clean:
	rm -f ./echo.bin ./echo.hex *.o

teletype:
	stty -F $(PORT) $(BAUD_RATE) ixon
