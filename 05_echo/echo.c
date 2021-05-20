/*
* Copyright (C) 2021 Biren Patel
* MIT License
* Note: AVR also provides setbaud.h to abstract away UART intialization details
* Note: LEDs are split across two ports for arudino board compatibility
*/

#ifndef F_CPU
        #error "F_CPU not defined"
#endif

#ifndef BAUD
        #error "BAUD_RATE not defined"
#endif

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <util/parity.h>

/*******************************************************************************
* trap() - no return do nothing loop and flash debug LED
* note: error codes are natural numbers, so for loop indicates error code
*******************************************************************************/
void trap(const uint8_t iter) {
        while (1) {
                for (int i = 0; i < iter; i++) {
                        PORTB ^= 1 << PORTB5;
                        _delay_ms(100)
                }

                _delay_ms(1000);
        }
}

/*******************************************************************************
* uart_init() - configure async UART
* note: ATmega328P UBRRnH bits 12-15 must be zero for future comptability
* @UCSR0B: TX and RX enabled, 9 bit char size
* @UCSROC: even parity, 9 bit char size
*******************************************************************************/
void uart_init(void) {
        const uint16_t ubrr = (uint16_t) ((F_CPU / (16UL * BAUD)) - 1UL);

        UBRR0H = (uint8_t) ((ubrr >> 8) & 0xF);
        UBRR0L = (uint8_t) (ubrr & 0xFF);

        UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << UCSZ02);
        UCSR0C = (1 << UPM01) | (1 << UCSZ01) | (1 << UCSZ00);
}

/*******************************************************************************
* uart_send() - send data
*******************************************************************************/
void uart_send(const uint8_t data) {
        while (((UCSR0A >> UDRE0) & 0x1) == 0) /* wait */ ;

        UCSR0B |= (parity_even_bit(data) << TXB80);

        UDR0 = data;
}

/*******************************************************************************
* uart_recv() - receive data
* Returns: 1 if error, else 0
*******************************************************************************/
#define RECV_OK         (uint8_t) 0
#define PARITY_ERROR    (uint8_t) 1
#define FRAME_ERROR     (uint8_t) 2
#define OVERRUN_ERROR   (uint8_t) 3

uint8_t uart_recv(uint8_t *byte) {
        uint8_t err = RECV_OK;

        while (((UCSR0A >> RXC0) & 0x1) == 0) /* wait */ ;

        if (((UCSR0A >> UPE0) & 0x1)) {
                err = PARITY_ERROR;
        } elif ((UCSR0A >> FE0) & 0x1) {
                err = FRAME_ERROR;
        } elif ((UCSR0A >> DOR0) & 0x1) {
                err = OVERRUN_ERROR;
        }

        *byte = RDR0;

        return err;
}

/*******************************************************************************
* led_init() - configure LED pins
* @PD4-7: output, drive low
* @PB0-3: output, drive low
* @PB5: output, drive low (debug LED)
*******************************************************************************/
void led_init(void) {
        DDRD = 0b11110000;
        DDRB = 0b00101111;
        PORTD = 0;
        PORTB = 0;
}

/*******************************************************************************
* led_send() - display binary repr of input on LEDs
*******************************************************************************/
void led_send(const uint8_t data) {
        PORTB |= data >> 4;
        PORTD |= data << 4;
}

/*******************************************************************************
* main() - listen on Rx and echo data to LEDs and Tx
*******************************************************************************/
int main(void) {
        led_init();
        uart_init();

        uint8_t data = 0;
        uint8_t err = 0;

        while (1) {
                err = uart_recv(&data);

                if (err) {
                        trap(err);
                }

                led_send(data);
                uart_send(data);
        }

        return 0;
}
