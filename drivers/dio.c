/*******************************************************************************
 * @file dio.c
 * @brief Implementation of digital input/ouput driver for ATmega328P
 * @author Copyright (C) 2021 Biren Patel.
 * @license This project is released under the MIT License.
 ******************************************************************************/

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
        [PB0] = { &PINB, 1 << PINB0, PINB0 },
        [PB1] = { &PINB, 1 << PINB1, PINB1 },
        [PB2] = { &PINB, 1 << PINB2, PINB2 },
        [PB3] = { &PINB, 1 << PINB3, PINB3 },
        [PB4] = { &PINB, 1 << PINB4, PINB4 },
        [PB5] = { &PINB, 1 << PINB5, PINB5 },
        [PB6] = { &PINB, 1 << PINB6, PINB6 },
        [PB7] = { &PINB, 1 << PINB7, PINB7 },

        /* Port C */
        [PC0] = { &PINC, 1 << PINC0, PINC0 },
        [PC1] = { &PINC, 1 << PINC1, PINC1 },
        [PC2] = { &PINC, 1 << PINC2, PINC2 },
        [PC3] = { &PINC, 1 << PINC3, PINC3 },
        [PC4] = { &PINC, 1 << PINC4, PINC4 },
        [PC5] = { &PINC, 1 << PINC5, PINC5 },
        [PC6] = { &PINC, 1 << PINC6, PINC6 },

        /* Port D */
        [PD0] = { &PIND, 1 << PIND0, PIND0 },
        [PD1] = { &PIND, 1 << PIND1, PIND1 },
        [PD2] = { &PIND, 1 << PIND2, PIND2 },
        [PD3] = { &PIND, 1 << PIND3, PIND3 },
        [PD4] = { &PIND, 1 << PIND4, PIND4 },
        [PD5] = { &PIND, 1 << PIND5, PIND5 },
        [PD6] = { &PIND, 1 << PIND6, PIND6 },
        [PD7] = { &PIND, 1 << PIND7, PIND7 },
};

/******************************************************************************/

uint8_t dio_open(const dio_config *const table, const uint8_t n)
{
        if (!table) {
                return DIO_ERR_NULL;
        }

        if (n == 0) {
                return DIO_ERR_VALUE;
        }

        for (uint8_t i = 0; i < n; i++) {
                uint8_t err = 0;
                dio_config entry = table[i];

                err = dio_open_entry(entry.pin, entry.mode);

                if (err) {
                        return err;
                }

                err = dio_write(entry.pin, entry.value);

                if (err) {
                        return err;
                }
        }

        return DIO_SUCCESS;
}

/******************************************************************************/

static uint8_t dio_open_entry(const uint8_t pin, const uint8_t mode)
{
        if (pin > PD7) {
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
        if (pin > PD7) {
                return DIO_ERR_PIN;
        }

        attributes attr = {0};
        memcpy_P(&attr, &lookup[pin], sizeof(attributes));

        volatile uint8_t *const port_reg = attr.pin + 2;

        switch (value) {
                case TOGGLE:
                        *port_reg ^= attr.mask;
                        break;

                case LOW:
                        *port_reg &= ~(attr.mask);
                        break;

                case PULLUP: /* fallthrough */
                case HIGH:
                        *port_reg |= attr.mask;
                        break;

                default:
                        return DIO_ERR_VALUE;
        }

        return DIO_SUCCESS;
}

/******************************************************************************/

uint8_t dio_read(const uint8_t pin, uint8_t *const value)
{
        if (pin > PD7) {
                return DIO_ERR_PIN;
        }

        attributes attr = {0};
        memcpy_P(&attr, &lookup[pin], sizeof(attributes));

        *value = (uint8_t) ((attr.pin >> attr.pos) & 0x1);

        return DIO_SUCCESS;
}
