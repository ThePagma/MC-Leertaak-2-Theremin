//
// Created by Deeq on 28/10/2026.
//

#ifndef MC_LEERTAAK_2_THEREMIN_FILTER_H
#define MC_LEERTAAK_2_THEREMIN_FILTER_H

#include <stdint.h>

void filter_init(uint8_t size);
uint16_t filter_apply(uint16_t value);
void filter_setSize(int16_t newSize);
uint8_t filter_getSize(void);

#endif //MC_LEERTAAK_2_THEREMIN_FILTER_H
