    //
    // Created by deeq2 on 28/10/2026.
    //

    #include <avr/io.h>
    #include <avr/interrupt.h>
    #include "../include/frequency.h"
    #include "../include/buzzer.h"


    static volatile uint16_t pulseLength = 0;
    static volatile uint8_t captureFlag = 0;
    enum PingState { START_PULSE, END_PULSE, WAIT, PAUSE};
    static enum PingState state = START_PULSE;
    static uint16_t startTime = 0;

    #define MEASURE_INTERVAL 20000   // 10 ms, bij 0,5 µs per stapje
    #define NO_ECHO 0xFFFF   // geen echo binnen 32,8 ms: hand buiten bereik
    #define DISTANCE_MAX 65

    void frequency_init(void) {
        DDRB |= (1 << DDB1);
        DDRB &= ~(1 << DDB0);
        TCCR1A = 0;
        TCCR1B = (1 << ICES1) | (1 << CS11);
        TIMSK1 |= (1 << ICIE1) | (1 << TOIE1);
    }

    ISR(TIMER1_CAPT_vect) {
        if (TCCR1B & (1 << ICES1)) {
            TCNT1 = 0;
            TCCR1B &= ~(1 << ICES1);
        }else {
            pulseLength = ICR1;
            captureFlag = 1;
            TCCR1B |= (1 << ICES1);
        }
        TIFR1 = (1 << ICF1);
    }

    // in geval dat hand buiten bereik is
    ISR(TIMER1_OVF_vect) {
        pulseLength = NO_ECHO;
        captureFlag = 1;
        TCCR1B |= (1 << ICES1);
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
                    state = PAUSE;
                }
                break;
            case PAUSE:
                if (TCNT1 >= MEASURE_INTERVAL) {
                    state = START_PULSE;
                }
                break;
        }
    }

    uint16_t frequency_getDistance(void) {
        return pulseLength / 116; // pulse length is timer stap 1 stap is 0.5 microseconde dus inplaats van / 58 doe ik / 116
    }

    uint16_t frequency_calculate(uint16_t distance) {
        if (distance > DISTANCE_MAX) {
            distance = DISTANCE_MAX;
        }
        return FREQ_MAX - (uint32_t)(FREQ_MAX - FREQ_MIN) * distance / DISTANCE_MAX;
    }

    uint16_t frequency_getPulseLength(void) {
        return pulseLength;
    }