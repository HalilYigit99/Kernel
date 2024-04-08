#pragma once


#include "Nano.hpp"


#define RX_BUFFER_SIZE 32
#define TX_BUFFER_SIZE 32


namespace nano
{


    class Usart0 {

        public:

            static void Begin(dword baud);

            static void Write(byte data);

            static void Write(String text);

            static byte Read();

            static String ReadAvailable();

            static dword Avaliable();

            static dword AvaliableForWrite();

            static void Close();

    };

    
} // namespace nano


