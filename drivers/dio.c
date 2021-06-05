/*******************************************************************************
 * @file dio.c
 * @brief Implementation of digital input/ouput driver for ATmega328P
 * @author Copyright (C) 2021 Biren Patel.
 * @license This project is released under the MIT License.
 ******************************************************************************/

#include <avr/io.h>
#include <avr/pgmspace.h>
#include "dio.h"

#define MAX_PIN_INDEX PD7

/*******************************************************************************
* @struct name_attributes
* @brief Contains relevant register details for a given pin name
* @var name_attributes::pin
*       @brief pointer to the associated PIN register
* @var name_attributes::mask
*       @brief bitmask over the PIN register. e.g., 1 << PINC3
* @var name_attributes::pos
*       @brief bit position within the PIN register. e.g., PINC3
*******************************************************************************/
struct name_attributes {
        volatile uint8_t *const pin;
        const uint8_t mask;
        const uint8_t pos;
};

/*******************************************************************************
* @var lookup
* @brief Lookup table to access attributes associated with a given pin name
* @details Due to_SFR_IO8() offsets on the ATmega328P, the data direction and
* port registers can be accessed via pointer arithmetic on the associated pin
* register. The flash table only needs a reference to the pin register because
* DDR = PIN + 1 and PORT = PIN + 2. This will free 46 bytes of flash memory.
*******************************************************************************/
static const struct name_attributes lookup[] PROGMEM = {
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

static inline struct name_attributes get_attr(const uint8_t name)
{
        struct name_attributes n_attr;

        memcpy_P(&n_attr, &lookup[name], sizeof(struct name_attributes));

        return n_attr;
}

/******************************************************************************/

uint8_t dio_open(const uint8_t name, const uint8_t mode)
{
        if (name > MAX_PIN_INDEX) {
                return DIO_LOOKUP;
        }

        if (mode > OUTPUT) {
                return DIO_MODE;
        }

        struct name_attributes n_attr = get_attr(name);

        volatile uint8_t *ddr = n_attr.pin + 1;

        switch (mode) {
                case INPUT:
                        *ddr &= ~(n_attr.mask);
                        break;

                case OUTPUT:
                        *ddr |= n_attr.mask;
                        break;
        }

        return DIO_SUCCESS;
}

/******************************************************************************/

uint8_t dio_write(const uint8_t name, const uint8_t value)
{
        if (name > MAX_PIN_INDEX) {
                return DIO_LOOKUP;
        }

        if (value > PULLUP) {
                return DIO_VALUE;
        }

        struct name_attributes n_attr = get_attr(name);

        volatile uint8_t *ddr = n_attr.pin + 1;
        volatile uint8_t *port = n_attr.pin + 2;

        switch (value) {
                case LOW:
                        if (*ddr & n_attr.mask) {
                                *port &= ~(n_attr.mask);
                                break;
                        }

                        return DIO_DRIVE;

                case HIGH:
                        if (*ddr & n_attr.mask) {
                                *port |= n_attr.mask;
                                break;
                        }

                        return DIO_DRIVE;

                case PULLUP:
                        if (*ddr & n_attr.mask == 0) {
                                port |= n_attr.mask;
                                break;
                        }

                        return DIO_PULLUP;
        }

        return DIO_SUCCESS;
}

/******************************************************************************/

uint8_t dio_read(const uint8_t name, uint8_t *const value)
{
        if (name > MAX_PIN_INDEX) {
                return DIO_LOOKUP;
        }

        if (value == NULL) {
                return DIO_NULL;
        }

        struct name_attributes n_attr = get_attr(name);

        *value = (*n_attr.pin >> n_attr.pos) & 0x1;

        return DIO_SUCCESS;
}

/******************************************************************************/

uint8_t dio_toggle(const uint8_t name)
{
        if (name > MAX_PIN_INDEX) {
                return DIO_LOOKUP;
        }

        struct name_attributes n_attr = get_attr(name);

        volatile uint8_t *port = n_attr.pin + 2;
        *port ^= n_attr.mask;

        return DIO_SUCCESS;
}
