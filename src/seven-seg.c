//
// Created by Deeq on 28/10/2026.
//
#include <avr/io.h>
#include "twi.h"
#include "seven-seg.h"
#define SEVENSEG_ADDRESS 0x21

static const uint8_t hexDigits[16] = {
    0b00111111,   // 0: a b c d e f
    0b00000110,   // 1: b c
    0b01011011,   // 2: a b d e g
    0b01001111,   // 3: a b c d g
    0b01100110,   // 4: b c f g
    0b01101101,   // 5: a c d f g
    0b01111101,   // 6: a c d e f g
    0b00000111,   // 7: a b c
    0b01111111,   // 8: alles behalve de punt
    0b01101111,   // 9: a b c d f g
    0b01110111,   // A: a b c e f g
    0b01111100,   // b: c d e f g
    0b00111001,   // C: a d e f
    0b01011110,   // d: b c d e g
    0b01111001,   // E: a d e f g
    0b01110001,   // F: a e f g
};

void sevenseg_init(void) {
    TWI_Init();
    TWI_FREQ(18, 1);
    PORTC |= (1 << PORTC4) | (1 << PORTC5);
}

static void sevenseg_write(uint8_t pattern) {
    TWI_MT_Start();
    TWI_Transmit_SLAW(SEVENSEG_ADDRESS);
    TWI_Transmit_Byte(pattern);
    TWI_Stop();
}

void sevenseg_showHex(uint8_t value) {
    if (value > 15) {
        return;
    }
    sevenseg_write(~hexDigits[value]);
}