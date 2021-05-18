# -*- MakeFile -*-
# Copyright (C) 2021 Biren Patel
# MIT License
# Build for toggle.c

CC = avr-gcc
CFLAGS = -O3 -mmcu=atmega328p -Wall -Werror -Wextra -Wpedantic
CFLAGS += -DF_CPU=16000000UL

MEMOP = flash:w:toggle.hex:i
DEVICE = ATmega328P
PORT = /dev/ttyACM0
TYPE = arduino

.PHONY: flash clean

toggle.hex: toggle.bin
	avr-objcopy -v -O ihex $< $@

toggle.bin: toggle.c
	$(CC) $(CFLAGS) -o $@ $<

flash: toggle.hex
	avrdude -v -p $(DEVICE) -c $(TYPE) -P $(PORT) -U $(MEMOP)

clean:
	rm -f ./toggle.bin ./toggle.hex
