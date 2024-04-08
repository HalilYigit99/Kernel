#include "Usart0.hpp"

#include <avr/io.h>
#include <avr/interrupt.h>

#include "binary.hpp"

namespace nano
{

    volatile byte rxBuffer[RX_BUFFER_SIZE];
    volatile byte txBuffer[TX_BUFFER_SIZE];
    volatile byte rxHead;
    volatile byte rxTail;
    volatile byte txHead;
    volatile byte txTail;

} // namespace nano

using namespace nano;

ISR(USART_RX_vect)
{
    // Read the data from the USART
    byte data = UDR0;

    // Add the data to the receive buffer
    if (rxHead == (rxTail - 1 + RX_BUFFER_SIZE) % RX_BUFFER_SIZE)
    {
        // The buffer is full, so discard the data
    }
    else
    {
        rxBuffer[rxHead] = data;
        rxHead = (rxHead + 1) % RX_BUFFER_SIZE;
    }
}

ISR(USART_UDRE_vect)
{
    // Check if there is data to transmit
    if (txHead != txTail)
    {
        // Transmit the data
        UDR0 = txBuffer[txTail];
        txTail = (txTail + 1) % TX_BUFFER_SIZE;
    }
}

void Usart0::Begin(dword baud)
{
    // Calculate the baud rate register value
    uint16_t baudRateRegisterValue = (F_CPU / 16 / baud);

    // Set the baud rate
    UBRR0H = (baudRateRegisterValue >> 8);
    UBRR0L = baudRateRegisterValue;

    // Enable the receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0) | (1 << UDRIE0);

    // Set the frame format (8 data bits, 1 stop bit, no parity)
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

    // Initialize the receive and transmit buffers
    rxHead = 0;
    rxTail = 0;
    txHead = 0;
    txTail = 0;
}

void Usart0::Write(byte data)
{

    // Wait for the transmit buffer to have space
    while (((txHead + 1) % TX_BUFFER_SIZE) == txTail) 
    {

    }

    cli();

    // Add the data to the transmit buffer
    txBuffer[txHead] = data;
    txHead = (txHead + 1) % TX_BUFFER_SIZE;

    sei();

}

void Usart0::Write(String text)
{
    for (dword i = 0; i < text.Length(); i++)
    {
        Write(text[i]);
    }
}

byte Usart0::Read()
{
    // Wait for data to be available in the receive buffer
    while (rxHead == rxTail)
        ;

    // Read the data from the receive buffer
    byte data = rxBuffer[rxTail];
    rxTail = (rxTail + 1) % RX_BUFFER_SIZE;

    return data;
}

String Usart0::ReadAvailable()
{
    String text;

    // Read all available data from the receive buffer
    while (rxHead != rxTail)
    {
        text += rxBuffer[rxTail];
        rxTail = (rxTail + 1) % RX_BUFFER_SIZE;
    }

    return text;
}

dword Usart0::Avaliable()
{
    return (rxHead - rxTail + RX_BUFFER_SIZE) % RX_BUFFER_SIZE;
}

dword Usart0::AvaliableForWrite()
{
    return (TX_BUFFER_SIZE + txHead - txTail) % TX_BUFFER_SIZE;
}

void Usart0::Close()
{
    // Disable the receiver and transmitter
    UCSR0B = 0;

    // Clear the receive and transmit buffers
    rxHead = 0;
    rxTail = 0;
    txHead = 0;
    txTail = 0;
}
