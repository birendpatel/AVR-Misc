# -*- MakeFile -*-
# Copyright (C) 2021 Biren Patel
# MIT License
# Build for echo.c

CC = avr-gcc
CFLAGS = -O3 -mmcu=atmega328p -Wall -Werror -Wextra -Wpedantic
CFLAGS += -DF_CPU=16000000UL -DBAUD_RATE=115200

MEMOP = flash:w:echo.hex:i
DEVICE = ATmega328P
PORT = /dev/ttyACM0
TYPE = arduino

.PHONY: flash clean

echo.hex: echo.bin
	avr-objcopy -v -O ihex $< $@

echo.bin: echo.c
	$(CC) $(CFLAGS) -o $@ $<

flash: echo.hex
	avrdude -v -p $(DEVICE) -c $(TYPE) -P $(PORT) -U $(MEMOP)

clean:
	rm -f ./echo.bin ./echo.hex
