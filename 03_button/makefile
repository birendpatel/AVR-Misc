# -*- MakeFile -*-
# Copyright (C) 2021 Biren Patel
# MIT License
# Build for button.c

CC = avr-gcc
CFLAGS = -O1 -mmcu=atmega328p -Wall -Werror -Wextra -Wpedantic
CFLAGS += -DF_CPU=16000000UL

MEMOP = flash:w:button.hex:i
DEVICE = ATmega328P
PORT = /dev/ttyACM0
TYPE = arduino

.PHONY: flash clean

button.hex: button.bin
	avr-objcopy -v -O ihex $< $@

button.bin: button.c
	$(CC) $(CFLAGS) -o $@ $<

flash: button.hex
	avrdude -v -p $(DEVICE) -c $(TYPE) -P $(PORT) -U $(MEMOP)

clean:
	rm -f ./button.bin ./button.hex
