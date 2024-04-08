#pragma once

#include <stdint.h>

#include "cpp.hpp"

#ifndef sbi

#define sbi(port, bit) ((port) |= (1 << (bit)))

#endif

#ifndef cbi

#define cbi(port, bit) ((port) &= ~(1 << (bit)))

#endif

#ifndef bit_is_set

#define bit_is_set(port, bit) ((port) & (1 << (bit)))

#endif

#ifndef bit_is_clear

#define bit_is_clear(port, bit) (!((port) & (1 << (bit))))

#endif

#ifndef lo8

#define lo8(word) ((uint8_t)(word))

#endif

#ifndef hi8

#define hi8(word) ((uint8_t)((word) >> 8))

#endif
