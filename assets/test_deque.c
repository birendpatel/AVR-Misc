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

void test_max_push_back_then_pop_back_returns_correct_data(void) {
        //arrange
        struct deque dq;
        uint8_t err_0;
        uint8_t err_1;
        uint8_t err_2;
        unsigned char data;
        unsigned char buf[255];

        //act
        err_0 = deque_new(&dq, buf, sizeof(buf));
        err_1 = deque_push_back(&dq, 42);
        err_2 = deque_pop_back(&dq, &data);

        //assert
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_0);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_1);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_2);
        TEST_ASSERT_EQUAL_INT(42, data);
}

void test_max_push_front_then_pop_front_returns_correct_data(void) {
        //arrange
        struct deque dq;
        uint8_t err_0;
        uint8_t err_1;
        uint8_t err_2;
        unsigned char data;
        unsigned char buf[255];

        //act
        err_0 = deque_new(&dq, buf, sizeof(buf));
        err_1 = deque_push_front(&dq, 42);
        err_2 = deque_pop_front(&dq, &data);

        //assert
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_0);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_1);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_2);
        TEST_ASSERT_EQUAL_INT(42, data);
}

void test_max_push_back_then_pop_front_returns_correct_data(void) {
        //arrange
        struct deque dq;
        uint8_t err_0;
        uint8_t err_1;
        uint8_t err_2;
        unsigned char data;
        unsigned char buf[255];

        //act
        err_0 = deque_new(&dq, buf, sizeof(buf));
        err_1 = deque_push_back(&dq, 42);
        err_2 = deque_pop_front(&dq, &data);

        //assert
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_0);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_1);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_2);
        TEST_ASSERT_EQUAL_INT(42, data);
}

void test_max_push_front_then_pop_back_returns_correct_data(void) {
        //arrange
        struct deque dq;
        uint8_t err_0;
        uint8_t err_1;
        uint8_t err_2;
        unsigned char data;
        unsigned char buf[255];

        //act
        err_0 = deque_new(&dq, buf, sizeof(buf));
        err_1 = deque_push_front(&dq, 42);
        err_2 = deque_pop_back(&dq, &data);

        //assert
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_0);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_1);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_2);
        TEST_ASSERT_EQUAL_INT(42, data);
}

void test_singleton_push_back_then_pop_back_returns_correct_data(void) {
        //arrange
        struct deque dq;
        uint8_t err_0;
        uint8_t err_1;
        uint8_t err_2;
        unsigned char data;
        unsigned char buf[1];

        //act
        err_0 = deque_new(&dq, buf, sizeof(buf));
        err_1 = deque_push_back(&dq, 42);
        err_2 = deque_pop_back(&dq, &data);

        //assert
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_0);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_1);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_2);
        TEST_ASSERT_EQUAL_INT(42, data);
}

void test_singleton_push_front_then_pop_front_returns_correct_data(void) {
        //arrange
        struct deque dq;
        uint8_t err_0;
        uint8_t err_1;
        uint8_t err_2;
        unsigned char data;
        unsigned char buf[1];

        //act
        err_0 = deque_new(&dq, buf, sizeof(buf));
        err_1 = deque_push_front(&dq, 42);
        err_2 = deque_pop_front(&dq, &data);

        //assert
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_0);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_1);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_2);
        TEST_ASSERT_EQUAL_INT(42, data);
}

void test_singleton_push_back_then_pop_front_returns_correct_data(void) {
        //arrange
        struct deque dq;
        uint8_t err_0;
        uint8_t err_1;
        uint8_t err_2;
        unsigned char data;
        unsigned char buf[1];

        //act
        err_0 = deque_new(&dq, buf, sizeof(buf));
        err_1 = deque_push_back(&dq, 42);
        err_2 = deque_pop_front(&dq, &data);

        //assert
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_0);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_1);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_2);
        TEST_ASSERT_EQUAL_INT(42, data);
}

void test_singleton_push_front_then_pop_back_returns_correct_data(void) {
        //arrange
        struct deque dq;
        uint8_t err_0;
        uint8_t err_1;
        uint8_t err_2;
        unsigned char data;
        unsigned char buf[1];

        //act
        err_0 = deque_new(&dq, buf, sizeof(buf));
        err_1 = deque_push_front(&dq, 42);
        err_2 = deque_pop_back(&dq, &data);

        //assert
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_0);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_1);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_2);
        TEST_ASSERT_EQUAL_INT(42, data);
}

