/*
* Copyright (C) 2021 Biren Patel
* MIT License
* Double ended queue for unsigned char data. The deque is constructed over a
* pre-existing base array. Do not write to the base array while the deque is in
* use. The API functions do not use any dynamic allocation, but if you want to
* malloc/custom_alloc the struct deque then the API will still work just fine.
*
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
* Returns: error codes 0 thru 2
* note: do not read/write directly to base array after deque_new returns
*******************************************************************************/
uint8_t deque_new(struct deque *d, unsigned char *buf, const uint8_t cap);

/*******************************************************************************
* deque_push_back()
*******************************************************************************/
uint8_t deque_push_back(struct deque *d, const unsigned char data);

/*******************************************************************************
* deque_pop_back()
*******************************************************************************/
uint8_t deque_pop_back(struct deque *d, unsigned char *data);

/*******************************************************************************
* deque_push_front()
*******************************************************************************/
uint8_t deque_push_front(struct deque *d, const unsigned char data);

/*******************************************************************************
* deque_pop_front()
*******************************************************************************/
uint8_t deque_pop_front(struct deque *d, unsigned char *data);

#endif /* DEQUE_H */
