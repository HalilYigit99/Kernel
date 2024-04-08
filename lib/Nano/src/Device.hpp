#pragma once

#include "cpp.hpp"
#include "Nano.hpp"

namespace nano
{

    class Device {
        public:

            static void Reboot();
            static void Shutdown();

            static void AttachDebugger();
            static void DeattachDebugger();

            static void EnablePowerSaving();
            static void DisablePowerSaving();

            static void EnableExceptionHandling();
            static void DisableExceptionHandling();

            static size_t GetAvailableHeap();

            static void Memdump();

    };
    
} // namespace nano


