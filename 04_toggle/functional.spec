Copyright (C) 2021 Biren Patel
MIT License
Functional Specification

/*******************************************************************************
* Overview
*******************************************************************************/

Three LEDs are connected to their respective output pins on a microcontroller. A
button to ground is configured for input.

Technical note (1): input pull up resistor is activated on setup

When the button is pressed, the MCU cycles between turning the LEDs on in the
following order: NONE -> GREEN -> YELLOW -> RED. Only one LED can be on at any
point in time. The MCU always begins in the NONE state whenever it is reset.

If the LED is red and the button is pressed, then the NONE state is entered
and all LEDs will be off. If the MCU is in the NONE state and the button is
pressed, then the green LED will turn on. The cycle continues forever in this
fixed cyclical pattern.

Technical note (2): button debouncing is not implemented in either hardware or
software

Technical note (3): include a debugging LED to track state conditions

/*******************************************************************************
* Usage Scenario
*******************************************************************************/

Goran is teaching driving lessons to recently discovered aliens who wish to
peacefully inhabit our planet.

He uses our MCU to demonstrate the fundamental concepts of traffic lights. The
aliens understand thanks to the power of visual hands-on learning.

Unfortunately, our MCU includes a NONE state which is not possible on real
traffic lights. When the aliens attempt to drive in the real world, the light
moves immediately from red to green and chaos ensues. The situation is made
drastically worse by a lack of debouncing algorithms. The aliens turn violent
and hostile and the world burns thanks to Goran's poor foresight.
