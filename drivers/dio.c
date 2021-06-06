/*******************************************************************************
 * @file dio.c
 * @brief Implementation of digital input/ouput driver for ATmega328P
 * @author Copyright (C) 2021 Biren Patel.
 * @license This project is released under the MIT License.
 ******************************************************************************/

#include <avr/io.h>
#include <avr/pgmspace.h>
#include "dio.h"

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
