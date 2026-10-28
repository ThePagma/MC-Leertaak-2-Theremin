#include <stdio.h>
#include <stdint.h>
#include "hd44780pcf8574.h"
#include "lcd.h"

#define LCD_ADDRESS       0x27   // I2C-adres van het LCD (TO, hoofdstuk 10)
#define LCD_COLS          16     // tekens per regel (2x16 display)
#define DISTANCE_SHOW_MAX 400    // HC-SR04 meet tot 400 cm; hoger (NO_ECHO) = geen hand gezien

// schrijft één regel, aangevuld met spaties tot 16 tekens,
// zodat er nooit restjes van een langere oude tekst blijven staan
static void lcd_writeLine(uint8_t row, const char *text) {
    char line[LCD_COLS + 1];                          // 16 tekens + de afsluitende '\0'
    snprintf(line, sizeof(line), "%-16.16s", text);   // precies 16 tekens: aanvullen met spaties, of afkappen
    HD44780_PCF8574_PositionXY(LCD_ADDRESS, 0, row);
    HD44780_PCF8574_DrawString(LCD_ADDRESS, line);
}

void lcd_init(void) {
    HD44780_PCF8574_Init(LCD_ADDRESS);      // let op: roept zelf TWI_Init() aan (200 kHz)
    HD44780_PCF8574_DisplayOn(LCD_ADDRESS);
    HD44780_PCF8574_DisplayClear(LCD_ADDRESS);
}

void lcd_showValues(uint16_t distance, uint16_t frequency) {
    char text[24];   // ruim genoeg; lcd_writeLine maakt er precies 16 tekens van

    if (distance > DISTANCE_SHOW_MAX) {
        snprintf(text, sizeof(text), "Afstand: --");          // geen echo: hand buiten bereik
    } else {
        snprintf(text, sizeof(text)d, "Afstand: %ucm", distance);
    }
    lcd_writeLine(0, text);

    snprintf(text, sizeof(text), "frequentie:%4uHz", frequency);   // %4u: getal 4 breed, dus "frequentie: 500Hz" en "frequentie:1220Hz"
    lcd_writeLine(1, text);
}