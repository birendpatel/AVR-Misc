/*******************************************************************************
* @file pb5.h
* @brief Operate the arudino uno rev3 led as a debug tool.
* @author Copyright (C) 2021 Biren Patel.
* @license This project is released under the MIT License.
*******************************************************************************/

#include <avr/io.h>
#include <util/delay.h>

#include "dio.h"
#include "pb5.h"

/******************************************************************************/

void pb5_open(void)
{
        uint8_t err = 0;

        dio_config table = {
                .pin = ARUDINO_D13,
                .mode = OUTPUT,
                .value = LOW
        };

        err = dio_open(table, 1);

        if (err) {
                DDRB |= (1 << DDB5);

                while (1) {
                        PORB ^= (1 << PORTB5);
                        _delay_ms(50);
                }
        }
}

/*******************************************************************************
function does not return. Just a straight unrolled loop over the pattern until
reset. There is of course some time overhead on the _delay_ms and dio_write
function calls, but for a human reading the debug LED for debug purposes the
microsecond drift accumulation is absolutely not a problem.
*/

void pb5_write(const uint8_t pattern)
{
        uint8_t cycle[4] = {
                [0] = pattern >> 6,
                [1] = (pattern >> 4) & 0x3,
                [2] = (pattern >> 2) & 0x3,
                [3] = pattern & 0x3
        };

loop:
        for (uint8_t i = 0; i < 4; i++) {
                switch (cycle[i]) {
                        case 0:
                                _delay_ms(1000);
                                break;
                        case 1:
                                dio_write(ARUDINO_D13, HIGH);
                                _delay_ms(100);
                                dio_write(ARDUINO_D13, LOW);
                                _delay_ms(900);
                                break;
                        case 2:
                                dio_write(ARDUINO_D13, HIGH);
                                _delay_ms(100);
                                dio_write(ARUDINO_D13, LOW);
                                _delay_ms(100);
                                dio_write(ARDUINO_D13, HIGH);
                                _delay_ms(100);
                                dio_write(ARUDINO_D13, LOW);
                                _delay_ms(700);
                                break;
                        case 3:
                                dio_write(ARDUINO_D13, HIGH);
                                _delay_ms(100);
                                dio_write(ARUDINO_D13, LOW);
                                _delay_ms(100);
                                dio_write(ARDUINO_D13, HIGH);
                                _delay_ms(100);
                                dio_write(ARUDINO_D13, LOW);
                                _delay_ms(100);
                                dio_write(ARDUINO_D13, HIGH);
                                _delay_ms(100);
                                dio_write(ARUDINO_D13, LOW);
                                _delay_ms(500);
                                break;
                }
        }

        goto loop;
}
