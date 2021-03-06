/*
* Copyright (C) 2021 Biren Patel
* MIT License
*/

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#define NONE    ((uint8_t) 0x0)
#define GREEN   ((uint8_t) 0x1)
#define YELLOW  ((uint8_t) 0x2)
#define RED     ((uint8_t) 0x3)
#define WRAP    RED

#define SW1_PRESSED (!(PINB & (1 << PINB0)))

/*******************************************************************************
* setup() - configure registers
* @PD2: output, drive low
* @PD3: output, drive low
* @PD4: output, drive low
* @PB0: input, pull up
* @PB5: output, drive low
*******************************************************************************/
void setup(void) {
        DDRD = (1 << DDD2) | (1 << DDD3) | (1 << DDD4);
        DDRB = (1 << DDB5);
        PORTB = 1 << PORTB0;
        return;
}

/*******************************************************************************
* advance() - increment state with fast mod
*******************************************************************************/
void advance(uint8_t *prev) {
        *prev = (*prev + 1) & WRAP;
}

/*******************************************************************************
* trap() - demonstration of the debug led.
* If the fastmod in advance() was poorly implemented then the switch in main
* would fall back here into a do-nothing loop. Try changing WRAP to 0x7 and
* reflash to see it in action.
*******************************************************************************/
void trap(void) {
        PORTD = 0;

        while (1) {
                PORTB ^= 1 << PORTB5;
                _delay_ms(200);
        }
}

/*******************************************************************************
* main() - traffic light loop
* @flag: determines if SW1 has been released
* note: debounce is not implemented
*******************************************************************************/
int main(void) {
        uint8_t flag = 0;
        uint8_t state = NONE;

        setup();

        while (1) {
                if (SW1_PRESSED) {
                        if (flag == 0) {
                                advance(&state);

                                switch (state) {
                                case NONE:
                                        PORTD = 0;
                                        break;

                                case GREEN:
                                        PORTD = 1 << PORTD2;
                                        break;

                                case YELLOW:
                                        PORTD = 1 << PORTD3;
                                        break;

                                case RED:
                                        PORTD = 1 << PORTD4;
                                        break;

                                default:
                                        trap();
                                }

                                flag = 1;
                        }
                } else {
                        flag = 0;
                }
        }

        return 0;
}
