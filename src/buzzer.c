//
// Created by Deeq on 27/10/2026.
//

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../include/buzzer.h"

void buzzer_init(void) {
    DDRD |= (1 << DDD3);
    TCCR2A = (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);
    OCR2B = 128;
}

void buzzer_setVolume(uint8_t volume) {
    OCR2B = volume;
}