#include <avr/interrupt.h>
#include <avr/io.h>
#include "volume.h"
#include "buzzer.h"
#include "frequency.h"
#include "filter.h"
#include "buttons.h"
#include "seven-seg.h"

int main() {
    volume_init();
    buzzer_init();
    frequency_init();
    filter_init(5);
    buttons_init();
    sevenseg_init();
    sei();

    sevenseg_showHex(filter_getSize());
    while(1) {
        buzzer_setVolume(volume_get());
        frequency_update();
        if (frequency_hasNewMeasurement()) {
            uint16_t distance = frequency_getDistance();
            distance = filter_apply(distance);
            buzzer_setFrequency(frequency_calculate(distance));
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
