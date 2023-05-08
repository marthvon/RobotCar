#include "Timer.h"

void Timer::begin() {
    last = millis();
}

const unsigned long Timer::get_delta() const {
    return delta;
}

const unsigned long Timer::get_timestamp() const {
    return last;
}

void Timer::tick() {
    const unsigned long now = millis();
    delta = now - last;
    last = now;
}

const unsigned long get_delta_from_timestamp(const unsigned long timestamp) const {
    return last - timestamp;
}
