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
* @brief Contains relevant registers details for a given pin name
* @var name_attributes::pin
*       @brief pointer to the PIN register
* @var name_attributes::mask
*       @brief bitmask over PIN register. e.g., 1 << PINC3
* @var name_attributes::pos
*       @brief bit position within PIN register. e.g., PINC3
*******************************************************************************/
struct name_attributes {
        volatile uint8_t *const pin;
        const uint8_t mask;
        const uint8_t pos;
};

/*******************************************************************************
* @var lookup
* @brief Lookup table to access registers associated with a given pin name
* @details On the ATmega328P due to_SFR_IO8() offsets, the data direction and
* port registers can be accessed via pointer arithmetic on the associated pin
* register. Therefore, the flash table need only contain a reference to the pin
* register. DDR = PIN + 1 and PORT = PIN + 2.
*******************************************************************************/
static const struct name_attributes lookup[] PROGMEM = {
        [PIN1]  = { &PINC, 1 << PINC6, PINC6 },
        [PIN2]  = { &PIND, 1 << PIND0, PIND0 },
        [PIN3]  = { &PIND, 1 << PIND1, PIND1 },
        [PIN4]  = { &PIND, 1 << PIND2, PIND2 },
        [PIN5]  = { &PIND, 1 << PIND3, PIND3 },
        [PIN6]  = { &PIND, 1 << PIND4, PIND4 },
        [PIN9]  = { &PINB, 1 << PINB6, PINB6 },
        [PIN10] = { &PINB, 1 << PINB7, PINB7 },
        [PIN11] = { &PIND, 1 << PIND5, PIND5 },
        [PIN12] = { &PIND, 1 << PIND6, PIND6 },
        [PIN13] = { &PIND, 1 << PIND7, PIND7 },
        [PIN14] = { &PINB, 1 << PINB0, PINB0 },
        [PIN15] = { &PINB, 1 << PINB1, PINB1 },
        [PIN16] = { &PINB, 1 << PINB2, PINB2 },
        [PIN17] = { &PINB, 1 << PINB3, PINB3 },
        [PIN18] = { &PINB, 1 << PINB4, PINB4 },
        [PIN19] = { &PINB, 1 << PINB5, PINB5 },
        [PIN23] = { &PINC, 1 << PINC0, PINC0 },
        [PIN24] = { &PINC, 1 << PINC1, PINC1 },
        [PIN25] = { &PINC, 1 << PINC2, PINC2 },
        [PIN26] = { &PINC, 1 << PINC3, PINC3 },
        [PIN27] = { &PINC, 1 << PINC4, PINC4 },
        [PIN28] = { &PINC, 1 << PINC5, PINC5 },
};

/*******************************************************************************
* @function get_name_attributes()
* @brief access struct name_attributes lookup table
* @param[in] name
* @param[out] n_attr contains valid reference only if DIO_SUCCESS is returned
* @return DIO_SUCCESS or DIO_LOOKUP
*******************************************************************************/
uint8_t get_name_attributes
(
        const uint8_t name,
        struct name_attributes *const n_attr
)
{
        if (pin > PD7) {
                return DIO_LOOKUP;
        }

        memcpy_P(n_attr, &lookup[name], sizeof(struct name_attributes));

        return DIO_SUCCESS;
}

/******************************************************************************/

uint8_t dio_open(const uint8_t name, const uint8_t mode)
{
        struct name_attributes n_attr;

        if (get_name_attributes(name, &n_attr) != DIO_SUCCESS) {
                return DIO_LOOKUP;
        }

        volatile uint8_t *ddr = n_attr.pin + 1;

        switch (mode) {
                case INPUT:
                        *ddr &= ~(n_attr.mask);
                        break;

                case OUTPUT:
                        *ddr |= n_attr.mask;
                        break;

                default:
                        return DIO_MODE;
        }

        return DIO_SUCCESS;
}

/******************************************************************************/

uint8_t dio_write(const uint8_t name, const uint8_t value)
{
        struct name_attributes n_attr;

        if (get_name_attributes(name, &n_attr) != DIO_SUCCESS) {
                return DIO_LOOKUP;
        }

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

                default:
                        return DIO_VALUE;
        }

        return DIO_SUCCESS;
}

/******************************************************************************/

uint8_t dio_read(const uint8_t name, uint8_t *const value)
{
        struct name_attributes n_attr;

        if (get_name_attributes(name, &n_attr) != DIO_SUCCESS) {
                return DIO_LOOKUP;
        }

        if (!value) {
                return DIO_NULL;
        }

        *value = (*n_attr.pin >> n_attr.pos) & 0x1;

        return DIO_SUCCESS;
}

/******************************************************************************/

uint8_t dio_toggle(const uint8_t name, uint8_t *const value)
{
        struct name_attributes n_attr;

        if (get_name_attributes(name, &n_attr) != DIO_SUCCESS) {
                return DIO_LOOKUP;
        }

        volatile uint8_t *port = n_attr.pin + 2;

        *port ^= n_attr.mask;

        if (value) {
                *value = (*port >> n_attr.pos) & 0x1;
        }

        return DIO_SUCCESS;
}
