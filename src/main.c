#include <avr/interrupt.h>
#include <avr/io.h>
#include "volume.h"

int main() {
        volume_init();
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