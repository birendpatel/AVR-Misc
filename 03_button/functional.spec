Copyright (C) 2021 Biren Patel
MIT License
Functional Specification

/*******************************************************************************
* Overview
*******************************************************************************/

An MCU is connected to an LED configured for output. A push button is configured
for input. Whenever the button is pressed, the LED will light up. The LED will
stay lit so long as the button is held down. Under no circumstances will the 
LED light up if the button is not pressed.

technical note: pull up resistor is enabled on input pin, button provides a path
to ground. 

/*******************************************************************************
* Usage Scenario
*******************************************************************************/

Bob is walking his dog at 2 AM. It's pitch black outside. His dog takes a fierce
dump. Bob wants to collect the feces and dispose of it because he is not an 
asshole member of society. However, he forgot his flashlight and can't find the
mess. Luckily, he brought our MCU along with him because he's a weird dude. 
After all, he's walking a dog at 2 AM. He holds the button down and the bright
light allows him to see the mess.
