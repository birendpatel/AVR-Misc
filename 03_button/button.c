/*
 * Copyright (C) 2021 Biren Patel
 * MIT License
 */

#include <stdbool.h>
#include <avr/io.h>

/*******************************************************************************
 * setup() - configure registers
 * @PD2: output, drive low
 * @PD3: input, pull up
 ******************************************************************************/
void setup(void) {
        DDRD = 1 << DDD2;
        PORTD = 1 << PORTD3;
}

/*******************************************************************************
 * main() - turn on the LED so long as the button is pressed
 ******************************************************************************/
int main(void) {
        setup();

        while (true) {
                //unlike PORTx, PINx is an input buffer provided for read ops
                //sfr_defs header also provides the bit_is_clear() macro
                if ((PIND & (1 << PIND3)) == false) {
                        PORTD |= 1 << PORTD2;
                }

                PORTD &= ~(1 << PORTD2);
        }

        return 0;
}
