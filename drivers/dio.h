/*******************************************************************************
* @file dio.h
* @brief Digital input/ouput driver for ATmega328P
* @author Copyright (C) 2021 Biren Patel. This project is released under the
* MIT License.
* @details dio.h is a driver which encapsulates digital I/O operations similar
* to the arduino platform. For example, digitalWrite(3, HIGH) on the arduino
* translates to dio_write(PIN3, HIGH) within the dio.h API.
*******************************************************************************/

#ifndef DIO_H
#define DIO_H

/*******************************************************************************
* @def no_address
* @brief The no_address macro is a synonym for the C register keyword
* @details Why would anyone use the register keyword in the 21st century? Am I
* just a crazy fool? Maybe! I use register as a compile-time check. It's like
* the const keyword. Const offers an optimization benefit but it also lets the
* compiler inform me if the read-only contract was violated. Register does NOT
* offer an optimization benefit. However, it lets the compiler inform me if the
* local-scope no-references contract of a certain variable was violated. YMMV.
*******************************************************************************/
#ifndef no_address
        #define no_address register
#endif

/*******************************************************************************
* @def PIN0
* @brief Digital I/O pin map
* @details Every pin on the ATmega328P that may be configured for digital I/O
* has a corresponding pin macro. The user uses these pin macros to interface
* with the dio_* functions instead of performing operations directly on the
* DDRx, PORTx, and PINx registers.
*******************************************************************************/
#define PIN0    (uint8_t) 255   /**< NUL */
#define PIN1    (uint8_t) 0     /**< PC6 */
#define PIN2    (uint8_t) 1     /**< PD0 */
#define PIN3    (uint8_t) 2     /**< PD1 */
#define PIN4    (uint8_t) 3     /**< PD2 */
#define PIN5    (uint8_t) 4     /**< PD3 */
#define PIN6    (uint8_t) 5     /**< PD4 */
#define PIN9    (uint8_t) 6     /**< PB6 */
#define PIN10   (uint8_t) 7     /**< PB7 */
#define PIN11   (uint8_t) 8     /**< PD5 */
#define PIN12   (uint8_t) 9     /**< PD6 */
#define PIN13   (uint8_t) 10    /**< PD7 */
#define PIN14   (uint8_t) 11    /**< PB0 */
#define PIN15   (uint8_t) 12    /**< PB1 */
#define PIN16   (uint8_t) 13    /**< PB2 */
#define PIN17   (uint8_t) 14    /**< PB3 */
#define PIN18   (uint8_t) 15    /**< PB4 */
#define PIN19   (uint8_t) 16    /**< PB5 */
#define PIN23   (uint8_t) 17    /**< PC0 */
#define PIN24   (uint8_t) 18    /**< PC1 */
#define PIN25   (uint8_t) 19    /**< PC2 */
#define PIN26   (uint8_t) 20    /**< PC3 */
#define PIN27   (uint8_t) 21    /**< PC4 */
#define PIN28   (uint8_t) 22    /**< PC5 */

/*******************************************************************************
* @function dio_open
* @brief Configure a pin for either input or output
* @param[in] pin One of PIN1 thru PIN28
* @param[in] mode Either INPUT or OUTPUT
*******************************************************************************/
#define INPUT   0
#define OUTPUT  1

uint8_t dio_open (
        no_address const uint8_t pin,
        no_address const uint8_t mode
);

/*******************************************************************************
* @function dio_write
* @brief Drive an output pin or configure the pullup resistor on an input pin.
* @param[in] pin One of PIN1 thru PIN28
* @param[in] value One of HIGH, LOW, or PULLUP
*******************************************************************************/
#define HIGH    1
#define LOW     0
#define PULLUP  1

uint8_t dio_write (
        no_address const uint8_t pin,
        no_address const uint8_t value
);

#endif /* DIO_H */
