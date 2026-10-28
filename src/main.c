#include <avr/interrupt.h>
#include <avr/io.h>
#include "volume.h"
#include "buzzer.h"
#include "frequency.h"
#include "filter.h"
#include "buttons.h"
#include "seven-seg.h"
#include "lcd.h"

#define LCD_UPDATE_TICKS 20   // LCD hooguit elke 20 metingen (ongeveer 200 ms) bijwerken

int main(void) {
    volume_init();
    buzzer_init();
    frequency_init();
    filter_init(5);
    buttons_init();
    lcd_init();        // eerst het LCD: deze library zet de I2C-bus op 200 kHz
    sevenseg_init();   // daarna de bus op 100 kHz, die het 7-segmentendisplay nodig heeft
    sei();

    sevenseg_showHex(filter_getSize());

    uint8_t lcdTicks = 0;
    uint16_t shownDistance = 0xFFFF;    // nog niets getoond: de eerste keer altijd bijwerken
    uint16_t shownFrequency = 0xFFFF;

    while (1) {
        buzzer_setVolume(volume_get());
        frequency_update();

        if (frequency_hasNewMeasurement()) {
            buttons_tick();   // elke meting duurt ongeveer 10 ms: tijdbasis voor het ontdenderen

            uint16_t distance = filter_apply(frequency_getDistance());
            uint16_t frequency = frequency_calculate(distance);
            buzzer_setFrequency(frequency);

            // LCD alleen bijwerken als het tijd is én als er iets veranderd is,
            // want elke update houdt de main-loop ongeveer 20 ms bezig
            lcdTicks++;
            if (lcdTicks >= LCD_UPDATE_TICKS) {
                lcdTicks = 0;
                if (distance != shownDistance || frequency != shownFrequency) {
                    lcd_showValues(distance, frequency);
                    shownDistance = distance;
                    shownFrequency = frequency;
                }
            }
        }

        if (buttons_plusPressed()) {
            filter_setSize(filter_getSize() + 2);
            sevenseg_showHex(filter_getSize());
        }
        if (buttons_minPressed()) {
            filter_setSize(filter_getSize() - 2);
            sevenseg_showHex(filter_getSize());
        }
    }
}