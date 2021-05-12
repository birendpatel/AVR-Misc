/*
 * Copyright (C) 2021 Biren Patel
 * MIT License
 * Blink an LED at a regular interval
 */

//inform the compiler of the CPU frequency.
//required for correct delay() behavior (see line 19)
//i'm on an arduino uno, which currently uses a 16 MHz external clock.
//on a stock avr chip, you'll have to read and decipher the fuse bits.
//note that on stock arduinos you cannot read or write fuse bits.
#define F_CPU (16000000UL)

//when we compile our source, avr-gcc will need a -mmcu flag which provides
//the device. The IO header includes IO definitions for all devices, and the
//-mmcu flag redirects to the correct IO header. Don't include the specific
//device header, because io.h also provides other functionality!
#include <avr/io.h>

//this is a high level library for busy-wait functionality. It lets us request
//delays in time rather than in # of cycles. This is why F_CPU needs to be
//carefully set. To use this library, we MUST pass an -Ox optimization flag.
#include <util/delay.h>

//if you've installed avr-libc, the standard C library is available!
#include <stdbool.h>

//sometimes you might see source which uses void main(void) instead.
//this stems from freestanding versus hosted c compiler implementations.
//avr-gcc will warn you when attempting to return void.
//in reality, mcu programming is typically event driven within an infinite loop,
//so the return is moot.
int main(void) {

        //ports are represented by registers inside a mcu.
        //DDRD is data direction register for port D.
        //a set bit indicates that the respective pin is configured for output.
        //on an arduino you'll have to compare pin configurations in the avr
        //data sheet to the arudino schematics. For example, arduino digital pin
        //8 on the Uno is configured in data direction register for port B via
        //pin B0.
        DDRD = (1 << PIND4);

        //when a bit is set in PORTD and the respective pin is configured for
        //output in the DD register, then the port pin is driven high. Here,
        //we configure all pins in port D to drive low. We really only care
        //about pinD4.
        //in other words, the value of DDR determines what the pin does, but the
        //value of PORTD determines what the *output* pin is currently doing.
        PORTD = 0;

        //event drive mcu programming
        while (true) {
                //xor toggle on port D causes pin D4 to be driven low if it
                //is currently driven high, and vise versa.
                PORTD ^= (1 << PIND4);

                //wait .1 seconds (provided F_CPU is correct) before toggling
                //the LED. This function actually takes a double!
                _delay_ms(1000);
        }

        return 0;
}
