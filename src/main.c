#include <avr/interrupt.h>
#include <avr/io.h>
#include "volume.h"
#include "buzzer.h"

int main() {
        volume_init();
        buzzer_init();
        sei();

        DDRB |= (1 << DDB5);

        while(1) {
                if (volume_get() > 127) {
                        PORTB |= (1 << PORTB5);
                } else {
                        PORTB &= ~(1 << PORTB5);
                }
        }
}