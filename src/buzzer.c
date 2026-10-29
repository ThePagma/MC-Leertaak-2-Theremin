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
    OCR2B = 128; // start volume

    TCCR0A = (1 << WGM01);
    TCCR0B = (1 << CS02);
    OCR0A = 70;

    TIMSK0 = (1 << OCIE0A);
}

ISR(TIMER0_COMPA_vect) {
    if (OCR2B == 0) {
        TCCR2A &= ~(1 << COM2B1);   // volume 0: PWM uit laten
    } else {
        TCCR2A ^= (1 << COM2B1);    // anders: PWM omdraaien voor de toon
    }
}

void buzzer_setVolume(uint8_t volume) {
    OCR2B = volume;
}

void buzzer_setFrequency(uint16_t frequency) {
    // 16000000 / 256 (deler) / 2 (twee interrupts per periode) = 31250
    if (frequency < FREQ_MIN) {
     frequency = FREQ_MIN;
    }else if (frequency > FREQ_MAX) {
        frequency = FREQ_MAX;
    }

    OCR0A = 31250 / frequency - 1;
}