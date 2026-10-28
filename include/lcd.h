//
// Created by Deeq on 29/10/2026.
//

#ifndef MC_LEERTAAK_2_THEREMIN_LCD_H
#define MC_LEERTAAK_2_THEREMIN_LCD_H

#include <stdint.h>

void lcd_init(void);
void lcd_showValues(uint16_t distance, uint16_t frequency);

#endif //MC_LEERTAAK_2_THEREMIN_LCD_H