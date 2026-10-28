//
// Created by Deeq on 28/10/2026.
//

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../include/buttons.h"

static volatile uint8_t plusFlag = 0;
static volatile uint8_t minFlag = 0;

void buttons_init(void) {
    DDRD &= ~((1 << DDD4) | (1 << DDD5));       // PD4 en PD5 als input
    PORTD |= (1 << PORTD4) | (1 << PORTD5);     // pull-ups aan
    PCICR |= (1 << PCIE2);                      // pin change interrupts van port D aan
    PCMSK2 |= (1 << PCINT20) | (1 << PCINT21);  // alleen PD4 en PD5 doen mee
}

ISR(PCINT2_vect) {
    if (!(PIND & (1 << PIND4))) {   // pin is ingedrukt
        plusFlag = 1;
    }
    if (!(PIND & (1 << PIND5))) {   // pin is ingedrukt
        minFlag = 1;
    }
}

uint8_t buttons_plusPressed(void) {
    uint8_t mem = plusFlag;
    plusFlag = 0;
    return mem;
}
uint8_t buttons_minPressed(void) {
    uint8_t mem = minFlag;
    minFlag = 0;
    return mem;
}

