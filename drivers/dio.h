/*******************************************************************************
* @file dio.h
* @brief Digital input/ouput driver for ATmega328P with SPDIP configuration
* @author Copyright (C) 2021 Biren Patel.
* @license This project is released under the MIT License.
* @details DIO is a driver which encapsulates digital I/O operations similar
* to the arduino platform. For example, digitalWrite(3, HIGH) on the arduino
* translates to dio_write(PIN3, HIGH) within the dio.h API.
*******************************************************************************/

#ifndef DIO_H
#define DIO_H

/* error codes */
#define DIO_SUCCESS     0 /**< @brief function returned successfully          */
#define DIO_LOOKUP      1 /**< @brief input pin argument does not exist       */
#define DIO_MODE        2 /**< @brief input mode argument is invalid          */
#define DIO_VALUE       3 /**< @brief input value argument is invalid         */
#define DIO_PULLUP      4 /**< @brief cannot engage pullup on output pin      */
#define DIO_DRIVE       5 /**< @brief cannot drive input pin high or low      */

/* api mode and value args */
#define INPUT   0
#define OUTPUT  1
#define LOW     0
#define HIGH    1
#define PULLUP  2

/* map: SPDIP physical layout to pin configurations */
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

/* map: pin configurations to digital I/O pin interface */
#define PIN1    PC6
#define PIN2    PD0
#define PIN3    PD1
#define PIN4    PD2
#define PIN5    PD3
#define PIN6    PD4
#define PIN9    PB6
#define PIN10   PB7
#define PIN11   PD5
#define PIN12   PD6
#define PIN13   PD7
#define PIN14   PB0
#define PIN15   PB1
#define PIN16   PB2
#define PIN17   PB3
#define PIN18   PB4
#define PIN19   PB5
#define PIN23   PC0
#define PIN24   PC1
#define PIN25   PC2
#define PIN26   PC3
#define PIN27   PC4
#define PIN28   PC5

/*******************************************************************************
* @function dio_open
* @brief Configure a pin for either input or output
* @param[in] pin One of PIN1 thru PIN28
* @param[in] mode Either INPUT or OUTPUT
* @return DIO_SUCCESS, DIO_MODE, or DIO_LOOKUP
*******************************************************************************/
uint8_t dio_open(uint8_t pin, uint8_t mode);

/*******************************************************************************
* @function dio_write
* @brief Drive an output pin or configure the pullup resistor on an input pin.
* @param[in] pin One of PIN1 thru PIN28
* @param[in] value One of HIGH, LOW, or PULLUP
* @return DIO_SUCCESS, DIO_LOOKUP, DIO_VALUE, DIO_PULLUP, or DIO_DRIVE
*******************************************************************************/
uint8_t dio_write(uint8_t pin, uint8_t value);

/*******************************************************************************
* @function dio_read
* @brief Read voltage on an input pin
* @param[in] pin One of PIN1 thru PIN28
* @param[out] value Either HIGH or LOW on successful return
* @return DIO_SUCCESS, DIO_VALUE, or DIO_LOOKUP
*******************************************************************************/
uint8_t dio_read(uint8_t pin, uint8_t *value);

/*******************************************************************************
* @function dio_toggle
* @brief Toggle a pin from HIGH to LOW or from LOW to HIGH
* @param[in] pin One of PIN1 thru PIN28
* @param[out] value Contains new pin status as either HIGH or LOW. May be NULL.
* @return DIO_SUCCESS or DIO_LOOKUP
*******************************************************************************/
uint8_t dio_toggle(uint8_t pin, uint8_t *value);

#endif /* DIO_H */
