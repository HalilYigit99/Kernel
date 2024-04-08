#include "Nano.hpp"

#include <avr/io.h>
#include <avr/interrupt.h>

namespace nano
{

    volatile dword uptimeMS;

    void initUptimeTimer() {
        byte sreg = SREG;
        cli();


        TCCR0A = (1 << WGM01);

        TCCR0B = (1 << CS00) | (1 << CS01);

        OCR0A = 250;

        OCR0B = 125;

        TIMSK0 = (1 << OCIE0A) | (1 << OCIE0B);

        SREG = sreg;
    }
    
} // namespace nano

ISR(TIMER0_COMPA_vect) {
    nano::uptimeMS++;
}
