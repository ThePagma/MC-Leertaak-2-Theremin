#include <Arduino.h>

static volatile uint8_t volume = 0;

void setup() {
    ADMUX  = (1 << REFS0) | (1 << ADLAR); // refs0 op high omdat ik avcc gebruikt en adlar high zodat resultaat links uitlijnen zodat ADCH de 8 belangrijkste bits bevat
    ADCSRB = 0;
    ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADATE) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); // zet alle bits aan behalve ADIF want die staat al goed en zet de Prescaler op 128 deler
    Serial.begin(9600);
    sei();
}

ISR(ADC_vect) {
    volume = ADCH;
}


void loop() {

}
