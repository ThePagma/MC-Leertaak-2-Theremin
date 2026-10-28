    //
    // Created by deeq2 on 28/10/2026.
    //

    #include <avr/io.h>
    #include <avr/interrupt.h>
    #include "../include/frequency.h"

    static volatile uint16_t pulseLength = 0;
    static volatile uint8_t captureFlag = 0;
    enum PingState { START_PULSE, END_PULSE, WAIT };
    static enum PingState state = START_PULSE;
    static uint16_t startTime = 0;

    void frequency_init(void) {
        DDRB |= (1 << DDB5);

        DDRB |= (1 << DDB1);
        DDRB &= ~(1 << DDB0);
        TCCR1A = 0;
        TCCR1B = (1 << ICES1) | (1 << CS11);
        TIMSK1 |= (1 << ICIE1);
    }

    ISR(TIMER1_CAPT_vect) {
        if (TCCR1B & (1 << ICES1)) {
            TCNT1 = 0;
            TCCR1B &= ~(1 << ICES1);
        }else {
            PORTB ^= (1 << PORTB5);   // TEST: LED omdraaien bij elke meting
            pulseLength = ICR1;
            captureFlag = 1;
            TCCR1B |= (1 << ICES1);
        }
        TIFR1 = (1 << ICF1);
    }

    void frequency_update(void) {
        switch (state) {
            case START_PULSE:
                PORTB |= (1 << PORTB1);
                startTime = TCNT1;
                state = END_PULSE;
                break;
            case END_PULSE:
                if (TCNT1 - startTime >= 20) {
                    // trigger laag,
                    PORTB &= ~(1 << PORTB1);
                    state = WAIT;
                }
                break;
            case WAIT:
                if (captureFlag == 1) {
                    captureFlag = 0;
                    state = START_PULSE;
                }
                break;
        }
    }

    uint16_t frequency_getPulseLength(void) {
        return pulseLength;
    }