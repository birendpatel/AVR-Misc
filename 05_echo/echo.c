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
* note: trap called when send_recv() encounter frame or parity error
*******************************************************************************/
void trap(void) {
        while (1) {
                PORTB ^= 1 << PORTB5;
                _delay_ms(100);
        }
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
*******************************************************************************/
void uart_recv(uint8_t *byte) {
        return;
}

/*******************************************************************************
* main() - listen on Rx and echo data to LEDs and Tx
*******************************************************************************/
int main(void) {
        led_init();
        uart_init();

        return 0;
}
