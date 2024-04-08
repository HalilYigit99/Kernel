#pragma once

#include "cpp.hpp"

namespace nano
{

    class HardwareInterrupt {
        private:
            static void Initilaze();
            friend class Interrupt;
            friend class Device;
    };
    
} // namespace nano


