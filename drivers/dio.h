/*******************************************************************************
* @file dio.h
* @brief Digital I/O driver for the ATmega328P with SPDIP configuration.
* @author Copyright (C) 2021 Biren Patel.
* @license This project is released under the MIT License.
*******************************************************************************/

#ifndef DIO_H
#define DIO_H

/* error codes */
#define DIO_SUCCESS     (uint8_t) 0 /**< @brief Function was successful.      */
#define DIO_ERR_PIN     (uint8_t) 1 /**< @brief Input pin is invalid.         */
#define DIO_ERR_MODE    (uint8_t) 2 /**< @brief Input mode is invalid.        */
#define DIO_ERR_VALUE   (uint8_t) 3 /**< @brief Input value is invalid.       */
#define DIO_ERR_NULL    (uint8_t) 4 /**< @brief Input pointer is null.        */

/* API mode and value arguments */
#define INPUT   (uint8_t) 0
#define OUTPUT  (uint8_t) 1
#define LOW     (uint8_t) 0
#define HIGH    (uint8_t) 1
#define PULLUP  (uint8_t) 1
#define TOGGLE  (uint8_t) 2

/* digital I/O pins for the ATmega328P SPDIP pin configuration */
#define PB0 (uint8_t) 0
#define PB1 (uint8_t) 1
#define PB2 (uint8_t) 2
#define PB3 (uint8_t) 3
#define PB4 (uint8_t) 4
#define PB5 (uint8_t) 5
#define PB6 (uint8_t) 6
#define PB7 (uint8_t) 7
#define PC0 (uint8_t) 8
#define PC1 (uint8_t) 9
#define PC2 (uint8_t) 10
#define PC3 (uint8_t) 11
#define PC4 (uint8_t) 12
#define PC5 (uint8_t) 12
#define PC6 (uint8_t) 13
#define PD0 (uint8_t) 14
#define PD1 (uint8_t) 15
#define PD2 (uint8_t) 16
#define PD3 (uint8_t) 17
#define PD4 (uint8_t) 18
#define PD5 (uint8_t) 19
#define PD6 (uint8_t) 20
#define PD7 (uint8_t) 21

/* pin map for SPDIP physical layout */
#define PIN01 PC6
#define PIN02 PD0
#define PIN03 PD1
#define PIN04 PD2
#define PIN05 PD3
#define PIN06 PD4
#define PIN09 PB6
#define PIN10 PB7
#define PIN11 PD5
#define PIN12 PD6
#define PIN13 PD7
#define PIN14 PB0
#define PIN15 PB1
#define PIN16 PB2
#define PIN17 PB3
#define PIN18 PB4
#define PIN19 PB5
#define PIN23 PC0
#define PIN24 PC1
#define PIN25 PC2
#define PIN26 PC3
#define PIN27 PC4
#define PIN28 PC5

/* pin map for arduino uno rev3 */
#define ARDUINO_D00 PD0
#define ARDUINO_D01 PD1
#define ARDUINO_D02 PD2
#define ARDUINO_D03 PD3
#define ARDUINO_D04 PD4
#define ARDUINO_D05 PD5
#define ARDUINO_D06 PD6
#define ARDUINO_D07 PD7
#define ARDUINO_D08 PB0
#define ARDUINO_D09 PB1
#define ARDUINO_D10 PB2
#define ARDUINO_D11 PB3
#define ARDUINO_D12 PB4
#define ARDUINO_D13 PB5
#define ARDUINO_A00 PC0
#define ARDUINO_A01 PC1
#define ARDUINO_A02 PC2
#define ARDUINO_A03 PC3
#define ARDUINO_A04 PC4
#define ARDUINO_A05 PC5
#define ARDUINO_RST PC6

/*******************************************************************************
* @struct dio_config
* @brief Configurations for digital I/O pin setup.
* @var dio_config::pin
*       @brief Selected from the Px, PINx, or ARDUINOx macros
* @var dio_config::mode
*       @brief INPUT or OUTPUT
* @var dio_config::value
*       @brief LOW, HIGH, or PULLUP
*******************************************************************************/
typedef struct dio_config {
        uint8_t pin;
        uint8_t mode;
        uint8_t value;
} dio_config;

/*******************************************************************************
* @function dio_open
* @brief Configure pins for input or output and with an initial value
* @param[in] table
* @param[in] n total elements in table
*******************************************************************************/
uint8_t dio_open(const dio_config *const table, const uint8_t n);

/*******************************************************************************
* @function dio_write
* @brief Drive an output pin or configure the pullup resistor on an input pin.
* @param[in] pin
* @param[in] value One of HIGH, LOW, TOGGLE, or PULLUP
*******************************************************************************/
uint8_t dio_write(const uint8_t pin, const uint8_t value);

/*******************************************************************************
* @function dio_read
* @brief Read voltage on an input pin
* @param[in] name
* @param[out] val Either HIGH or LOW on successful return
*******************************************************************************/
uint8_t dio_read(const uint8_t pin, uint8_t *const value);

#endif /* DIO_H */
