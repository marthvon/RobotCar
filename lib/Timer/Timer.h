#pragma once
#include <Arduino.h>

class Timer {
    unsigned long last = 0;
    unsigned long delta = 0;
public:
    Timer(){}

    void begin();
    const unsigned long get_delta() const;
    const unsigned long get_timestamp() const;
    const unsigned long get_delta_from_timestamp(const unsigned long timestamp) const;
    void tick();
};
