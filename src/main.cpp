#include <Arduino.h>
#include "volume.h"



void setup() {
    volume_init();
    Serial.begin(9600);
    sei();
}



void loop() {
    Serial.println(volume_get());
    delay(100);
}
