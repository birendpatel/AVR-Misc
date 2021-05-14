/*
 * Copyright (C) 2021 Biren Patel
 * MIT License
 * Blink an LED at a regular interval
 */

/*
First ,we inform the compiler of the CPU frequency. This is required for correct
behavior of the _delay_ms() function called in main(). Typically, one must read
and decipher the fuse bits on the mcu to determine the frequency. I am on an
arduino uno for this example, and these boards use an external clock operating
at 16 MHz. Note: This macro only assists the compiler. It does not alter the
frequency of your mcu.
*/
#define F_CPU (16000000UL)

/*
When we later compile our source code, avr-gcc will need an -mmcu flag which
we pass to the compiler. This flag identifies the mcu device, and allows the
compiler to include IO header files specific to that device.
*/
#include <avr/io.h>

/*
This header exposes high level inline functions for busy-wait functionality. It
lets us request delays in units of time rather than in number of cycles. This
header only works correctly when we define F_CPU. Otherwise, the compiler will
default to a frequency that is almost surely incorrect. In addition, to use
this header we must pass an -Ox optimization flag to the compiler.
*/
#include <util/delay.h>

/*
If you have installed avr-libc, then the standard C library is available.
*/
#include <stdbool.h>

/*
Due to differences in freestanding versus hosted compilers, sometimes you might
see avr source code which uses 'void main(void)'. This triggers a warning.
Embedded programming is often event driven, so typically main() will employ an
infinite loop. Therefore, the return value is moot. However, we'll adhere by
NASA Power of Ten rules, so we'll use 'int main(void)'.
*/
int main(void) {
        /*
        Take a look at the pin config map on your mcu data sheet. Pins on the
        mcu are grouped into ports. Data direction registers (DDRx) are simply
        registers which identify whether a pin in port x is configured for
        input or output. I've hooked up an LED to PD4, so I want to configure
        the fourth bit on the data direction register for port D to output. On
        an arduino, you'll have to compare the pin configurations on the mcu to
        the arduino schematics and find out which digital pin that PD4 maps to.
        */
        DDRD = (1 << DDD4);

        /*
        Data direction registers only determine what a pin *can* do, but not
        what that pin *is* doing. When a pin has been configured for output,
        then the associated port output register (PORTx) controls whether that
        pin is being driven high (on) or low (off). Here, we configure all pins
        to drive low, although we really only care about PIND4, which is
        identified by the PORTD4 macro.
        */
        PORTD = 0;

        /*
        Event driven programming. In more sophisticated code, our mcu will be
        listening and responding to changes in its environment.
        */
        while (true) {
                /*
                Again, DDR registers specify what a pin can do, but PORT
                registers specifiy what they are doing. Here, we simply toggle
                the register contents at bit 4 (PORTD4) to switch between
                driving high and driving low.
                */
                PORTD ^= (1 << PORTD4);

                /*
                We request a wait for 100 milliseconds (0.1 seconds). This will
                only work correctly if F_CPU was defined accurately. Without
                this call, the loop will iterate so rapidly at 16 MHz that we
                won't be able to detect any changes in the LED status. Note that
                the _delay_ms argument is actually casted to a double.
                */
                _delay_ms(100);
        }

        return 0;
}
