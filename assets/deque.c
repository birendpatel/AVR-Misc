/*
* Copyright (C) 2021 Biren Patel
* MIT License
* Double ended queue implementation
*/

#include "deque.h"

/*******************************************************************************
* struct deque
* @cap: maximum deque capacity
* @len: total elements currently in deque
* @front: index to front element
* @back: index to back element
* @buf: base array
*******************************************************************************/
struct deque {
        uint8_t cap;
        uint8_t len;
        uint8_t front;
        uint8_t back;
        unsigned char *buf;
};

/******************************************************************************/
