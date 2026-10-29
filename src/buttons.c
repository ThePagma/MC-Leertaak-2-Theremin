//
// Created by Deeq on 28/10/2026.
//

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../include/buttons.h"

#define DEBOUNCE_TICKS 5   // 5 metingen van ongeveer 10 ms = ongeveer 50 ms
static volatile uint8_t debouncing = 0;   // 1 = knoppen worden even genegeerd
static uint8_t debounceCount = 0;
static volatile uint8_t plusFlag = 0;
static volatile uint8_t minFlag = 0;

void buttons_init(void) {
    DDRD &= ~((1 << DDD4) | (1 << DDD5));       // PD4 en PD5 als input
    PORTD |= (1 << PORTD4) | (1 << PORTD5);     // pull-ups aan
    PCICR |= (1 << PCIE2);                      // pin change interrupts van port D aan
    PCMSK2 |= (1 << PCINT20) | (1 << PCINT21);  // alleen PD4 en PD5 doen mee
}

// als knop wordt ingedruk zet flag om hoog en de knoppen uit
ISR(PCINT2_vect) {
    if (!(PIND & (1 << PIND4))) {
        plusFlag = 1;
    }
    if (!(PIND & (1 << PIND5))) {
        minFlag = 1;
    }
    // knoppen uit zetten voor debounce
    PCMSK2 &= ~((1 << PCINT20) | (1 << PCINT21));
    debouncing = 1;
}

// wacht aantaal ticks om debouncing te voor komen
void buttons_tick(void) {
    if (debouncing) {
        debounceCount++;
        if (debounceCount >= DEBOUNCE_TICKS) {
            debounceCount = 0;
            debouncing = 0;
            PCIFR = (1 << PCIF2);
            PCMSK2 |= (1 << PCINT20) | (1 << PCINT21);
        }
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


