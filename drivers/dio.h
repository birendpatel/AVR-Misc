/*******************************************************************************
 * @file dio.h
 * @brief Digital input/ouput driver for ATmega328P
 * @author Copyright (C) 2021 Biren Patel. This project is released under the
 * MIT License.
 * @details dio.h is a driver which encapsulates digital I/O operations similar
 * to the arduino platform. For example, digitalWrite(3, HIGH) on the arduino
 * translates to dio_write(PIN3, HIGH) within the dio.h API.
 ******************************************************************************/

#ifndef DIO_H
#define DIO_H

#define PIN0    0  /**< NUL - User may alter the macro name but not the value */
#define PIN1    1  /**< PC6 - User may alter the macro name but not the value */
#define PIN2    2  /**< PD0 - User may alter the macro name but not the value */
#define PIN3    3  /**< PD1 - User may alter the macro name but not the value */
#define PIN4    4  /**< PD2 - User may alter the macro name but not the value */
#define PIN5    5  /**< PD3 - User may alter the macro name but not the value */
#define PIN6    6  /**< PD4 - User may alter the macro name but not the value */
#define PIN9    7  /**< PB6 - User may alter the macro name but not the value */
#define PIN10   8  /**< PB7 - User may alter the macro name but not the value */
#define PIN11   9  /**< PD5 - User may alter the macro name but not the value */
#define PIN12   10 /**< PD6 - User may alter the macro name but not the value */
#define PIN13   11 /**< PD7 - User may alter the macro name but not the value */
#define PIN14   12 /**< PB0 - User may alter the macro name but not the value */
#define PIN15   13 /**< PB1 - User may alter the macro name but not the value */
#define PIN16   14 /**< PB2 - User may alter the macro name but not the value */
#define PIN17   15 /**< PB3 - User may alter the macro name but not the value */
#define PIN18   16 /**< PB4 - User may alter the macro name but not the value */
#define PIN19   17 /**< PB5 - User may alter the macro name but not the value */
#define PIN23   18 /**< PC0 - User may alter the macro name but not the value */
#define PIN24   19 /**< PC1 - User may alter the macro name but not the value */
#define PIN25   20 /**< PC2 - User may alter the macro name but not the value */
#define PIN26   21 /**< PC3 - User may alter the macro name but not the value */
#define PIN27   22 /**< PC4 - User may alter the macro name but not the value */
#define PIN28   23 /**< PC5 - User may alter the macro name but not the value */



#endif /* DIO_H */
