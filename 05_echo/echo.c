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

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <util/setbaud.h>

void led_init(void);
void led_send(const unsigned char data);
void uart_init(void);
void uart_send(const unsigned char data);
void uart_send_msg(const char *msg);
uint8_t uart_recv(unsigned char *data);
void trap(const uint8_t err);

/*******************************************************************************
* led_init() - configure LED pins
* @PD4-7: output, drive low
* @PB0-3: output, drive low
* @PB5: output, drive low (debug LED)
*******************************************************************************/
void led_init(void) {
        DDRD = 0xF0;
        DDRB = 0x2F;
        PORTD = 0;
        PORTB = 0;
}

/*******************************************************************************
* led_send() - display binary representation of input data on LEDs
* @data: MSB [7][6][5][4][3][2][1][0] LSB -> [B3][B2][B1][B0][D7][D6][D5][D4]
* note: uart frames contain 7 data bits, port B3 LED should never turn on.
*******************************************************************************/
void led_send(const unsigned char data) {
        PORTB = (PORTB & 0xF0) | data >> 4; //retain B5 status
        PORTD = data << 4;
}

/*******************************************************************************
* uart_init() - configure asynchronous UART
* @UCSR0B: enable TX and RX
* @UCSROC: set 7 bits per frame and set even parity mode
*******************************************************************************/
void uart_init(void) {
        UBRR0H = UBRRH_VALUE;
        UBRR0L = UBRRL_VALUE;
        UCSR0B = (1 << RXEN0) | (1 << TXEN0);
        UCSR0C = (1 << UCSZ01) | (1 << UPM01);
}

/*******************************************************************************
* uart_send() - transmit one frame
*******************************************************************************/
void uart_send(const unsigned char data) {
        while (((UCSR0A >> UDRE0) & 0x1) == 0);
        UDR0 = data;
}

/*******************************************************************************
* uart_send_msg() - transmit a null terminated string
* @msg: no more than 255 characters are sent and null char is never sent
*******************************************************************************/
void uart_send_msg(const char *msg) {
        uint8_t i = 0;

        while (msg[i]) {
                uart_send((unsigned char) msg[i]);
                ++i;

                if (i == UINT8_MAX) {
                        break;
                }
        }
}

/*******************************************************************************
* uart_recv() - receive one frame
* @data: contains the recieved frame regardless of error status
* Returns: nonzero error code on failure or RECV_OK (0) on success
*******************************************************************************/
#define RECV_OK         (uint8_t) 0
#define PARITY_ERROR    (uint8_t) '1'
#define FRAME_ERROR     (uint8_t) '2'
#define OVERRUN_ERROR   (uint8_t) '3'

uint8_t uart_recv(unsigned char *data) {
        uint8_t err = RECV_OK;

        while (((UCSR0A >> RXC0) & 0x1) == 0);

        if (((UCSR0A >> UPE0) & 0x1)) {
                err = PARITY_ERROR;
        } else if ((UCSR0A >> FE0) & 0x1) {
                err = FRAME_ERROR;
        } else if ((UCSR0A >> DOR0) & 0x1) {
                err = OVERRUN_ERROR;
        }

        *data = UDR0;

        return err;
}

/*******************************************************************************
* trap() - transmit error code and signal error status via debug LED
* @err: error code, transmitted as "error: #"
*******************************************************************************/
void trap(const uint8_t err) {
        static char msg[] = "error: #";
        msg[7] = (char) err;
        uart_send_msg(msg);

        while (1) {
                PORTB ^= 1 << PORTB5;
                _delay_ms(100);
        }
}

/*******************************************************************************
* main() - listen on Rx and echo data to LEDs and Tx
*******************************************************************************/
int main(void) {
        static char msg[] = "<#>";
        unsigned char data = 0;
        uint8_t err = 0;

        led_init();
        uart_init();

        while (1) {
                err = uart_recv(&data);

                if (err) {
                        trap(err);
                }

                msg[1] = (char) data;
                uart_send_msg(msg);
                led_send(data);
                _delay_ms(250);
        }

        return 0;
}
