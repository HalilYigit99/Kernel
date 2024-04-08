#pragma once

#include "Nano.hpp"

namespace nano
{

    class String;

    class Object {
        private:
            void* self;
        public:

            Object() {
                this->self = (void*)this;
            }

            template <typename T>
            Object(T& x) {
                this->self = (void*)&x;
            }

            ~Object() {

            }

            template <typename T>
            operator T() {
                return *((T*)this->self);
            }

            virtual String ToString();

    };

    typedef Object object;
    
} // namespace nano

#include "String.hpp"
