//
// Created by Deeq on 28/10/2026.
//

#ifndef MC_LEERTAAK_2_THEREMIN_BUTTON_H
#define MC_LEERTAAK_2_THEREMIN_BUTTON_H
#include <stdint.h>

void buttons_init(void);
void buttons_tick(void);
uint8_t buttons_plusPressed(void);
uint8_t buttons_minPressed(void);

#endif //MC_LEERTAAK_2_THEREMIN_BUTTON_H
