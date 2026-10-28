//
// Created by deeq2 on 28/10/2026.
//

#ifndef MC_LEERTAAK_2_THEREMIN_FREQUENCY_H
#define MC_LEERTAAK_2_THEREMIN_FREQUENCY_H

#include <stdint.h>

void frequency_init(void);
void frequency_update(void);
uint16_t frequency_getDistance(void);
uint16_t frequency_calculate(uint16_t distance);
uint8_t frequency_hasNewMeasurement();

#endif //MC_LEERTAAK_2_THEREMIN_FREQUENCY_H
