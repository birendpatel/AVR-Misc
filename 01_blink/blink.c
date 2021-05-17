/*
 * Copyright (C) 2021 Biren Patel
 * MIT License
 */

//inform the compiler of the CPU frequency (via fuse bits or external clock)
#define F_CPU (16000000UL)

//-mmcu compiler flag gets device-specific io header from this generic header
#include <avr/io.h>

//high level inline functions for busy-wait in units of time rather than cycles
//requires -0x optimization and F_CPU
#include <util/delay.h>

//avr-libc
#include <stdbool.h>

int main(void) {
        //pins are grouped into ports. data direction registers (DDRx) identify
        //if a pin in port x is configure for input or output.
        DDRD = (1 << DDD4);

        //port registers (PORTx) are write buffers to drive pins high or low
        PORTD = 0;

        while (true) {
                //xor toggle
                PORTD ^= (1 << PORTD4);

                //100 is casted to double
                _delay_ms(100);
        }

        //unreachable
        return 0;
}
