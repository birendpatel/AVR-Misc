/*
* Copyright (C) 2021 Biren Patel
* MIT License
* Hardware: ATmega328P (Arduino Uno Rev3)
* Note: LEDs are split across ports B and D for arduino compatibility
*/

#ifndef F_CPU
        #error "F_CPU not defined"
#endif

#ifndef BAUD
        #error "BAUD not defined"
#endif

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include "deque.h"

void led_init(void);
void led_send(const unsigned char data);
void uart_init(void);
void uart_send(const unsigned char data);
uint8_t uart_recv(struct deque *fifo);
void trap(const uint8_t err);

/*******************************************************************************
* led_init() - configure LED pins
* @PD4-7: output, drive low
* @PB0-3: output, drive low
* @PB5: output, drive low (debug LED)
*******************************************************************************/
void led_init(void)
{
        DDRD = 0xF0;
        DDRB = 0x2F;
        PORTD = 0;
        PORTB = 0;
}

/*******************************************************************************
* led_send() - display binary representation of input data on LEDs
* @data: MSB [7][6][5][4][3][2][1][0] LSB -> [B3][B2][B1][B0][D7][D6][D5][D4]
*******************************************************************************/
void led_send(const unsigned char data)
{
        PORTB = (PORTB & 0xF0) | data >> 4; //retain B5 status
        PORTD = data << 4;
}

/*******************************************************************************
* uart_init() - configure asynchronous UART
* @UBRR0H: set UBBR using baud rate and cpu frequency defined in makefile
* @UCSR0B: enable TX and RX
* @UCSROC: set 8 bits per frame
*******************************************************************************/
void uart_init(void)
{
        UBRR0H = UBRRH_VALUE;
        UBRR0L = UBRRL_VALUE;
        UCSR0B = (1 << RXEN0) | (1 << TXEN0);
        UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
}

/*******************************************************************************
* uart_send() - transmit one frame
*******************************************************************************/
void uart_send(const unsigned char data)
{
        while (((UCSR0A >> UDRE0) & 0x1) == 0);
        UDR0 = data;
}

/*******************************************************************************
* uart_recv() - receive frames until frame containing newline or threshold met
* @fifo: data from received frames are queued to this buffer
* Returns: nonzero error code on failure or RECV_OK (0) on success
*******************************************************************************/

#define RECV_OK         (uint8_t) 0
#define PARITY_ERROR    (uint8_t) '1'
#define FRAME_ERROR     (uint8_t) '2'
#define OVERRUN_ERROR   (uint8_t) '3'
#define FIFO_ERROR      (uint8_t) '4'
#define BAD_BREAK       (uint8_t) '5'

uint8_t uart_recv(struct deque *fifo)
{
        unsigned char data;
        unsigned char status;

        while (1) {
                while (((UCSR0A >> RXC0) & 0x1) == 0) /* spin */;

                status = UCSR0A;
                data = UDR0;

                if (((status >> UPE0) & 0x1)) {
                        return PARITY_ERROR;
                } else if ((status >> FE0) & 0x1) {
                        return FRAME_ERROR;
                } else if ((status >> DOR0) & 0x1) {
                        return OVERRUN_ERROR;
                }

                if (deque_push_back(fifo, data)) {
                        return FIFO_ERROR;
                }

                if (data == (unsigned char) '\n') {
                        return RECV_OK;
                }

        }

        return BAD_BREAK;
}

/*******************************************************************************
* trap() - transmit error code and signal error status via debug LED
* @err: error code, transmitted as "error: #"
*******************************************************************************/
void trap(const uint8_t err)
{
        static char msg[10] = "error: #\n";
        msg[7] = (char) err;

        for (uint8_t i = 0; i < 9; i++) {
                uart_send(msg[i]);
        }

        while (1) {
                PORTB ^= 1 << PORTB5;
                _delay_ms(100);
        }
}

/*******************************************************************************
* main() - listen on Rx for a newline terminated string of data and then echo
that data to LEDs and Tx.
*******************************************************************************/
#define BUF_SIZE 64

int main(void)
{
        led_init();
        uart_init();

        uint8_t err = 0;
        unsigned char buf[BUF_SIZE] = {0};
        struct deque fifo;

        err = deque_new(&fifo, buf, BUF_SIZE);

        if (err) {
                trap(err);
        }

        while (1) {
                err = uart_recv(&fifo);

                if (err) {
                        trap(err);
                }

                unsigned char data = 0;
                while (deque_is_not_empty(fifo)) {
                        err = deque_pop_front(&fifo, &data);

                        if (err) {
                                trap(err);
                        }

                        uart_send(data);
                        led_send(data);
                        _delay_ms(500);

                        if (data == (unsigned char) '\n') {
                                break;
                        }
                }

                led_send(0x00);
        }

        return 0;
}