void test_mid_push_back_then_pop_back_returns_correct_data(void) {
        //arrange
        struct deque dq;
        uint8_t err_0;
        uint8_t err_1;
        uint8_t err_2;
        unsigned char data;
        unsigned char buf[129];

        //act
        err_0 = deque_new(&dq, buf, sizeof(buf));
        err_1 = deque_push_back(&dq, 42);
        err_2 = deque_pop_back(&dq, &data);

        //assert
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_0);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_1);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_2);
        TEST_ASSERT_EQUAL_INT(42, data);
}

void test_mid_push_front_then_pop_front_returns_correct_data(void) {
        //arrange
        struct deque dq;
        uint8_t err_0;
        uint8_t err_1;
        uint8_t err_2;
        unsigned char data;
        unsigned char buf[129];

        //act
        err_0 = deque_new(&dq, buf, sizeof(buf));
        err_1 = deque_push_front(&dq, 42);
        err_2 = deque_pop_front(&dq, &data);

        //assert
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_0);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_1);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_2);
        TEST_ASSERT_EQUAL_INT(42, data);
}

void test_mid_push_back_then_pop_front_returns_correct_data(void) {
        //arrange
        struct deque dq;
        uint8_t err_0;
        uint8_t err_1;
        uint8_t err_2;
        unsigned char data;
        unsigned char buf[129];

        //act
        err_0 = deque_new(&dq, buf, sizeof(buf));
        err_1 = deque_push_back(&dq, 42);
        err_2 = deque_pop_front(&dq, &data);

        //assert
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_0);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_1);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_2);
        TEST_ASSERT_EQUAL_INT(42, data);
}

void test_mid_push_front_then_pop_back_returns_correct_data(void) {
        //arrange
        struct deque dq;
        uint8_t err_0;
        uint8_t err_1;
        uint8_t err_2;
        unsigned char data;
        unsigned char buf[129];

        //act
        err_0 = deque_new(&dq, buf, sizeof(buf));
        err_1 = deque_push_front(&dq, 42);
        err_2 = deque_pop_back(&dq, &data);

        //assert
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_0);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_1);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_2);
        TEST_ASSERT_EQUAL_INT(42, data);
}

void test_push_back_on_full_array_returns_error(void) {
        //arrange
        struct deque dq;
        uint8_t err_0;
        uint8_t err_1;
        uint8_t err_2;
        unsigned char buf[1];

        //act
        err_0 = deque_new(&dq, buf, sizeof(buf));
        err_1 = deque_push_back(&dq, 42);
        err_2 = deque_push_back(&dq, 52);

        //assert
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_0);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_1);
        TEST_ASSERT_EQUAL(DEQUE_FULL, err_2);
}

void test_push_front_on_full_array_returns_error(void) {
        //arrange
        struct deque dq;
        uint8_t err_0;
        uint8_t err_1;
        uint8_t err_2;
        unsigned char buf[1];

        //act
        err_0 = deque_new(&dq, buf, sizeof(buf));
        err_1 = deque_push_front(&dq, 42);
        err_2 = deque_push_front(&dq, 52);

        //assert
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_0);
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_1);
        TEST_ASSERT_EQUAL(DEQUE_FULL, err_2);
}

void test_pop_back_on_empty_array_returns_error(void) {
        //arrange
        struct deque dq;
        uint8_t err_0;
        uint8_t err_1;
        unsigned char data;
        unsigned char buf[1];

        //act
        err_0 = deque_new(&dq, buf, sizeof(buf));
        err_1 = deque_pop_back(&dq, &data);

        //assert
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_0);
        TEST_ASSERT_EQUAL(DEQUE_EMPTY, err_1);
}

void test_pop_front_on_empty_array_returns_error(void) {
        //arrange
        struct deque dq;
        uint8_t err_0;
        uint8_t err_1;
        unsigned char data;
        unsigned char buf[1];

        //act
        err_0 = deque_new(&dq, buf, sizeof(buf));
        err_1 = deque_pop_front(&dq, &data);

        //assert
        TEST_ASSERT_EQUAL(DEQUE_SUCCESS, err_0);
        TEST_ASSERT_EQUAL(DEQUE_EMPTY, err_1);
}

void test_deque_made_empty_is_truly_empty_via_pop_back(void) {
        //arrange
        struct deque dq;
        uint8_t err;
        unsigned char data;
        unsigned char buf[2];

        //act
        deque_new(&dq, buf, sizeof(buf));
        deque_push_back(&dq, 42);
        deque_push_back(&dq, 52);
        deque_pop_back(&dq, &data);
        deque_pop_back(&dq, &data);
        err = deque_pop_back(&dq, &data);

        //assert
        TEST_ASSERT_EQUAL(DEQUE_EMPTY, err);
}

