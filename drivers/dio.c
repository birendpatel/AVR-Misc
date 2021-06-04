/*******************************************************************************
 * @file dio.c
 * @brief Implementation of digital input/ouput driver for ATmega328P
 * @author Copyright (C) 2021 Biren Patel. This project is released under the
 * MIT License.
 ******************************************************************************/

#include <avr/io.h>
#include <avr/pgmspace.h>

#include "dio.h"

int main(void) {
        dio_open(PIN24, OUTPUT | HIGH);
        dio_open(PIN17, INPUT | PULLUP);
}
