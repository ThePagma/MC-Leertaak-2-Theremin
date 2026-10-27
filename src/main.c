#include <avr/interrupt.h>
#include <avr/io.h>
#include "volume.h"
#include "buzzer.h"

int main() {
        volume_init();
        buzzer_init();
        sei();

        while(1) {
                buzzer_setVolume(volume_get());
        }
}