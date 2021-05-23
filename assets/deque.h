/*
* Copyright (C) 2021 Biren Patel
* MIT License
* Double ended queue for unsigned char data. The deque is constructed over a
* pre-existing base array. Do not write to the base array while the deque is in
* use. The API functions do not use any dynamic allocation, but will work fine
* if malloc/custom_alloc is used to allocate the struct deque.
*/

#ifndef DEQUE_H
#define DEQUE_H

#include <stdint.h>

/*******************************************************************************
* API error codes
* @DEQUE_CAP_BOUNDS: attempted to initialize deque with zero capacity
* @DEQUE_NULL_INPUT: input argument is a null pointer
* @DEQUE_FULL: attempted to push data onto a full deque
* @DEQUE_EMPTY: attempted to pop data off an empty deque
*******************************************************************************/
#define DEQUE_SUCCESS           0
#define DEQUE_CAP_BOUNDS        (uint8_t) '1'
#define DEQUE_NULL_INPUT        (uint8_t) '2'
#define DEQUE_FULL              (uint8_t) '3'
#define DEQUE_EMPTY             (uint8_t) '4'

/*******************************************************************************
* struct deque
* @cap: maximum capacity
* @len: current size
* @front: index of front element
* @back: index of back element
* @buf: base array
* note: all struct deque members are READ-ONLY
*******************************************************************************/
struct deque {
        uint8_t cap;
        uint8_t len;
        uint8_t front;
        uint8_t back;
        unsigned char *buf;
};

/*******************************************************************************
* deque_new() - initialize double ended queue
* @buf: base array
* @cap: length of base array
* Returns: error code DEQUE_SUCCESS else DEQUE_CAP_BOUNDS or DEQUE_NULL_INPUT
* note: do not read/write directly to base array after deque_new returns
*******************************************************************************/
uint8_t deque_new(struct deque *dq, unsigned char *buf, const uint8_t cap);

/*******************************************************************************
* deque_push_back()
* Returns: error code DEQUE_SUCCESS else DEQUE_NULL_INPUT or DEQUE_FULL
*******************************************************************************/
uint8_t deque_push_back(struct deque *dq, const unsigned char data);

/*******************************************************************************
* deque_pop_back()
* Returns: error code DEQUE_SUCCESS else DEQUE_NULL_INPUT or DEQUE_EMPTY
*******************************************************************************/
uint8_t deque_pop_back(struct deque *dq, unsigned char *data);

/*******************************************************************************
* deque_push_front()
* Returns: error code DEQUE_SUCCESS else DEQUE_NULL_INPUT or DEQUE_FULL
*******************************************************************************/
uint8_t deque_push_front(struct deque *dq, const unsigned char data);

/*******************************************************************************
* deque_pop_front()
* Returns: error code DEQUE_SUCCESS else DEQUE_NULL_INPUT or DEQUE_EMPTY
*******************************************************************************/
uint8_t deque_pop_front(struct deque *dq, unsigned char *data);

/*******************************************************************************
* helper macros
*******************************************************************************/
#define deque_is_full(dq) ((dq).cap == (dq).len)
#define deque_is_not_full(dq) (!((dq).cap == (dq).len))

#define deque_is_empty(dq) ((dq).len == 0)
#define deque_is_not_empty(dq) (!((dq).len == 0))

#define deque_peek_back(dq) ((dq).buf[(dq).back])
#define deque_peek_front(dq) ((dq).buf[(dq).front])

#endif /* DEQUE_H */
