#include <avr/interrupt.h>
#include <avr/io.h>
#include "volume.h"
#include "buzzer.h"
#include "frequency.h"
#include "filter.h"
#include "buttons.h"
#include "seven-seg.h"
#include "lcd.h"

#define LCD_UPDATE_TICKS 20   // elke elke 20 loops instellen

int main(void) {
    volume_init();
    buzzer_init();
    frequency_init();
    filter_init(5);
    buttons_init();
    lcd_init();
    sevenseg_init();
    sei();

    sevenseg_showHex(filter_getSize());

    uint8_t lcdTicks = 0;
    uint16_t shownDistance = 0xFFFF;
    uint16_t shownFrequency = 0xFFFF;

    while (1) {
        buzzer_setVolume(volume_get());
        frequency_update(); // meet ultrasone waarde

        if (frequency_hasNewMeasurement()) {
            buttons_tick();   // elke meting als timer voor wanneer debounce voorbij is

            uint16_t distance = filter_apply(frequency_getDistance());
            uint16_t frequency = frequency_calculate(distance);
            buzzer_setFrequency(frequency);

            // lcd wordt alleen bijwerken als het tijd is en als er iets veranderd is
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

        // filter instellen en 9 seg updaten
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