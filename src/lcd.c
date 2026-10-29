#include <stdio.h>
#include <stdint.h>
#include "hd44780pcf8574.h"
#include "lcd.h"

#define LCD_ADDRESS       0x27
#define LCD_COLS          16     // tekens per regel (2x16 display)
#define DISTANCE_SHOW_MAX 400    // HC-SR04 meet tot 400 cm;

// schrijft een regel aangevuld met spaties tot 16 tekens
// zodat er nooit stukje van een langere oude tekst blijven staan
static void lcd_writeLine(uint8_t row, const char *text) {
    char line[LCD_COLS + 1];
    snprintf(line, sizeof(line), "%-16.16s", text);
    HD44780_PCF8574_PositionXY(LCD_ADDRESS, 0, row);
    HD44780_PCF8574_DrawString(LCD_ADDRESS, line);
}

void lcd_init(void) {
    HD44780_PCF8574_Init(LCD_ADDRESS);
    HD44780_PCF8574_DisplayOn(LCD_ADDRESS);
    HD44780_PCF8574_DisplayClear(LCD_ADDRESS);
}
// tekst in het engels want anders past het niet
void lcd_showValues(uint16_t distance, uint16_t frequency) {
    char text[24];

    if (distance > DISTANCE_SHOW_MAX) {
        snprintf(text, sizeof(text), "Distance: --");   // hand buiten bereik
    } else {
        snprintf(text, sizeof(text), "Distance: %ucm", distance);
    }
    lcd_writeLine(0, text);

    snprintf(text, sizeof(text), "frequency:%4uHz", frequency);
    lcd_writeLine(1, text);
}