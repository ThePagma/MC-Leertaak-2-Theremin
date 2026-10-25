#include <Arduino.h>
#include "volume.h"

static volatile uint8_t volume = 0;


void setup() {
    volume_init();
    Serial.begin(9600);
    sei();
}

ISR(ADC_vect) {
    volume = ADCH;
}

void loop() {
    Serial.println(volume);
    delay(100);
}
