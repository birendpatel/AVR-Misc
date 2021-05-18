Copyright (C) 2021 Biren Patel
MIT License
Functional Specification

/*******************************************************************************
* Overview
*******************************************************************************/

The microcontroller is connected to a single LED configured for output. The MCU
transmits a message over the LED via morse code. When the LED lights up, the
length of time that it stays lit allows us to differentiate between dots and
dashes. The length of time that it stays unlit allows us to differentiate
between letters and words. The MCU transmits the same message forever in a loop.

Technical note: dots should be sustained for 300 milliseconds

/*******************************************************************************
* Usage Scenario
*******************************************************************************/

McJimmy's is an evil multinational fast food company which may or may not put
illegal horse meat in its signature hamburger. McJimmy's executives decide that
all neon signs on their restaurant storefronts should blink subliminal messages
in order to entice more customers. "The KGB did that kind of stuff during the
cold war," says the CEO. They easily install our morse code MCU into their signs
and "I LOVE HORSE MEAT" is transmited endlessly across the globe. Sales boom and
the executives give themselves million dollar bonuses in celebration.
