#include "SevenSegmentLed.h"

SevenSegmentLed::SevenSegmentLed(PinName a, PinName b, PinName c, PinName d, PinName e, PinName f, PinName g, PinName dp)
    : segment_leds(a, b, c, d, e, f, g, dp)
{
    this->scroll_interval_ms = 500ms;
}

void SevenSegmentLed::write_number(unsigned int number)
{
    if (number < 10)
    {
        segment_leds.write(this->pattern_number[number]);
    }
}

void SevenSegmentLed::scroll(unsigned int number)
{
    int digit = log10(number) + 1;
    unsigned int *pattern = new unsigned int[digit];
    for (int i = 0; i < digit; i++)
    {
        pattern[i] = number % 10;
        number /= 10;
    }
    for (int i = digit; i >= 0; i--)
    {
        this->write_number(pattern[i]);
        ThisThread::sleep_for(scroll_interval_ms);
        segment_leds.write(0);
        ThisThread::sleep_for(100ms);
    }
    delete[] pattern;
}

void SevenSegmentLed::scroll(std::string number)
{
    std::string tmp;
    for (int i = 0; i < number.length(); i++)
    {
        if (number[i] == '.')
        {
            this->segment_leds = 0b10000000;
        }
        else
        {
            tmp = number[i];
            this->write_number(std::stoi(tmp));
        }
        ThisThread::sleep_for(this->scroll_interval_ms);
    }
    this->segment_leds = 0;
}

void SevenSegmentLed::off_led()
{
    this->segment_leds = 0;
}