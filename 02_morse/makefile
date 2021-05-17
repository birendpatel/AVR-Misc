# -*- MakeFile -*-
# Copyright (C) 2021 Biren Patel
# MIT License
# Build for morse.c

CC = avr-gcc
CFLAGS = -O1 -mmcu=atmega328p -Wall -Werror -Wextra -Wpedantic
CFLAGS += -DF_CPU=16000000UL

MEMOP = flash:w:morse.hex:i
DEVICE = ATmega328P
PORT = /dev/ttyACM0
TYPE = arduino

.PHONY: flash

flash: morse.hex
	avrdude -v -p $(DEVICE) -c $(TYPE) -P $(PORT) -U $(MEMOP)
	rm -f ./morse.bin ./morse.hex


morse.hex: morse.bin
	avr-objcopy -v -O ihex $< $@

morse.bin: morse.c
	$(CC) $(CFLAGS) -o $@ $<
