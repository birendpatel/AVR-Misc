Copyright (C) 2021 Biren Patel
MIT License
Functional Specification

/*******************************************************************************
* Overview
*******************************************************************************/

A microcontroller is set up with 8 LEDs configured for output. A user transmits
several bytes of data to the microcontroller via their personal computer.

The microcontroller echos the binary representation of the data onto the row of
LEDs. The microcontroller also echos the data back to the user's personal
computer but each byte returned encapsulated in brackets.

technical note (1): communication via UART

techincal note (2): frame format for the UART includes a parity bit and traps 
into a loop on the debug LED.

/*******************************************************************************
* Example
*******************************************************************************/

The user is running the linux terminal program "screen" and is connected to the
microcontroller via their serial port. The user sends the letter "a". The
microcontroller displays "01100001" on its LEDs and echos "<a>" back to the
user via the serial connection.

technical note (2): PB3 is the MSB. PB0-3 recieves upper nibble, PD4-7 receives
lower nibble. PD4 is the LSB.

/*******************************************************************************
* Usage Scenario
*******************************************************************************/

Juanito is incredibly lonely and has no friends. He decides to talk to our MCU
as an outlet for his lack of friendship. However, the MCU only repeats what he
says and has absolutely zero intelligence. This crude form of communication
does not fill the empty void in Juanito's heart. 
