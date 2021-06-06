/*******************************************************************************
* @file dio.c
* @brief Simple and quick demonstration of the digital I/O driver interface.
* @author Copyright (C) 2021 Biren Patel.
* @license This project is released under the MIT License.
*******************************************************************************/

#include <util/delay.h>
#include "dio.h"

void setup(void) {
        uint8_t err = 0;

        const dio_config table[8] = {
                [0] = {ARDUINO_D04, OUTPUT, LOW},
                [1] = {ARDUINO_D05, OUTPUT, HIGH},
                [2] = {ARDUINO_D06, OUTPUT, LOW},
                [3] = {ARDUINO_D07, OUTPUT, HIGH},
                [4] = {ARDUINO_D08, OUTPUT, LOW},
                [5] = {ARDUINO_D09, OUTPUT, HIGH},
                [6] = {ARDUINO_D10, OUTPUT, LOW},
                [7] = {ARDUINO_D11, OUTPUT, HIGH},
        }

        (void) dio_open(table, 8);
}

int main(void) {
        setup();

        while (1) {
                _delay_ms(1000);

                (void) dio_write(ARDUINO_D04, TOGGLE);
                (void) dio_write(ARDUINO_D05, TOGGLE);
                (void) dio_write(ARDUINO_D06, TOGGLE);
                (void) dio_write(ARDUINO_D07, TOGGLE);
                (void) dio_write(ARDUINO_D08, TOGGLE);
                (void) dio_write(ARDUINO_D09, TOGGLE);
                (void) dio_write(ARDUINO_D10, TOGGLE);
                (void) dio_write(ARDUINO_D11, TOGGLE);
        }

        return 0;
}
