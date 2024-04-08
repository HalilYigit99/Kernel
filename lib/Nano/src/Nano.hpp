#pragma once

#include <stddef.h>
#include <stdint.h>

#include "cpp.hpp"

namespace nano
{

    typedef uint32_t time_t;
    typedef uint64_t qword;
    typedef uint32_t dword;
    typedef uint16_t word;
    typedef uint8_t byte;
    
    typedef const char* cstring;
    typedef char* str;

    void App_begin();
    
} // namespace nano

#include "Object.hpp"
#include "String.hpp"
