/*
 * Copyright (C) 2021 Biren Patel
 * MIT License
 * Deprogram an arudino uno to a null state identified by cheeky morse code
 * on the builtin LED. This program demonstrates the wonders of macro hell.
 */

#define F_CPU (16000000UL)

#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>

#define UNIT    300
#define LED_HI  (PORTB = 1 << PORTB5)
#define LED_LO  (PORTB = 0)

#define PAUSE   do {LED_LO; _delay_ms(UNIT * 1);} while(0)
#define LETTER  do {LED_LO; _delay_ms(UNIT * 2);} while(0)
#define WORD    do {LED_LO; _delay_ms(UNIT * 6);} while(0)

#define DASH    do {LED_HI; _delay_ms(UNIT * 3); PAUSE;} while(0)
#define DOT     do {LED_HI; _delay_ms(UNIT * 1); PAUSE;} while(0)

int main(void) {
        /* builtin LED is on digital pin 13 */
        DDRB = 1 << DDB5;
        LED_LO;

        while (true) {
                /* send 'READY' */
                DOT; DASH; DOT; LETTER;
                DOT; LETTER;
                DOT; DASH; LETTER;
                DASH; DOT; DOT; LETTER;
                DASH; DOT; DASH; DASH; WORD;
        }

        return 0;
}