void test_deque_made_empty_is_truly_empty_via_pop_front(void) {
        //arrange
        struct deque dq;
        uint8_t err;
        unsigned char data;
        unsigned char buf[2];

        //act
        deque_new(&dq, buf, sizeof(buf));
        deque_push_back(&dq, 42);
        deque_push_back(&dq, 52);
        deque_pop_front(&dq, &data);
        deque_pop_front(&dq, &data);
        err = deque_pop_front(&dq, &data);

        //assert
        TEST_ASSERT_EQUAL(DEQUE_EMPTY, err);
}

void test_macro_deque_is_full(void) {
        //arrange
        struct deque dq;
        unsigned char buf[2];

        //act
        deque_new(&dq, buf, sizeof(buf));
        deque_push_back(&dq, 42);
        deque_push_back(&dq, 52);

        //assert
        TEST_ASSERT_TRUE(deque_is_full(dq));
}

void test_macro_deque_is_not_full(void) {
        //arrange
        struct deque dq;
        unsigned char buf[2];

        //act
        deque_new(&dq, buf, sizeof(buf));
        deque_push_back(&dq, 42);

        //assert
        TEST_ASSERT_TRUE(deque_is_not_full(dq));
}

void test_macro_deque_is_empty(void) {
        //arrange
        struct deque dq;
        unsigned char buf[2];

        //act
        deque_new(&dq, buf, sizeof(buf));

        //assert
        TEST_ASSERT_TRUE(deque_is_empty(dq));
}

void test_macro_deque_is_not_empty(void) {
        //arrange
        struct deque dq;
        unsigned char buf[2];

        //act
        deque_new(&dq, buf, sizeof(buf));
        deque_push_back(&dq, 42);

        //assert
        TEST_ASSERT_TRUE(deque_is_not_empty(dq));
}

void test_macro_deque_peek_back(void) {
        //arrange
        struct deque dq;
        unsigned char buf[2];

        //act
        deque_new(&dq, buf, sizeof(buf));
        deque_push_front(&dq, 10);
        deque_push_back(&dq, 20);

        //assert
        TEST_ASSERT_EQUAL(20, deque_peek_back(dq));
}

void test_macro_deque_peek_front(void) {
        //arrange
        struct deque dq;
        unsigned char buf[2];

        //act
        deque_new(&dq, buf, sizeof(buf));
        deque_push_front(&dq, 10);
        deque_push_back(&dq, 20);

        //assert
        TEST_ASSERT_EQUAL(10, deque_peek_front(dq));
}

int main(void)
{
        UNITY_BEGIN();

        //initialization tests
        RUN_TEST(test_new_deque_zero_capacity_returns_error);
        RUN_TEST(test_new_deque_null_buffer_returns_error);
        RUN_TEST(test_new_deque_with_legal_parameters_returns_success);

        //single-item max-element buffer
        RUN_TEST(test_max_push_back_then_pop_back_returns_correct_data);
        RUN_TEST(test_max_push_front_then_pop_front_returns_correct_data);
        RUN_TEST(test_max_push_back_then_pop_front_returns_correct_data);
        RUN_TEST(test_max_push_front_then_pop_back_returns_correct_data);

        //single-item single-element buffer
        RUN_TEST(test_singleton_push_back_then_pop_back_returns_correct_data);
        RUN_TEST(test_singleton_push_front_then_pop_front_returns_correct_data);
        RUN_TEST(test_singleton_push_back_then_pop_front_returns_correct_data);
        RUN_TEST(test_singleton_push_front_then_pop_back_returns_correct_data);

        //single-item mid-size-element buffer
        RUN_TEST(test_mid_push_back_then_pop_back_returns_correct_data);
        RUN_TEST(test_mid_push_front_then_pop_front_returns_correct_data);
        RUN_TEST(test_mid_push_back_then_pop_front_returns_correct_data);
        RUN_TEST(test_mid_push_front_then_pop_back_returns_correct_data);

        //single-item error conditions
        RUN_TEST(test_push_back_on_full_array_returns_error);
        RUN_TEST(test_push_front_on_full_array_returns_error);
        RUN_TEST(test_pop_back_on_empty_array_returns_error);
        RUN_TEST(test_pop_front_on_empty_array_returns_error);

        //check empty
        RUN_TEST(test_deque_made_empty_is_truly_empty_via_pop_back);
        RUN_TEST(test_deque_made_empty_is_truly_empty_via_pop_front);

        //macro tests
        RUN_TEST(test_macro_deque_is_full);
        RUN_TEST(test_macro_deque_is_not_full);
        RUN_TEST(test_macro_deque_is_empty);
        RUN_TEST(test_macro_deque_is_not_empty);
        RUN_TEST(test_macro_deque_peek_back);
        RUN_TEST(test_macro_deque_peek_front);

        return UNITY_END();
}
