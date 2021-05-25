# -*- MakeFile -*-
# Copyright (C) 2021 Biren Patel
# MIT License
# Build for assets unit tests

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Wpedantic -Wnull-dereference
CFLAGS += -Wdouble-promotion -Wconversion -Wcast-qual
CFLAGS +=  -O1
CFLAGS += -ggdb
CFLAGS += -I../extern/unity/src/

vpath %.h ../extern/unity/src
vpath %.c ../extern/unity/src

UDIR = ../extern/unity/src/

.PHONY: clean run

#------------------------------------------------------------------------------#
# unity build
#------------------------------------------------------------------------------#

unity.o: unity.h unity_internals.h
	$(CC) -c -o $@ $(UDIR)unity.c

#------------------------------------------------------------------------------#
# test builds
#------------------------------------------------------------------------------#

test_deque: unity.o deque.o test_deque.o

test_deque.o: test_deque.c deque.h unity.h unity_internals.h

deque.o: deque.c deque.h

#------------------------------------------------------------------------------#
# phony
#------------------------------------------------------------------------------#

run:
	./test_deque

clean:
	rm -f *.o ./test_deque
