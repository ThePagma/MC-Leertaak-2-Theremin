//
// Created by Deeq on 25/10/2026.
//

#include <Arduino.h>
#include "../include/volume.h"

void volume_init() {
    ADMUX  = (1 << REFS0) | (1 << ADLAR); // refs0 op high omdat ik avcc gebruikt en adlar high zodat resultaat links uitlijnen zodat ADCH de 8 belangrijkste bits bevat
    ADCSRB = 0;
    ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADATE) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); // zet alle bits aan behalve ADIF want die staat al goed en zet de Prescaler op 128 deler
}
