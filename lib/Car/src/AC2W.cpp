#include "AC2W.h"

using namespace Car;

AnalogCar2W::AnalogCar2W(const uint8_t p_forwardLeftWheel, const uint8_t p_backwardLeftWheel, const uint8_t p_forwardRightWheel, const uint8_t p_backwardRightWheel) 
    : wheel(p_forwardLeftWheel, p_backwardLeftWheel, p_forwardRightWheel, p_backwardRightWheel)
{}
AnalogCar2W::AnalogCar2W(const AnalogCar2W& other) 
    : wheel(other.wheel.leftForward, other.wheel.leftBackward, other.wheel.rightForward, other.wheel.rightBackward)
{} 

void AnalogCar2W::begin() {
    pinMode(wheel.leftForward, OUTPUT);
    pinMode(wheel.leftBackward, OUTPUT);
    pinMode(wheel.rightForward, OUTPUT);
    pinMode(wheel.rightBackward, OUTPUT);
}

void AnalogCar2W::run() {
    if(!isUpdate)
        return;
    isUpdate = false;
    if(speed == 0.0) {
        digitalWrite(wheel.leftForward, LOW);
        digitalWrite(wheel.leftBackward, LOW);
        digitalWrite(wheel.rightForward, LOW);
        digitalWrite(wheel.rightBackward, LOW);
        return;
    }
    update();
}

void AnalogCar2W::reset() {
    speed = 0;
    angle = 0;
    isUpdate = true;
}

void AnalogCar2W::update() const { 
    const uint8_t s = speed > 0? speed : -speed;
    float a = cos(angle);
    //                        if go forward? if stir left? dampen speed  else go backward? if stir right? dampen speed... otherwise just go full speed
    const uint8_t sl = 255 * (speed > 0? (angle < 0? (a<0?-a:a): 1.0) : (angle > 0? (a<0?-a:a): 1.0)) * s;
    //                        if go forward? if stir right? dampen speed  else go backward? if stir left? dampen speed... otherwise just go full speed
    const uint8_t sr = 255 * (speed > 0? (angle > 0? (a<0?-a:a): 1.0) : (angle < 0? (a<0?-a:a): 1.0)) * s;

    //if go forward and stir staight or right(+) else stir left(-) but angle<=90deg... otherwise go backward but stir right(+) and angle>90deg
    if(speed < 0? (a < 0 && angle > 0) : (angle >= 0 || a >= 0)) {
        analogWrite(wheel.leftForward,  sl); 
        digitalWrite(wheel.leftBackward, LOW);
    } else { // speed < 0 && (angle <= 0 || a >= 0)
        digitalWrite(wheel.leftForward,  LOW);
        analogWrite(wheel.leftBackward, sl);         
    }
    //if go forward and stir staight or left(-) else stir right(+) but angle<=90deg... otherwise go backward but stir left(-) and angle>90deg
    if(speed < 0? (a < 0 && angle < 0) : (angle <= 0 || a >= 0)) {
        analogWrite(wheel.rightForward, sl); 
        digitalWrite(wheel.rightBackward, LOW);
    } else {
        digitalWrite(wheel.rightForward, LOW);
        analogWrite(wheel.rightBackward, sl);
    }
}

void AnalogCar2W::setSpeed(const float p_speed) {
    speed = p_speed;
    isUpdate = true;
}

void AnalogCar2W::setAngle(const float p_angle) {
    angle = p_angle;
    isUpdate = true;
}
