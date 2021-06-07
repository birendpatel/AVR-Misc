/*******************************************************************************
* @file dio.c
* @brief Implementation of digital input/ouput driver for ATmega328P
* @author Copyright (C) 2021 Biren Patel.
* @license This project is released under the MIT License.
*******************************************************************************/

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "dio.h"

static uint8_t dio_open_entry(const uint8_t pin, const uint8_t mode);

/*******************************************************************************
* @struct name_attributes
* @brief Contains relevant register details for a given pin name
* @var name_attributes::pin_reg
*       @brief pointer to the associated PIN register
* @var name_attributes::mask
*       @brief bitmask over the PIN register. e.g., 1 << PINC3
* @var name_attributes::pos
*       @brief bit position within the PIN register. e.g., PINC3
*******************************************************************************/
typedef struct attributes {
        volatile uint8_t *const pin_reg;
        const uint8_t mask;
        const uint8_t pos;
} attributes;

/*******************************************************************************
* @var lookup
* @brief Lookup table to access the attributes associated with a given pin
* @details Due to_SFR_IO8() offsets on the ATmega328P, the data direction and
* port registers can be accessed via pointer arithmetic on the associated pin
* register. The flash table only needs a reference to the pin register because
* DDR = PIN + 1 and PORT = PIN + 2. This will free 46 bytes of flash memory.
*******************************************************************************/
static const attributes lookup[] PROGMEM = {
        /* Port B */
        [DIO_B0] = { &PINB, 1 << PINB0, PINB0 },
        [DIO_B1] = { &PINB, 1 << PINB1, PINB1 },
        [DIO_B2] = { &PINB, 1 << PINB2, PINB2 },
        [DIO_B3] = { &PINB, 1 << PINB3, PINB3 },
        [DIO_B4] = { &PINB, 1 << PINB4, PINB4 },
        [DIO_B5] = { &PINB, 1 << PINB5, PINB5 },
        [DIO_B6] = { &PINB, 1 << PINB6, PINB6 },
        [DIO_B7] = { &PINB, 1 << PINB7, PINB7 },

        /* Port C */
        [DIO_C0] = { &PINC, 1 << PINC0, PINC0 },
        [DIO_C1] = { &PINC, 1 << PINC1, PINC1 },
        [DIO_C2] = { &PINC, 1 << PINC2, PINC2 },
        [DIO_C3] = { &PINC, 1 << PINC3, PINC3 },
        [DIO_C4] = { &PINC, 1 << PINC4, PINC4 },
        [DIO_C5] = { &PINC, 1 << PINC5, PINC5 },
        [DIO_C6] = { &PINC, 1 << PINC6, PINC6 },

        /* Port D */
        [DIO_D0] = { &PIND, 1 << PIND0, PIND0 },
        [DIO_D1] = { &PIND, 1 << PIND1, PIND1 },
        [DIO_D2] = { &PIND, 1 << PIND2, PIND2 },
        [DIO_D3] = { &PIND, 1 << PIND3, PIND3 },
        [DIO_D4] = { &PIND, 1 << PIND4, PIND4 },
        [DIO_D5] = { &PIND, 1 << PIND5, PIND5 },
        [DIO_D6] = { &PIND, 1 << PIND6, PIND6 },
        [DIO_D7] = { &PIND, 1 << PIND7, PIND7 },
};

/*******************************************************************************
dio_open ensures that the DDR and PORT assignments happen atomically. We don't
want an interrupt to occur after the DDR assignment and before the PORT
assignment. These are edge scenarios where an interrupt doesn't use the DIO
interface and attempts to modify the same DDR as held in the current iteration.

The following path is unusual but has the unintended effect of engaging the D0
pullup resistor.

1. dio_open_entry() -> DDRD |= (1 << DDD0)
2. interrupt -> DDRD &= ~ (1 << DDD0)
3. dio_write() -> PORTD |= (1 << PORTD0)
*/

uint8_t dio_open(const dio_config *const table, const uint8_t n)
{
        uint8_t err = 0;
        uint8_t gei = 0;

        if (!table) {
                return DIO_ERR_NULL;
        }

        if (n == 0) {
                return DIO_ERR_VALUE;
        }

        for (uint8_t i = 0; i < n; i++) {
                dio_config entry = table[i];

                /* an ISR may execute between these instructions */

                gei = SREG >> 7;
                cli();

                err = dio_open_entry(entry.pin, entry.mode);

                if (err) {
                        goto fail;
                }

                err = dio_write(entry.pin, entry.value);

                if (err) {
                        goto fail;
                }

                SREG |= (gei << 7);
        }

        return DIO_SUCCESS;

fail:
        SREG |= (gei << 7);
        return err;
}

/******************************************************************************/

static uint8_t dio_open_entry(const uint8_t pin, const uint8_t mode)
{
        if (pin > DIO_D7) {
                return DIO_ERR_PIN;
        }

        attributes attr = {0};
        memcpy_P(&attr, &lookup[pin], sizeof(attributes));

        volatile uint8_t *const ddr_reg = attr.pin_reg + 1;

        switch (mode) {
                case INPUT:
                        *ddr_reg &= ~(attr.mask);
                        break;

                case OUTPUT:
                        *ddr_reg |= attr.mask;
                        break;

                default:
                        return DIO_ERR_MODE;
        }

        return DIO_SUCCESS;
}

/******************************************************************************/

uint8_t dio_write(const uint8_t pin, const uint8_t value)
{
        if (pin > DIO_D7) {
                return DIO_ERR_PIN;
        }

        attributes attr = {0};
        memcpy_P(&attr, &lookup[pin], sizeof(attributes));

        volatile uint8_t *const port_reg = attr.pin_reg + 2;

        switch (value) {
                case LOW:
                        *port_reg &= ~(attr.mask);
                        break;

                case HIGH: /* PULLUP on INPUT */
                        *port_reg |= attr.mask;
                        break;

                case TOGGLE:
                        *port_reg ^= attr.mask;
                        break;

                default:
                        return DIO_ERR_VALUE;
        }

        return DIO_SUCCESS;
}

/******************************************************************************/

uint8_t dio_read(const uint8_t pin, uint8_t *const value)
{
        if (pin > DIO_D7) {
                return DIO_ERR_PIN;
        }

        attributes attr = {0};
        memcpy_P(&attr, &lookup[pin], sizeof(attributes));

        *value = (uint8_t) ((*attr.pin_reg >> attr.pos) & 0x1);

        return DIO_SUCCESS;
}
