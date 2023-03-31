#include "Car.h"

#define templateCar2W template<uint8_t forwardLeftWheel, uint8_t backwardLeftWheel, uint8_t forwardRightWheel, uint8_t backwardRightWheel>
#define DigitalCar2W  DigitalCar2W<forwardLeftWheel, backwardLeftWheel, forwardRightWheel, backwardRightWheel>
#define AnalogCar2W  AnalogCar2W<forwardLeftWheel, backwardLeftWheel, forwardRightWheel, backwardRightWheel>

templateCar2W
void DigitalCar2W::begin() const {
    pinMode(forwardLeftWheel, OUTPUT);
    pinMode(backwardLeftWheel, OUTPUT);
    pinMode(forwardRightWheel, OUTPUT);
    pinMode(backwardRightWheel, OUTPUT);
}

templateCar2W
void DigitalCar2W::run() { 
    if(!(data & 0b00001000))
        return;
    digitalWrite(forwardLeftWheel, (isGo() & !isReverse() & isRight()? HIGH: LOW));
    digitalWrite(backwardLeftWheel, (isGo() & isReverse() & isLeft()? HIGH: LOW));
    digitalWrite(forwardRightWheel, (isGo() & !isReverse() & isLeft()? HIGH: LOW));
    digitalWrite(backwardRightWheel, (isGo() & isReverse() & isRight()? HIGH: LOW));
    data &= 0b11110111;
}

templateCar2W
void DigitalCar2W::setGo(const bool p_go) {
    data &= 0b00001111;
    data |= 0b00001000 | (p_go? 0b00010000 : 0);
}
templateCar2W
inline const bool DigitalCar2W::isGo() {
    return (data >> 4);
}
templateCar2W
void DigitalCar2W::setReverse(const bool p_reverse) {
    data &= 0b00011011;
    data |= 0b00001000 | (p_reverse? 0b00000100 : 0);
}
templateCar2W
inline const bool DigitalCar2W::isReverse() {
    return (data & 0b00000100);
}
templateCar2W
void DigitalCar2W::setStir(const DigitalCar2W::STIR p_stir) {
    data &= 0b00011100;
    data |= 0b00001000 | (uint8_t)(p_stir);
}
templateCar2W
inline const bool DigitalCar2W::isLeft() {
    return (data & 0b00000010);
}
templateCar2W
inline const bool DigitalCar2W::isRight() {
    return (data & 0b00000001);
}


templateCar2W
void AnalogCar2W::begin() const {
    pinMode(forwardLeftWheel, OUTPUT);
    pinMode(backwardLeftWheel, OUTPUT);
    pinMode(forwardRightWheel, OUTPUT);
    pinMode(backwardRightWheel, OUTPUT);
}

templateCar2W
void AnalogCar2W::run() const {
    if(!isUpdate)
        return;
    isUpdate = false;
    if(speed == 0.0) {
        digitalWrite(forwardLeftWheel, LOW);
        digitalWrite(backwardLeftWheel, LOW);
        digitalWrite(forwardRightWheel, LOW);
        digitalWrite(backwardRightWheel, LOW);
        return;
    }
    update();
}

templateCar2W
void AnalogCar2W::update() const { 
    const uint8_t s = speed > 0? speed : -speed;
    float a = cos(angle);
    const uint8_t sl = 255 * (speed > 0? (angle < 0? (a<0?-a:a): 1.0) : (angle > 0? (a<0?-a:a): 1.0)) * s;
    const uint8_t sr = 255 * (speed > 0? (angle > 0? (a<0?-a:a): 1.0) : (angle < 0? (a<0?-a:a): 1.0)) * s;
    if(speed > 0? (a < 0 && angle > 0) : (angle >= 0 || a >= 0)) {
        analogWrite(forwardLeftWheel, sl); 
        digitalWrite(backwardLeftWheel, LOW);
    } else { // speed < 0 && (angle <= 0 || a >= 0)
        digitalWrite(forwardLeftWheel, LOW);
        analogWrite(backwardLeftWheel, sl);         
    }

    if(speed > 0? (a < 0 && angle < 0) : (angle <= 0 || a >= 0)) {
        analogWrite(forwardRightWheel, sl); 
        digitalWrite(backwardRightWheel, LOW);
    } else {
        digitalWrite(forwardRightWheel, LOW);
        analogWrite(backwardRightWheel, sl);
    }
}

templateCar2W
void AnalogCar2W::setSpeed(const float p_speed) {
    speed = p_speed;
    isUpdate = true;
}

templateCar2W
void AnalogCar2W::setAngle(const float p_angle) {
    angle = p_angle;
    isUpdate = true;
}