/*
* Copyright (C) 2021 Biren Patel
* MIT License
* Double ended queue implementation
*/

#include "deque.h"

/******************************************************************************/

uint8_t deque_new(struct deque *dq, unsigned char *buf, const uint8_t cap)
{
        if (!buf) {
                return DEQUE_NULL_INPUT;
        }

        if (cap == 0) {
                return DEQUE_CAP_BOUNDS;
        }

        dq->cap = cap;
        dq->len = 0;
        dq->front = 0;
        dq->back = 0;
        dq->buf = buf;

        return DEQUE_SUCCESS;
}

/******************************************************************************
* place data at current index then increment
*/

uint8_t deque_push_back(struct deque *dq, const unsigned char data)
{
        if (!dq) {
                return DEQUE_NULL_INPUT;
        }

        if (deque_is_full(*dq)) {
                return DEQUE_FULL;
        }

        dq->buf[dq->back] = data;
        dq->back = (dq->back + 1) % dq->cap;
        dq->len++;

        return DEQUE_SUCESSS;
}

/******************************************************************************
* decrement index then get data
*/

uint8_t deque_pop_back(struct deque *dq, unsigned char *data)
{
        if (!dq || !data) {
                return DEQUE_NULL_INPUT;
        }

        if (deque_is_empty(*dq)) {
                return DEQUE_EMPTY;
        }

        dq->back = (dq->back + dq->cap - 1) % dq->cap;
        *data = dq->buf[dq->back];
        dq->len--;

        return DEQUE_SUCCESS;

}

/******************************************************************************
* decrement then place data
*/

uint8_t deque_push_front(struct deque *dq, const unsigned char data)
{
        if (!dq) {
                return DEQUE_NULL_INPUT;
        }

        if (deque_is_full(*dq)) {
                return DEQUE_FULL;
        }

        dq->front = (dq->front + dq->cap - 1) % dq->cap;
        dq->buf[dq->front] = data;
        dq->len++;

        return DEQUE_SUCCESS;
}

/******************************************************************************
* get data at current index then increment
*/

uint8_t deque_pop_front(struct deque *dq, unsigned char *data)
{
        if (!dq || !data) {
                return DEQUE_NULL_INPUT;
        }

        if (deque_is_empty(*dq)) {
                return DEQUE_EMPTY;
        }

        *data = dq->buf[dq->front];
        dq->front = (dq->front + 1) % dq->cap;
        dq->len--;

        return DEQUE_SUCCESS;
}
