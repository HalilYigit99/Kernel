#pragma once

#include "Nano.hpp"
#include "cpp.hpp"
#include "Function.hpp"

namespace nano
{

    class Interrupt {
        private:

            Array<Function<void>> handlers;
            byte occurCount;

        public:

            Interrupt(byte id);

            ~Interrupt();

            void AddHandler(Function<void> handler);

            void RemoveHandler(Function<void> handler);

    };
    
} // namespace nano


