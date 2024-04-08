#include <Nano.hpp>
#include <List.hpp>
#include <Array.hpp>
#include <String.hpp>
#include <Thread.hpp>
#include <Usart0.hpp>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



namespace nano
{

    String message = "Hello World!\n";
    String ledMsg = "LED!\n";

    void Other() {
        Object obj1;
        obj1 = ledMsg.Clone();
        for (;;) {
            Thread::Sleep(1000);
            PORTB = ~PORTB;
            String msg2 = obj1;
            Usart0::Write(msg2);
        }
    }

    void App_begin() {

        DDRB = 255;

        PORTB = 255;

        Thread* other = new Thread(Other);

        other->Start();

        Usart0::Begin(9600);

        Usart0::Write(message);


    }
  
} // namespace nano

