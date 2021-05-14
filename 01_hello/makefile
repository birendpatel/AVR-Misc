# -*- MakeFile -*-
# Copyright (C) 2021 Biren Patel
# MIT License
# Build process for software on AVR devices (on Linux)

# First, we need a few new packages:
# sudo apt-get install avr-gcc avr-libc binutils-avr avrdude

CC = avr-gcc

# The mmcu flag is required for io.h header file.
# The -O optimization is the minimum level required for the delay functions.

CFLAGS = -O1 -mmcu=atmega328p -Wall -Werror -Wextra -Wpedantic

# It is often a good idea to separate the mcu write from the hex build.
# We'll use the phone flash rule to separate the two processes.

.PHONY: flash clean

# After we've compiled our source code using avr-gcc, we need to translate the
# binary format into a format that is suitable for our progrmmer. The -O ihex
# flag means we want to transform our binary into an output file with intel hex
# format.

hello.hex: hello.bin
	avr-objcopy -v -O ihex $< $@
	avr-size $@

# This is the starting point in the build dependency graph.
# The avr-size command is not too important. In fact, nothing is new here
# compared to typical C compilation on PC devices. However, the output file
# cannot be executed on your PC. I include the .bin extension as a mental note
# to myself that I'm working on an mcu build.

hello.bin: hello.c
	$(CC) $(CFLAGS) -o $@ $<
	avr-size $@

# This is the final step where we transfer the code and data inside our hex
# file onto the flash memory on the mcu. We'll use a programming for this, or
# optionally you don't need one if you have a bootloader currently on flash.
# There is an extremely helpful and detailed man page for avrdude. Read it!
# After you connect your device, you can infer the port via the dmesg command.
# The -U flag is tricky. Again, consult the man page. Here, -U essentialy says,
# "write to flash memory the contents of hello.hex which are in intel hex
# format".
# Sometimes you'll find invocations of avrdude that turn off verification and
# signature checks via -V -F. Don't do that! Also, remember that on a stock
# arduino the verbose output regarding the fuse bits is not correct. You need
# a programmer on the ICSP to read (and write) those fuse bits correctly.

MEMOP = flash:w:hello.hex:i
DEVICE = ATmega328P
PORT = /dev/ttyACM0
TYPE = arduino

flash: hello.hex
	avrdude -v -p $(DEVICE) -c $(TYPE) -P $(PORT) -U $(MEMOP)

clean:
	rm -f ./hello.bin ./hello.o ./hello.hex
