/*
* Copyright (C) 2021 Biren Patel
* MIT License
* Double ended queue for unsigned chars, no dynamic allocation, O(1) amoritized
*
*
*     push front --> \                                    / <-- push back
*                     \                                  /
*                      \                                /
*                       -- FRONT [ ][ ][ ][ ][ ] BACK --
*                      /                |               \
*                     /                 |                \
*     pop front <--- /                  v                 \ ---> pop back
*                                      pos
*
*/

#ifndef DEQUE_H
#define DEQUE_H

#include <stdint.h>

typedef struct deque deque;

/*******************************************************************************
* deque_new() - initialize double ended queue
* @buf: base array on which the deque is constructed
* @cap: length of base array
* @pos: start index in base array, 0 <= pos < cap. if pos > cap then pos = cap
* @err: contains error code on return, possibly NULL
* Returns: deque and error code in @err if @err is not NULL
* note: do not read/write directly to base array after deque_new returns
*******************************************************************************/
deque deque_new(unsigned char *buf, const uint8_t cap, uint8_t pos, uint8_t *err);

/*******************************************************************************
* deque_push_back()
*******************************************************************************/
uint8_t deque_push_back(deque *d, const unsigned char data);

/*******************************************************************************
* deque_pop_back()
*******************************************************************************/
uint8_t deque_pop_back(deque *d, unsigned char *data);

/*******************************************************************************
* deque_push_front()
*******************************************************************************/
uint8_t deque_push_front(deque *d, const unsigned char data);

/*******************************************************************************
* deque_pop_front()
*******************************************************************************/
uint8_t deque_pop_front(deque *d, unsigned char *data);

#endif /* DEQUE_H */
