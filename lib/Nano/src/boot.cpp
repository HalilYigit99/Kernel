#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdlib.h>

#include "Nano.hpp"
#include "binary.hpp"

#include "Thread.hpp"

namespace nano
{

    void initUptimeTimer();

    extern Thread* currentThread;
    
} // namespace nano



using namespace nano;


int __attribute__((naked)) main() {
    cli();
    __malloc_heap_end = (char*)RAMEND;
    __malloc_margin = 0;

    currentThread = new Thread(App_begin) ;

    currentThread->Start();

    initUptimeTimer();

    SP = (word)currentThread->stackPointer;

    asm volatile ("jmp restoreCPU");

}
