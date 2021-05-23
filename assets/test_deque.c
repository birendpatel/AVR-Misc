/*
* Copyright (C) 2021 Biren Patel
* MIT License
* Unit tests for double ended queue
*/

#include <stdint.h>

#include "deque.h"
#include "unity.h"

void test_new_deque_zero_capacity_returns_error(void) {
        //arrange
        struct deque dq;
        uint8_t err;
        unsigned char buf[] = {1, 2, 3};

        //act
        err = deque_new(&dq, buf, 0);

        //assert
        TEST_ASSERT_EQUAL(DEQUE_CAP_BOUNDS, err);
}

void test_new_deque_null_buffer_returns_error(void) {
        //arrange
        struct deque dq;
        uint8_t err;

        //act
        err = deque_new(&dq, NULL, 1);

        //assert
        TEST_ASSERT_EQUAL(DEQUE_NULL_INPUT, err);
}

void test_new_deque_with_legal_parameters_returns_success(void) {
        //arrange
        struct deque dq;
        uint8_t err;
        unsigned char buf[] = {1, 2, 3};

        //act
        err = deque_new(&dq, buf, sizeof(buf));

        //assert
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err);
}

int main(void)
{
        UNITY_BEGIN();
                RUN_TEST(test_new_deque_zero_capacity_returns_error);
                RUN_TEST(test_new_deque_null_buffer_returns_error);
                RUN_TEST(test_new_deque_with_legal_parameters_returns_success);
        return UNITY_END();
}
