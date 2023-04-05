#pragma once
#include <Arduino.h>

class Timer {
    unsigned long last;
    unsigned long delta;
public:
    Timer(){}

    void begin();
    const unsigned long get_delta() const;
    const unsigned long get_timestamp() const;
    void tick();
};