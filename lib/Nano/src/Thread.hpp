#pragma once

#include "Nano.hpp"



namespace nano
{

    enum class ThreadState : int8_t {
        FINISHED = -4,
        TERMINATED = -3,
        SLEEPING = -2,
        CREATED = -1,
        UNKNOWN = 0,
        STARTING = 1,
        RUNNING = 2
    };

    using ThreadEntry = void(*)();

    class Thread {
        public:
            static void Yield();
            static Thread* getCurrentThread();
            static void Sleep(dword ms);

            Thread(ThreadEntry entry);

            ~Thread();

            void Start(word stackDepth = 64);

            void Terminate();

        public:

            byte* stackBottom;
            byte* stackPointer;
            String name;
            ThreadState state;
            ThreadEntry entry;

            union {
                dword sleepToMS;
            } asyncData;

    };

    
} // namespace nano


