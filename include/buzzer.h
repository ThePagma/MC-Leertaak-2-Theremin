//
// Created by Deeq on 27/10/2026.
//

#ifndef MC_LEERTAAK_2_THEREMIN_BUZZER_H
#define MC_LEERTAAK_2_THEREMIN_BUZZER_H

#include <stdint.h>
#define FREQ_MIN 230
#define FREQ_MAX 1400

void buzzer_init(void);

void buzzer_setVolume(uint8_t volume);

void buzzer_setFrequency(uint16_t frequency);

#endif //MC_LEERTAAK_2_THEREMIN_BUZZER_H
