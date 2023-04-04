#include "DC2W.h"

using namespace Car;

void DigitalCar2W::begin() {
    pinMode(forwardLeftWheel, OUTPUT);
    pinMode(backwardLeftWheel, OUTPUT);
    pinMode(forwardRightWheel, OUTPUT);
    pinMode(backwardRightWheel, OUTPUT);

    #ifdef DEBUG
        hasInit = true;
    #endif
}

void DigitalCar2W::run() { 
    #ifdef DEBUG
        if(!hasInit) {
            Serial.println("[Error]: Pinmodes have not been initialized for this instance of DigitalCar2W.\n\tThe \"run\" methods operation were stopped\n");
            return;    
        }
    #endif

    if(!(data & 0b00001000))
        return;
    digitalWrite(forwardLeftWheel, (isGo() & !isReverse() & isRight()? HIGH: LOW));
    digitalWrite(backwardLeftWheel, (isGo() & isReverse() & isLeft()? HIGH: LOW));
    digitalWrite(forwardRightWheel, (isGo() & !isReverse() & isLeft()? HIGH: LOW));
    digitalWrite(backwardRightWheel, (isGo() & isReverse() & isRight()? HIGH: LOW));
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
