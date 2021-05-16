/*
 * Copyright (C) 2021 Biren Patel
 * MIT License
 * Light an LED via a push button to ground.
 */

#include <stdbool.h>
#include <avr/io.h>

/*******************************************************************************
 * setup() - configure registers
 * @PD2: output, drive low
 * @PD3: input, engage pull up resistor
 ******************************************************************************/
void setup(void) {
        DDRD = 1 << DDD2;
        PORTD = 1 << PORTD3;

        return;
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
                This cues PD2 to branch and output 5V.
                */
                if ((PIND & (1 << PIND3)) == false) {
                        PORTD |= 1 << PORTD2;
                }

                PORTD |= 0 << PORTD2;
        }

        return 0;
}
