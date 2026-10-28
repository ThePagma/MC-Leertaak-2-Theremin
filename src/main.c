#include <avr/interrupt.h>
#include <avr/io.h>
#include "volume.h"
#include "buzzer.h"
#include "frequency.h"
#include "filter.h"
#include "buttons.h"

int main() {
    volume_init();
    buzzer_init();
    frequency_init();
    filter_init(5);
    buttons_init();
    sei();

    while(1) {
        buzzer_setVolume(volume_get());
        filter_setSize(5); // test waarde
        frequency_update();
        if (frequency_hasNewMeasurement()) {
            uint16_t distance = frequency_getDistance();
            distance = filter_apply(distance);
            buzzer_setFrequency(frequency_calculate(distance));
        }

        if (buttons_plusPressed()) { filter_setSize(15); }   // TEST
        if (buttons_minPressed())  { filter_setSize(1); }    // TEST
    }

}
