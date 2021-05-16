/*
 * Copyright (C) 2021 Biren Patel
 * MIT License
 * Light an LED via a push button to ground.
 */

#include <stdbool.h>
#include <avr/io.h>

/*******************************************************************************
 * setup() - configure registers on reset
 * @PD2: output, drive low
 * @PD3: input, engage pull up resistor
 * @PB5: output, drive low (builtin LED on arduino uno)
 ******************************************************************************/
void setup(void) {
        /*
        No need to set PORTD2 to 0. For ATmega328p the datasheet specifies
        that it already has an initial value of 0. When we configure the pin
        for output, it drives low by default.
        */
        DDRD = 1 << DDD2;
        PORTD = 1 << PORTD3;

        /*
        Specifically for the arudino uno, the builtin LED defaults to input
        with the pull up resistor deactivated. But the op-amp buffer can power
        this LED. I choose to turn it off. In the future, we can toggle the
        LED to signal program states for debugging.
        */
        DDRB = 1 << DDB5;
}

/*******************************************************************************
 * main() - enable LED on PD2 when button on PD3 is pressed.
 ******************************************************************************/
int main(void) {
        setup();

        while (true) {
                /*
                PORTx is a write register, but PINx is a read register. In the
                setup, we enabled the pull up resistor on PD3. Therefore, 5V is
                presented to the input pin by default. If the button is pressed,
                0V is presented, and therefore the PINx register will read zero.
                This cues PD2 to branch and output 5V. Note, the sfr_defs header
                provides the bit_is_clear() macro to encapsulate the read op.
                */
                if ((PIND & (1 << PIND3)) == false) {
                        PORTD |= 1 << PORTD2;
                }

                PORTD &= ~(1 << PORTD2);
        }

        return 0;
}
