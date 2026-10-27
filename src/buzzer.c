//
// Created by Deeq on 27/10/2026.
//

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../include/buzzer.h"

void buzzer_init(void) {
    DDRD |= (1 << DDD3);
    TCCR2A = (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B = (1 << CS20);
    OCR2B = 128; // volume

    TCCR0A = (1 << WGM01);
    TCCR0B = (1 << CS02);
    OCR0A = 70; // temp waarde
    TIMSK0 = (1 << OCIE0A);
}

ISR(TIMER0_COMPA_vect) {
    TCCR2A ^= (1 << COM2B1);
}

void buzzer_setVolume(uint8_t volume) {
    OCR2B = volume;
}