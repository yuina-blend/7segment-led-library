#ifndef SEVEM_SEGMENT_LED
#define SEVEN_SEGMENT_LED

#include "mbed.h"
#include "string"

class SevenSegmentLed
{
public:
    Kernel::Clock::duration_u32 scroll_interval_ms;
    SevenSegmentLed(PinName a, PinName b, PinName c, PinName d, PinName e, PinName f, PinName g, PinName dp);
    void write_number(unsigned int number);
    void scroll(unsigned int number);
    void scroll(double number, unsigned int significant_figures);
    void off_led();
    SevenSegmentLed &operator=(unsigned int number)
    {
        write_number(number);
        return *this;
    }

protected:
    BusOut segment_leds;
    const int pattern_number[10] = {
        0b00111111,
        0b00000110,
        0b01011011,
        0b01001111,
        0b01100110,
        0b01101101,
        0b01111101,
        0b00100111,
        0b01111111,
        0b01101111};
};

#endif