/*******************************************************************************
* @file pb5.h
* @brief API for simply operating the arudino uno rev3 led as a debug tool.
* @author Copyright (C) 2021 Biren Patel.
* @license This project is released under the MIT License.
*******************************************************************************/

#ifndef PB5_H
#define PB5_H

/*******************************************************************************
* @function pb5_open
* @brief Configure pin B5 (arudino D13)
* @details If this open function fails internally, the builtin led will stay on.
*******************************************************************************/
void pb5_open(void);

/*******************************************************************************
* @function pb5_write
* @brief LED will flash according to input pattern. Function will not return.
* @details If this open function fails, the builtin led will rapidly flash.
* @param[in] pattern Each dibit from MSB -> LSB specifies the number of blinks
* to occur in one second. The entire pattern is performed over 4 seconds. e.g.,
* 0xB3 performs 2 blinks in second 1, 3 blinks in second 2, 0 blinks in second
* 3, and 3 blinks in second 4. This pattern repeatedly infinitely.
*******************************************************************************/
void pb5_write(const uint8_t pattern);

#endif /* PB5_H */
