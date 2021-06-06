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
#define DIO_B0 (uint8_t) 0
#define DIO_B1 (uint8_t) 1
#define DIO_B2 (uint8_t) 2
#define DIO_B3 (uint8_t) 3
#define DIO_B4 (uint8_t) 4
#define DIO_B5 (uint8_t) 5
#define DIO_B6 (uint8_t) 6
#define DIO_B7 (uint8_t) 7
#define DIO_C0 (uint8_t) 8
#define DIO_C1 (uint8_t) 9
#define DIO_C2 (uint8_t) 10
#define DIO_C3 (uint8_t) 11
#define DIO_C4 (uint8_t) 12
#define DIO_C5 (uint8_t) 13
#define DIO_C6 (uint8_t) 14
#define DIO_D0 (uint8_t) 15
#define DIO_D1 (uint8_t) 16
#define DIO_D2 (uint8_t) 17
#define DIO_D3 (uint8_t) 18
#define DIO_D4 (uint8_t) 19
#define DIO_D5 (uint8_t) 20
#define DIO_D6 (uint8_t) 21
#define DIO_D7 (uint8_t) 22

/* pin map for SPDIP physical layout */
#define PIN01 DIO_C6
#define PIN02 DIO_D0
#define PIN03 DIO_D1
#define PIN04 DIO_D2
#define PIN05 DIO_D3
#define PIN06 DIO_D4
#define PIN09 DIO_B6
#define PIN10 DIO_B7
#define PIN11 DIO_D5
#define PIN12 DIO_D6
#define PIN13 DIO_D7
#define PIN14 DIO_B0
#define PIN15 DIO_B1
#define PIN16 DIO_B2
#define PIN17 DIO_B3
#define PIN18 DIO_B4
#define PIN19 DIO_B5
#define PIN23 DIO_C0
#define PIN24 DIO_C1
#define PIN25 DIO_C2
#define PIN26 DIO_C3
#define PIN27 DIO_C4
#define PIN28 DIO_C5

/* pin map for arduino uno rev3 */
#define ARDUINO_D00 DIO_D0
#define ARDUINO_D01 DIO_D1
#define ARDUINO_D02 DIO_D2
#define ARDUINO_D03 DIO_D3
#define ARDUINO_D04 DIO_D4
#define ARDUINO_D05 DIO_D5
#define ARDUINO_D06 DIO_D6
#define ARDUINO_D07 DIO_D7
#define ARDUINO_D08 DIO_B0
#define ARDUINO_D09 DIO_B1
#define ARDUINO_D10 DIO_B2
#define ARDUINO_D11 DIO_B3
#define ARDUINO_D12 DIO_B4
#define ARDUINO_D13 DIO_B5
#define ARDUINO_A00 DIO_C0
#define ARDUINO_A01 DIO_C1
#define ARDUINO_A02 DIO_C2
#define ARDUINO_A03 DIO_C3
#define ARDUINO_A04 DIO_C4
#define ARDUINO_A05 DIO_C5
#define ARDUINO_RST DIO_C6

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
