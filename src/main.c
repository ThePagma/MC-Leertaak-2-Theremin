#include <avr/interrupt.h>
#include <avr/io.h>
#include "volume.h"
#include "buzzer.h"
#include "frequency.h"

int main() {
    volume_init();
    buzzer_init();
    frequency_init();
    sei();

    while(1) {
      buzzer_setVolume(volume_get());
      frequency_update();
      buzzer_setFrequency(frequency_getPulseLength() / 5);
    }
}
