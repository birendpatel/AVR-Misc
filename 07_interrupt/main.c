/*******************************************************************************
* @file main.c
* @brief Interrupt demonstration on INT0 vector.
* @author Copyright (C) 2021 Biren Patel.
* @license This project is released under the MIT License.
*******************************************************************************/

#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "dio.h"
#include "pb5.h"

#define INT_LED         ARDUINO_D01
#define BUTTON          ARDUINO_D02
#define POLL_LED        ARDUINO_D03

/******************************************************************************/

void setup_debugger(void) {
        pb5_open();
}

/******************************************************************************/
#define TABLE_SIZE 3

void setup_digital_io(void) {
        uint8_t err = 0;

        const dio_config table[TABLE_SIZE] = {
                [0] = {INT_LED, OUTPUT, LOW},
                [1] = {BUTTON, INPUT, PULLUP},
                [2] = {POLL_LED, OUTPUT, LOW}
        };

        err = dio_open(table, TABLE_SIZE);

        if (err) {
                pb5_write(0xF0);
        }
}

/*******************************************************************************
enable INT0 interrupt on falling edge
*/
void setup_interrupt(void) {
        cli();

        EIMSK |= 1 << INT0;
        EICRA |= (1 << ISC01);

        sei();
}

/******************************************************************************/

void setup(void) {
        setup_debugger();
        setup_digital_io();
        setup_interrupt();
}

/******************************************************************************/

volatile uint8_t err_state;

ISR(INT0_vect, ISR_BLOCK) {
        static uint8_t err;

        err = dio_write(INT_LED, TOGGLE);

        if (err) {
                err_state = 1;
        }
}

/******************************************************************************/

int main(void) {
        setup();

        while (1) {
                dio_write(POLL_LED, TOGGLE);
                _delay_ms(250);

                if (err_state) {
                        pb5_write(0xAA);
                }
        }

        return 0;
}
