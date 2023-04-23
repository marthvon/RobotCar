#include "DC2W.h"

using namespace Car;

DigitalCar2W::DigitalCar2W(const uint8_t p_forwardLeftWheel, const uint8_t p_backwardLeftWheel, const uint8_t p_forwardRightWheel, const uint8_t p_backwardRightWheel)
    : wheel(p_forwardLeftWheel, p_backwardLeftWheel, p_forwardRightWheel, p_backwardRightWheel)
{}
DigitalCar2W::DigitalCar2W(DigitalCar2W& other) 
    : wheel(other.wheel.leftForward, other.wheel.leftBackward, other.wheel.rightForward, other.wheel.rightBackward)
{} 

void DigitalCar2W::begin() {
    pinMode(wheel.leftForward, OUTPUT);
    pinMode(wheel.leftBackward, OUTPUT);
    pinMode(wheel.rightForward, OUTPUT);
    pinMode(wheel.rightBackward, OUTPUT);
}

void DigitalCar2W::run() { 
    if(!(data & 0b00001000))
        return;
    digitalWrite(wheel.leftForward, (isGo() & !isReverse() & isRight()? HIGH: LOW));
    digitalWrite(wheel.leftBackward, (isGo() & isReverse() & isLeft()? HIGH: LOW));
    digitalWrite(wheel.rightForward, (isGo() & !isReverse() & isLeft()? HIGH: LOW));
    digitalWrite(wheel.rightBackward, (isGo() & isReverse() & isRight()? HIGH: LOW));
    data &= 0b11110111;
}

void DigitalCar2W::reset() {
    data = 0b00001011;
}

void DigitalCar2W::setGo(const bool p_go) {
    data &= 0b00001111;
    data |= 0b00001000 | (p_go? 0b00010000 : 0);
}
inline const bool DigitalCar2W::isGo() {
    return (data >> 4);
}
void DigitalCar2W::setReverse(const bool p_reverse) {
    data &= 0b00011011;
    data |= 0b00001000 | (p_reverse? 0b00000100 : 0);
}
inline const bool DigitalCar2W::isReverse() {
    return (data & 0b00000100);
}
void DigitalCar2W::setStir(const STIR p_stir) {
    data &= 0b00011100;
    data |= 0b00001000 | (uint8_t)(p_stir);
}
inline const bool DigitalCar2W::isLeft() {
    return (data & 0b00000010);
}
inline const bool DigitalCar2W::isRight() {
    return (data & 0b00000001);
}
