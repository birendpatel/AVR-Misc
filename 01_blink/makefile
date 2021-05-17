# -*- MakeFile -*-
# Copyright (C) 2021 Biren Patel
# MIT License
# Requires avr-gcc, avr-libc, binutils-avr, and avrdude

CC = avr-gcc
CFLAGS = -O1 -mmcu=atmega328p -Wall -Werror -Wextra -Wpedantic

.PHONY: flash clean

# avr-gcc output must be transformed to intel hex format.
hello.hex: hello.bin
	avr-objcopy -v -O ihex $< $@
	avr-size $@

# the .bin extension is only a mental note identifying an mcu build
hello.bin: hello.c
	$(CC) $(CFLAGS) -o $@ $<
	avr-size $@

# transfer the code and adta inside hex file onto the mcu flash memory. -U says,
# "write to flash memory the contents of hello.hex which are in intel hex
# format". Note, on stock arduinos the fuse bits read by avrdude arent correct.
MEMOP = flash:w:hello.hex:i
DEVICE = ATmega328P
PORT = /dev/ttyACM0
TYPE = arduino

flash: hello.hex
	avrdude -v -p $(DEVICE) -c $(TYPE) -P $(PORT) -U $(MEMOP)

clean:
	rm -f ./hello.bin ./hello.o ./hello.hex
