#include "Thread.hpp"

#include "binary.hpp"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

namespace nano
{

    extern volatile dword uptimeMS;

    void ThreadBegin___();

    Thread* currentThread;

    List<Thread*> threads;

    struct ProcessorState
    {
        byte _foo;
        byte sreg;
        byte regs[32];
        byte pc_h;
        byte pc_l;
    } __attribute__((packed));

    byte indexCounter;

    void sleepAnMS() {
        sleep_enable();

        set_sleep_mode(SLEEP_MODE_IDLE);

        dword startTime = uptimeMS;

        while (startTime == uptimeMS) {
            sleep_cpu();
        }

        sleep_disable();

    }

    void selectNextThread() {
        int threadCount = threads.Count();
        int tour = 0;
        while (true) {
            indexCounter++;
            if (indexCounter >= threadCount) {
                indexCounter = 0;
                tour++;
                if (tour >= 5) {
                    sleepAnMS();
                }
            }

            currentThread = threads[indexCounter];

            switch (currentThread->state)
            {
            case ThreadState::STARTING :
            case ThreadState::RUNNING :
                return;
                break;

            case ThreadState::SLEEPING :
                if (currentThread->asyncData.sleepToMS < uptimeMS) {
                    return;
                }
                break;
            
            default:
                break;
            }

        }
    }

    Thread* Thread::getCurrentThread() {
        return currentThread;
    }

    void Thread::Yield() {
        asm volatile ("jmp yield");
    }

    void Thread::Sleep(dword ms) {
        cbi(TIMSK0, OCIE0B);

        dword end = uptimeMS + ms;

        currentThread->asyncData.sleepToMS = end;
        currentThread->state = ThreadState::SLEEPING;

        sbi(TIMSK0, OCIE0B);

        while (uptimeMS < end) {
            
        }

    }

    Thread::Thread(ThreadEntry entry) {
        this->entry = entry;
        this->state = ThreadState::CREATED;
        threads.Add(this);
    }

    Thread::~Thread() {
        this->state = ThreadState::UNKNOWN;
        threads.Remove(this);

        if (this->stackBottom) {
            delete this->stackBottom;
        }

    }

    void Thread::Start(word stackDepth) {
        this->stackBottom = new byte[stackDepth + sizeof(ProcessorState)];
        this->stackPointer = (byte*)((dword)this->stackBottom + stackDepth);
        ProcessorState* state = (ProcessorState*)this->stackPointer;
        state->pc_h = hi8((word)ThreadBegin___);
        state->pc_l = lo8((word)ThreadBegin___);
        this->state = ThreadState::STARTING;
    }

    void Thread::Terminate() {
        this->state = ThreadState::TERMINATED;
        if (currentThread == this) Thread::Yield();
    }

    void ThreadBegin___() {
        currentThread->state = ThreadState::RUNNING;

        if (currentThread->entry) {
            currentThread->entry();
        }

        currentThread->state = ThreadState::FINISHED;

        for (;;) {
            Thread::Yield();
        }

    }
    
} // namespace nano

using namespace nano;

extern "C" void __attribute__((naked, used)) onCPUSaved() {
    currentThread->stackPointer = (byte*)SP;
    SP = RAMEND;
    cbi(TIMSK0, OCIE0B);
    sei();

    selectNextThread();

    cli();

    sbi(TIMSK0, OCIE0B);

    SP = (word)currentThread->stackPointer;

    asm volatile ("jmp restoreCPU");

}





// asm volatile(
//     ".section .text \n"
//     ".extern onCPUSaved \n"
//     ".global __vector_15 \n"
//     ".global yield \n"
//     ".global restoreCPU \n"
//     "yield: \n"
//     "cli \n"
//     "__vector_15: \n"
//     "push r31 \n"
//     "push r30 \n"
//     "push r29 \n"
//     "push r28 \n"
//     "push r27 \n"
//     "push r26 \n"
//     "push r25 \n"
//     "push r24 \n"
//     "push r23 \n"
//     "push r22 \n"
//     "push r21 \n"
//     "push r20 \n"
//     "push r19 \n"
//     "push r18 \n"
//     "push r17 \n"
//     "push r16 \n"
//     "push r15 \n"
//     "push r14 \n"
//     "push r13 \n"
//     "push r12 \n"
//     "push r11 \n"
//     "push r10 \n"
//     "push r9 \n"
//     "push r8 \n"
//     "push r7 \n"
//     "push r6 \n"
//     "push r5 \n"
//     "push r4 \n"
//     "push r3 \n"
//     "push r2 \n"
//     "push r1 \n"
//     "push r0 \n"
//     "in r0,0x3F \n"
//     "push r0 \n"
//     "jmp onCPUSaved \n"

//     "restoreCPU: \n"
//     "cli \n"
//     "pop r0 \n"
//     "out 0x3F, r0 \n"
//     "pop r0 \n"
//     "pop r1 \n"
//     "pop r2 \n"
//     "pop r3 \n"
//     "pop r4 \n"
//     "pop r5 \n"
//     "pop r6 \n"
//     "pop r7 \n"
//     "pop r8 \n"
//     "pop r9 \n"
//     "pop r10 \n"
//     "pop r11 \n"
//     "pop r12 \n"
//     "pop r13 \n"
//     "pop r14 \n"
//     "pop r15 \n"
//     "pop r16 \n"
//     "pop r17 \n"
//     "pop r18 \n"
//     "pop r19 \n"
//     "pop r20 \n"
//     "pop r21 \n"
//     "pop r22 \n"
//     "pop r23 \n"
//     "pop r24 \n"
//     "pop r25 \n"
//     "pop r26 \n"
//     "pop r27 \n"
//     "pop r28 \n"
//     "pop r29 \n"
//     "pop r30 \n"
//     "pop r31 \n"
//     "reti \n"
// );


